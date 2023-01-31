#include "fd_base58.h"
#include "../txn/fd_txn.h"

void basic_test32( void ) {
  char buf[ FD_BASE58_ENCODED_32_SZ ];
  uchar bytes[ 32UL ];
  fd_memset( bytes, '\0', 32UL );
  FD_TEST( !strcmp( "11111111111111111111111111111111", fd_base58_encode_32( bytes, buf ) ) );
  bytes[31]++;
  FD_TEST( !strcmp( "11111111111111111111111111111112", fd_base58_encode_32( bytes, buf ) ) );
  bytes[30]++;
  /* 257 in base58 is 5S */
  FD_TEST( !strcmp( "1111111111111111111111111111115S", fd_base58_encode_32( bytes, buf ) ) );
  fd_memset( bytes, '\xFF', 32UL );
  FD_TEST( !strcmp( "JEKNVnkbo3jma5nREBBJCDoXFVeKkD56V3xKrvRmWxFG", fd_base58_encode_32( bytes, buf ) ) );
  bytes[31]--;
  FD_TEST( !strcmp( "JEKNVnkbo3jma5nREBBJCDoXFVeKkD56V3xKrvRmWxFF", fd_base58_encode_32( bytes, buf ) ) );
}
void basic_test64( void ) {
  char buf[ FD_BASE58_ENCODED_64_SZ ];
  uchar bytes[ 64UL ];
  fd_memset( bytes, '\0', 64UL );
  FD_TEST( !strcmp( "1111111111111111111111111111111111111111111111111111111111111111", fd_base58_encode_64( bytes, buf ) ) );
  bytes[63]++;
  FD_TEST( !strcmp( "1111111111111111111111111111111111111111111111111111111111111112", fd_base58_encode_64( bytes, buf ) ) );
  bytes[62]++;
  /* 257 in base58 is 5S */
  FD_TEST( !strcmp( "111111111111111111111111111111111111111111111111111111111111115S", fd_base58_encode_64( bytes, buf ) ) );
  fd_memset( bytes, '\xFF', 64UL );
  FD_TEST( !strcmp( "67rpwLCuS5DGA8KGZXKsVQ7dnPb9goRLoKfgGbLfQg9WoLUgNY77E2jT11fem3coV9nAkguBACzrU1iyZM4B8roQ",
                    fd_base58_encode_64( bytes, buf ) ) );
  bytes[63]--;
  FD_TEST( !strcmp( "67rpwLCuS5DGA8KGZXKsVQ7dnPb9goRLoKfgGbLfQg9WoLUgNY77E2jT11fem3coV9nAkguBACzrU1iyZM4B8roP",
                    fd_base58_encode_64( bytes, buf ) ) );
}

void validators( void ) {
  char buf[64];
  uchar buf2[32];
  const char encoded[ 6 ][ 45 ] = {
    "XkCriyrNwS3G4rzAXtG5B1nnvb5Ka1JtCku93VqeKAr",
    "Awes4Tr6TX8JDzEhCZY2QVNimT6iD1zWHzf1vNyGvpLM",
    "DRpbCBMxVnDK7maPM5tGv6MvB3v1sRMC86PZ8okm21hy",
    "EgxVyTgh2Msg781wt9EsqYx4fW8wSvfFAHGLaJQjghiL",
    "EvnRmnMrd69kFdbLMxWkTn1icZ7DCceRhvmb2SJXqDo4",
    "Certusm1sa411sMpV9FPqU5dXAYhmmhygvxJ23S6hJ24"
  };
  const uchar binary[ 6 ][ FD_TXN_ACCT_ADDR_SZ ] = {
    { 0x07,0xe0,0x46,0x93,0x3c,0x70,0x90,0xfa,0x2e,0x3e,0x85,0x39,0xfc,0x95,0xdc,0x8f,
      0xed,0x4d,0x15,0xd0,0xbf,0x3d,0x3a,0xce,0x98,0x88,0x81,0x67,0x81,0x30,0x8d,0x8b },
    { 0x93,0xb9,0x5b,0xa3,0xdb,0x98,0x5d,0x8c,0xca,0xe4,0x90,0x69,0x42,0x8f,0xec,0xf2,
      0xff,0x3b,0x7d,0xa6,0x62,0xa9,0x58,0xba,0x9e,0x0e,0x46,0xeb,0x0d,0xbd,0x16,0xf6 },
    { 0xb8,0xa7,0xfd,0xff,0xf8,0x8b,0x18,0xcc,0x25,0x98,0x52,0x9d,0x0d,0xad,0x9b,0xf9,
      0x69,0x7a,0x8a,0x20,0x8e,0xe9,0x68,0xd4,0x4e,0x61,0x8b,0x03,0x2e,0x04,0x65,0x10 },
    { 0xcb,0x64,0x55,0xcb,0x03,0x29,0xc7,0x8f,0xea,0x65,0x57,0xa6,0x1b,0x97,0x9a,0x96,
      0x5e,0xe7,0xe7,0x9a,0xc7,0x8c,0x8f,0xd9,0x89,0x37,0x92,0xf2,0x78,0x6d,0x0e,0xd5 },
    { 0xce,0xef,0x13,0xd8,0x09,0x8b,0xf5,0xda,0x4b,0x19,0x59,0x6a,0xc9,0xad,0x36,0x7c,
      0x9c,0x5e,0x1a,0xad,0xe0,0xae,0xc9,0xd7,0xc0,0x41,0x3a,0xeb,0xcc,0x62,0x3b,0xdf },
    { 0xad,0x23,0x76,0x6d,0xde,0xe6,0xe9,0x9c,0xa3,0x34,0x0e,0xe5,0xbe,0xac,0x08,0x84,
      0xc8,0x9d,0xdb,0xc7,0x4d,0xfe,0x24,0x8f,0xea,0x56,0x13,0x56,0x98,0xba,0xfd,0xd1 }
  };
  for( ulong i=0UL; i<6UL; i++ ) {
    FD_TEST( !strcmp( encoded[ i ], fd_base58_encode_32( binary[ i ],  buf  )       ) );
    FD_TEST( !memcmp( binary[ i ],  fd_base58_decode_32( encoded[ i ], buf2 ), 32UL ) );
  }
}
#define MAKE_TESTS(n)                                                                                               \
void test_matches_naive ## n ( fd_rng_t * rng ) {                                                                   \
  for( ulong i=0UL; i<10000000UL; i++ ) {                                                                           \
    uchar bytes[ n ];                                                                                               \
    uchar bytes2[ n ];                                                                                              \
    for( ulong j=0UL; j<(ulong)(n); j++ ) {                                                                         \
      bytes[ j ] = fd_rng_uchar( rng );                                                                             \
    }                                                                                                               \
    char buffer1[ 2UL*(n) ];                                                                                        \
    char buffer2[ 2UL*(n) ];                                                                                        \
    FD_TEST( !strcmp( fd_base58_encode_##n(  bytes,    buffer1          ),                                          \
                      fd_base58_encode_slow( bytes, n, buffer2, 2UL*(n) ) ) );                                      \
    if( !fd_base58_decode_##n( buffer1, bytes2 ) ) { __asm("int $3"); } \
                                                                                                                    \
    FD_TEST( !memcmp( fd_base58_decode_##n(  buffer1,                  bytes2             ), bytes, (ulong)(n) ) ); \
    FD_TEST( !memcmp( fd_base58_decode_slow( buffer1, strlen(buffer1), bytes2, (ulong)(n) ), bytes, (ulong)(n) ) ); \
  }                                                                                                                 \
}                                                                                                                   \
                                                                                                                    \
void test_performance ## n( fd_rng_t * rng ) {                                                                      \
  const ulong test_count = 3000000;                                                                                 \
                                                                                                                    \
  ulong xor = 0UL;                                                                                                  \
  char buf[2UL * (n) ];                                                                                             \
  uchar bytes[ n ];                                                                                                 \
  /* Warmup loop, count non-conversion work */                                                                      \
  long warmup_start = fd_log_wallclock( );                                                                          \
  for( ulong i=0UL; i<test_count; i++ ) {                                                                           \
    for( ulong j=0UL; j<(ulong)(n); j++ ) {                                                                         \
      bytes[ j ] = fd_rng_uchar( rng );                                                                             \
    }                                                                                                               \
  }                                                                                                                 \
  for( ulong j=0UL; j<(ulong)(n); j++ ) {                                                                           \
    xor ^= (ulong)bytes[ j ];                                                                                       \
  }                                                                                                                 \
  long warmup_end = fd_log_wallclock( );                                                                            \
                                                                                                                    \
  long start = fd_log_wallclock( );                                                                                 \
  for( ulong i=0UL; i<test_count; i++ ) {                                                                           \
    for( ulong j=0UL; j<(ulong)(n); j++ ) bytes[ j ] = fd_rng_uchar( rng );                                         \
    fd_base58_encode_##n( bytes, buf );                                                                             \
    for( ulong j=0UL; j<2UL*(n); j++ ) xor ^= (ulong)buf[ j ]; /* Prevent compiler from removing call */            \
  }                                                                                                                 \
  long end = fd_log_wallclock( );                                                                                   \
  long ed_start = fd_log_wallclock( );                                                                              \
  for( ulong i=0UL; i<test_count; i++ ) {                                                                           \
    for( ulong j=0UL; j<(ulong)(n); j++ ) bytes[ j ] = fd_rng_uchar( rng );                                         \
    fd_base58_encode_##n( bytes, buf );                                                                             \
    fd_base58_decode_##n( buf, bytes );                                                                             \
    for( ulong j=0UL; j<(n); j++ ) xor ^= (ulong)bytes[ j ]; /* Prevent compiler from removing call */              \
  }                                                                                                                 \
  long ed_end = fd_log_wallclock( );                                                                                \
  FD_LOG_NOTICE(( #n ": Average time per call: %f ns. Average time per empty loop: %f ns. "                         \
        "Average encode+decode time per call: %f ns.",                                                              \
        (double)(end       -       start)/(double)test_count,                                                       \
        (double)(warmup_end-warmup_start)/(double)test_count,                                                       \
        (double)(ed_end    -    ed_start)/(double)test_count  ));                                                   \
                                                                                                                    \
  __asm__ volatile("" :: "m" (xor)); /* Prevent compiler from eliminating everything */                             \
}                                                                                                                   \

void test_performance_slow( fd_rng_t * rng ) {                                                          
  const ulong test_count = 3000000;                                                                     
                                                                                                        
  ulong xor = 0UL;                                                                                      
  char buf[ 64UL ];                                                                                 
  uchar bytes[ 32UL ];                                                                                  
  /* Warmup loop, count non-conversion work */                                                          
  long warmup_start = fd_log_wallclock( );                                                              
  for( ulong i=0UL; i<test_count; i++ ) {                                                               
    for( ulong j=0UL; j<(ulong)(32); j++ ) {                                                            
      bytes[ j ] = fd_rng_uchar( rng );                                                                 
    }                                                                                                   
  }                                                                                                     
  for( ulong j=0UL; j<(ulong)(32); j++ ) {                                                              
    xor ^= (ulong)bytes[ j ];                                                                           
  }                                                                                                     
  long warmup_end = fd_log_wallclock( );                                                                
                                                                                                        
  long start = fd_log_wallclock( );                                                                     
  for( ulong i=0UL; i<test_count; i++ ) {                                                               
    for( ulong j=0UL; j<(ulong)(32); j++ ) bytes[ j ] = fd_rng_uchar( rng );                            
    fd_base58_encode_slow( bytes, 32UL, buf, 45UL );                                                    
    for( ulong j=0UL; j<45UL; j++ ) xor ^= (ulong)buf[ j ]; /* Prevent compiler from removing call */
  }                                                                                                     
  long end = fd_log_wallclock( );                                                                       
  FD_LOG_NOTICE(( "slow: Average time per call: %f ns. Average time per empty loop: %f ns",             
        (double)(end       -       start)/(double)test_count,                                           
        (double)(warmup_end-warmup_start)/(double)test_count ));                                        
                                                                                                        
  __asm__ volatile("" :: "m" (xor)); /* Prevent compiler from eliminating everything */                 
}                                                                                                       

MAKE_TESTS(32)
MAKE_TESTS(64)

int
main( int     argc,
      char ** argv ) {
  fd_boot( &argc, &argv );

  fd_rng_t _rng[1]; fd_rng_t * rng = fd_rng_join( fd_rng_new( _rng, 0U, 0UL ) );
  basic_test64( );
  basic_test32( );
  validators( );
  test_performance_slow( rng );
  test_matches_naive32( rng );

  test_performance32( rng );

  test_matches_naive64( rng );
  test_performance64( rng );
  fd_rng_delete( fd_rng_leave( rng ) );

  FD_LOG_NOTICE(( "pass" ));
  fd_halt();
  return 0;
}
