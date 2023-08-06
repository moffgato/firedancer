#include "../fd_flamenco.h"
#include "fd_solcap.pb.h"
#include "fd_solcap_proto.h"
#include "fd_solcap_writer.h"
#include "../cjson/cJSON.h"
#include "../../ballet/base58/fd_base58.h"
#include "../../ballet/base64/fd_base64.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <math.h>

static int
usage( void ) {
  fprintf( stderr,
    "Usage: fd_solcap_import [options] {IN_FILE} {OUT_FILE}\n"
    "\n"
    "Imports a runtime capture file from JSON.\n"
    "\n"
    "Options:\n"
    "  --page-sz      {gigantic|huge|normal}    Page size\n"
    "  --page-cnt     {count}                   Page count\n"
    "  --scratch-mb   1024                      Scratch mem MiB\n"
    "\n" );
  return 0;
}

/* fd_alloc wrapper */

static fd_alloc_t * current_alloc;
static void * my_malloc( ulong sz ) { return fd_alloc_malloc( current_alloc, 1UL, sz ); }
static void   my_free  ( void * p ) {        fd_alloc_free  ( current_alloc, p       ); }

static cJSON *
read_json_file( fd_wksp_t *  wksp,
                fd_alloc_t * alloc,
                char const * path ) {

  /* Wire up fd_alloc with cJSON */

  current_alloc = alloc;
  cJSON_Hooks hooks = {
    .malloc_fn = my_malloc,
    .free_fn   = my_free
  };
  cJSON_InitHooks( &hooks );

  /* Open file */

  int fd;
  fd = open( path, O_RDONLY );
  if( FD_UNLIKELY( fd<0 ) ) {
    FD_LOG_WARNING(( "open(%s) failed (%d-%s)", path, errno, strerror( errno ) ));
    return NULL;
  }

  /* Figure out file size */

  struct stat stat;
  if( FD_UNLIKELY( fstat( fd, &stat )<0 ) ) {
    FD_LOG_WARNING(( "fstat(%s) failed (%d-%s)", path, errno, strerror( errno ) ));
    close( fd );
    return NULL;
  }

  /* Allocate buffer to store file content */

  char * buf = fd_wksp_alloc_laddr( wksp, 1UL, (ulong)stat.st_size, 1UL );
  if( FD_UNLIKELY( !buf ) ) {
    FD_LOG_WARNING(( "Failed to alloc memory region to fit file content" ));
    close( fd );
    return NULL;
  }

  /* Copy file content to memory */

  char * cursor = buf;
  ulong rem = (ulong)stat.st_size;
  while( rem>0UL ) {
    long n = read( fd, cursor, rem );
    if( FD_UNLIKELY( n<0L ) ) {
      FD_LOG_WARNING(( "read(%s) failed (%d-%s)", path, errno, strerror( errno ) ));
      close( fd );
      return NULL;
    }
    if( FD_UNLIKELY( n==0L ) ) {
      FD_LOG_WARNING(( "read(%s) failed: unexpected EOF", path ));
      close( fd );
      return NULL;
    }

    cursor += (ulong)n;
    rem    -= (ulong)n;
  }

  /* Call parser */

  cJSON * json = cJSON_ParseWithLength( buf, (ulong)stat.st_size );

  /* Clean up */

  fd_wksp_free_laddr( buf );
  close( fd );
  return json;
}

/* unmarshal_hash interprets given JSON node as a string containing
   the Base58 encoding of 32 bytes.  Copies the bytes out to out_buf.
   Returns NULL if json is NULL, json is not string, or is not a valid
   32-byte Base58 encoding.  Returns out_buf on success. */

static uchar *
unmarshal_hash( cJSON const * json,
                uchar         out_buf[static 32] ) {

  char const * str = cJSON_GetStringValue( json );
  if( FD_UNLIKELY( !str ) ) return NULL;

  return fd_base58_decode_32( str, out_buf );
}

/* unmarshal_bank_preimage reads top-level bank preimage information
   from given JSON dictionary.   Copies values into given out struct.
   Aborts application via error log on failure. */

static void
unmarshal_bank_preimage( cJSON const *            json,
                         fd_solcap_BankPreimage * out ) {

  double slot_f = cJSON_GetNumberValue( cJSON_GetObjectItem( json, "slot" ) );
  FD_TEST( isfinite( slot_f ) );
  out->slot = (ulong)slot_f;

  FD_TEST( unmarshal_hash( cJSON_GetObjectItem( json, "hash"                ), out->bank_hash          ) );
  FD_TEST( unmarshal_hash( cJSON_GetObjectItem( json, "parent_hash"         ), out->prev_bank_hash     ) );
  FD_TEST( unmarshal_hash( cJSON_GetObjectItem( json, "accounts_delta_hash" ), out->account_delta_hash ) );
  FD_TEST( unmarshal_hash( cJSON_GetObjectItem( json, "last_blockhash"      ), out->poh_hash           ) );

  double sig_cnt_f = cJSON_GetNumberValue( cJSON_GetObjectItem( json, "signature_count" ) );
  FD_TEST( isfinite( sig_cnt_f ) );
  out->signature_cnt = (ulong)sig_cnt_f;

  cJSON * accs = cJSON_GetObjectItem( json, "accounts" );
  FD_TEST( accs );
  out->account_cnt = (ulong)cJSON_GetArraySize( accs );
}

/* unmarshal_account reads account meta/data from given JSON object.
   Object should be a dictionary and is found as an element of the
   "accounts" array.  On success, returns pointer to account data
   (allocated in current scratch frame), and copies metadata to given
   out structs.  On failure, aborts application via error log. */

static void *
unmarshal_account( cJSON const *             json,
                   fd_solcap_account_tbl_t * rec,
                   fd_solcap_AccountMeta *   meta ) {

  /* TODO !!! THIS IS OBVIOUSLY UNSAFE
     Representing lamports as double causes precision-loss for values
     exceeding 2^53-1.  This appears to be a limitation of the cJSON
     library. */
  double lamports_f = cJSON_GetNumberValue( cJSON_GetObjectItem( json, "lamports" ) );
  FD_TEST( isfinite( lamports_f ) );
  meta->lamports = (ulong)lamports_f;

  double rent_epoch_f = cJSON_GetNumberValue( cJSON_GetObjectItem( json, "rent_epoch" ) );
  FD_TEST( isfinite( rent_epoch_f ) );
  meta->rent_epoch = (ulong)rent_epoch_f;

  cJSON * executable_o = cJSON_GetObjectItem( json, "executable" );
  FD_TEST( executable_o );
  meta->executable = cJSON_IsBool( executable_o ) & cJSON_IsTrue( executable_o );

  FD_TEST( unmarshal_hash( cJSON_GetObjectItem( json, "pubkey" ), rec->key  ) );
  FD_TEST( unmarshal_hash( cJSON_GetObjectItem( json, "hash"   ), rec->hash ) );

  /* Data handling ... Base64 decode */

  char const * data_b64 = cJSON_GetStringValue( cJSON_GetObjectItem( json, "data" ) );
  FD_TEST( data_b64 );

  /* sigh ... cJSON doesn't remember string length, although it
     obviously had this information while parsing. */
  ulong data_b64_len = strlen( data_b64 );

  /* Very rough upper bound for decoded data sz.
     Could do better here, but better to be on the safe side. */
  ulong approx_data_sz = 3UL + data_b64_len/2UL;

  /* Grab scratch memory suitable for storing account data */
  void * data = fd_scratch_alloc( /* align */ 1UL, /* sz */ approx_data_sz );
  FD_TEST( data );

  /* Base64 decode */
  long data_sz = fd_base64_decode( data, data_b64, data_b64_len );
  FD_TEST( data_sz>=0L ); /* check for corruption */
  meta->data_sz = (ulong)data_sz;

  return data;
}

int
main( int     argc,
      char ** argv ) {
  fd_boot( &argc, &argv );
  fd_flamenco_boot( &argc, &argv );

  /* Command line handling */

  for( int i=1; i<argc; i++ )
    if( 0==strcmp( argv[i], "--help" ) ) return usage();

  char const * _page_sz   = fd_env_strip_cmdline_cstr ( &argc, &argv, "--page-sz",    NULL, "gigantic" );
  ulong        page_cnt   = fd_env_strip_cmdline_ulong( &argc, &argv, "--page-cnt",   NULL, 2UL        );
  ulong        scratch_mb = fd_env_strip_cmdline_ulong( &argc, &argv, "--scratch-mb", NULL, 1024UL     );

  ulong page_sz = fd_cstr_to_shmem_page_sz( _page_sz );
  if( FD_UNLIKELY( !page_sz ) ) FD_LOG_ERR(( "unsupported --page-sz" ));

  if( argc!=3 ) {
    fprintf( stderr, "ERROR: expected 2 arguments, got %d\n", argc-1 );
    usage();
    return 1;
  }

  /* Acquire workspace */

  fd_wksp_t * wksp = fd_wksp_new_anonymous( page_sz, page_cnt, fd_log_cpu_id(), "wksp", 0UL );
  if( FD_UNLIKELY( !wksp ) ) FD_LOG_ERR(( "fd_wksp_new_anonymous() failed" ));

  /* Create scratch allocator */

  ulong  smax = scratch_mb << 20;
  void * smem = fd_wksp_alloc_laddr( wksp, fd_scratch_smem_align(), smax, 1UL );
  if( FD_UNLIKELY( !smem ) ) FD_LOG_ERR(( "Failed to alloc scratch mem" ));

# define SCRATCH_DEPTH (4UL)
  ulong fmem[ SCRATCH_DEPTH ] __attribute((aligned(FD_SCRATCH_FMEM_ALIGN)));

  fd_scratch_attach( smem, fmem, smax, SCRATCH_DEPTH );

  /* Create heap allocator */

  void * alloc_buf = fd_wksp_alloc_laddr( wksp, fd_alloc_align(), fd_alloc_footprint(), 2UL );
  fd_alloc_t * alloc = fd_alloc_join( fd_alloc_new( alloc_buf, 2UL ), 0UL );
  if( FD_UNLIKELY( !alloc ) ) FD_LOG_ERR(( "Failed to create heap" ));

  /* Read input file */

  char const * in_path = argv[1];
  cJSON * json = read_json_file( wksp, alloc, in_path );
  if( FD_UNLIKELY( !json ) ) FD_LOG_ERR(( "Failed to read input file" ));
  FD_LOG_NOTICE(( "Read input file" ));

  /* Read bank preimage */

  fd_solcap_BankPreimage preimg[1] = {{0}};
  unmarshal_bank_preimage( json, preimg );

  cJSON * json_acc = cJSON_GetObjectItem( json, "accounts" );
  int n = cJSON_GetArraySize( json_acc );
  for( int i=0; i<n; i++ ) {
    fd_scratch_push();

    cJSON * acc = cJSON_GetArrayItem( json_acc, i );
    fd_solcap_account_tbl_t rec[1];  memset( rec,  0, sizeof(fd_solcap_account_tbl_t) );
    fd_solcap_AccountMeta   meta[1]; memset( meta, 0, sizeof(fd_solcap_AccountMeta  ) );
    void * data = unmarshal_account( acc, rec, meta );
    (void)data;

    fd_scratch_pop();
  }

  /* Cleanup */

  cJSON_free( json );
  fd_wksp_free_laddr( fd_alloc_delete( fd_alloc_leave( alloc ) ) );
  FD_TEST( fd_scratch_frame_used()==0UL );
  fd_wksp_free_laddr( fd_scratch_detach( NULL ) );
  fd_flamenco_halt();
  fd_halt();
  return 0;
}
