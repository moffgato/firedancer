#include "../../../../flamenco/gossip/fd_gossip.h"
#include "../../../../flamenco/types/fd_types.h"
#include "../../../../util/fd_util.h"
#include "../../../../flamenco/runtime/fd_blockstore.h"
#include "../../../../ballet/base58/fd_base58.h"

#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-extra-args"

#define HEAVIEST_FORK_THRESHOLD_DELTA_PERCENT     38UL
#define REPAIR_THRESHOLD_PERCENT                  42UL
#define WAIT_FOR_SUPERMAJORITY_THRESHOLD_PERCENT  80UL
#define LAST_VOTED_FORK_MAX_SLOTS                 0xFFFF

struct fd_last_voted_fork_slots {
    fd_pubkey_t key;
    ulong       next;
    ulong       timestamp;
    ulong       last_voted_slot;
    fd_pubkey_t last_voted_hash;
    //uchar       offsets[ SIZE_OF_BITMAP ];
};
typedef struct fd_last_voted_fork_slots fd_last_voted_fork_slots_t;

static int
fd_pubkey_eq( fd_pubkey_t const * key1, fd_pubkey_t const * key2 ) {
  return memcmp( key1->key, key2->key, sizeof(fd_pubkey_t) ) == 0;
}

static ulong
fd_pubkey_hash( fd_pubkey_t const * key, ulong seed ) {
  return fd_hash( seed, key->key, sizeof(fd_pubkey_t) );
}

static void
fd_pubkey_copy( fd_pubkey_t * keyd, fd_pubkey_t const * keys ) {
  memcpy( keyd->key, keys->key, sizeof(fd_pubkey_t) );
}

#define MAP_NAME     fd_last_voted_fork_slots
#define MAP_KEY_T    fd_pubkey_t
#define MAP_KEY_EQ   fd_pubkey_eq
#define MAP_KEY_HASH fd_pubkey_hash
#define MAP_KEY_COPY fd_pubkey_copy
#define MAP_T        fd_last_voted_fork_slots_t
#include "../../../../util/tmpl/fd_map_giant.c"

struct fd_last_voted_fork_slots_aggregate {
    fd_blockstore_t *            blockstore;
    fd_last_voted_fork_slots_t * pubkey_to_msg;
    ulong                        my_last_voted_fork_slots[ LAST_VOTED_FORK_MAX_SLOTS ];

    ulong                        root;
    ulong                        total_active_stake;
    ulong                        root_epoch_total_stake;
    ulong                        offset_to_acc_stake[ LAST_VOTED_FORK_MAX_SLOTS ];
};
typedef struct fd_last_voted_fork_slots_aggregate fd_last_voted_fork_slots_aggregate_t;

static union fd_wen_restart_progress {
    fd_last_voted_fork_slots_aggregate_t last_voted_fork_slots;
} progress;

typedef enum {
    WR_STATE_INIT                   = 0,
    WR_STATE_LAST_VOTED_FORK_SLOTS  = 1,
    WR_STATE_FIND_HEAVIEST_FORK     = 2,
    WR_STATE_AGREE_ON_HEAVIEST_FORK = 3,
    WR_STATE_GENERATE_SNAPSHOT      = 4,
    WR_STATE_DONE                   = 5
} fd_wen_restart_state_t;

static fd_wen_restart_state_t state = WR_STATE_INIT;

static ulong
fd_wen_restart_epoch_stake( ulong slot FD_PARAM_UNUSED, fd_pubkey_t * pubkey ) {
    /* TODO */
    /* From the blockstore, get the slot_bank for slot
     * slot_bank.epoch_stakes has stake information,
     * fd_stake_weights_by_node() in fd_stakes.c extracts the stake info from slot_bank.epoch_stakes
     * publish_stake_weights() in replay.c invokes fd_stake_weights_by_node() and gets an array of fd_stake_weight_t */

    fd_pubkey_t keys[5];
    fd_base58_decode_32("7Nc5PuBp6FzeRADM7z9NF2eRjsbN7sqyEaKCifduHd2U", keys[0].key);
    fd_base58_decode_32("6tr7Acuwy5PiEEQMyyDphTeEoY2MAz4nncjEvcZAcERo", keys[1].key);
    fd_base58_decode_32("6huxnL2kxmaqdcqeqwerhc9z74Z6k3m2YpLQwn5mYKk4", keys[2].key);
    fd_base58_decode_32("39mtt6iNnakTZT1guz2fv9ZKZotKafexKrxVc5a2h6Jb", keys[3].key);
    fd_base58_decode_32("6hyZvUyf4Ag9EdPzKGMvMjquupdSPPX28m3kzMSRKBzb", keys[4].key);

    ulong stakes [5] = { 9999999997717120UL,
                         9999999997717120UL,
                         9999999997717120UL,
                         9999999997717120UL,
                         99999997717120UL };

    ulong total = 0;
    for ( ulong i = 0; i < 5; i++ ) {
        total += stakes[i];
        if( FD_UNLIKELY( pubkey && !memcmp(pubkey->key, keys[i].key, 32UL) ) ) {
            return stakes[i];
        }
    }

    return pubkey? ULONG_MAX : total;
}

static fd_wen_restart_state_t
fd_wen_restart_last_voted_fork_slots( fd_gossip_restart_last_voted_fork_slots_t * msg ) {
    fd_pubkey_t * pubkey = &msg->from;
    ulong         stake  = fd_wen_restart_epoch_stake( progress.last_voted_fork_slots.root, pubkey );

    fd_last_voted_fork_slots_t * ele = fd_last_voted_fork_slots_query( progress.last_voted_fork_slots.pubkey_to_msg,
                                                                       pubkey,
                                                                       NULL );

    if( FD_LIKELY( !ele ) ) {
      ele                  = fd_last_voted_fork_slots_insert( progress.last_voted_fork_slots.pubkey_to_msg, pubkey );
      ele->timestamp       = msg->wallclock;
      ele->last_voted_slot = msg->last_voted_slot;
      fd_pubkey_copy( &ele->last_voted_hash, &msg->last_voted_hash );

      progress.last_voted_fork_slots.total_active_stake += stake;
      ulong aggregated = progress.last_voted_fork_slots.total_active_stake;
      ulong total      = progress.last_voted_fork_slots.root_epoch_total_stake;
      ulong percentile = aggregated * 100 / total;
      FD_LOG_NOTICE(( "Total active stake: %lu/%lu = %lu%\nLast voted slot:%lu", aggregated, total, percentile, ele->last_voted_slot ));

      if( FD_UNLIKELY( msg->offsets.discriminant==fd_restart_slots_offsets_enum_run_length_encoding ) ) {
          FD_LOG_ERR(( "Decode of RunLengthEncoding offsets is not implemented" ));
      }

      ulong last_voted_slot = ele->last_voted_slot;
      ulong root_slot = progress.last_voted_fork_slots.root;
      ulong offsets_len = msg->offsets.inner.raw_offsets.offsets.len;
      for (ulong i = 0; i < offsets_len; i++) {
        if( FD_UNLIKELY( last_voted_slot<root_slot+i ) ) break;
        ulong slot = last_voted_slot - i;

        ulong byte_off = i / sizeof(uchar);
        ulong bit_off  = i % sizeof(uchar);
        uchar bit = msg->offsets.inner.raw_offsets.offsets.bits.bits[byte_off] & (uchar)(1 << bit_off);
        if( FD_LIKELY( bit ) ) {
          ulong offset = slot - root_slot;
          progress.last_voted_fork_slots.offset_to_acc_stake[ offset ] += stake;
        }
      }

      if( FD_UNLIKELY( percentile>=WAIT_FOR_SUPERMAJORITY_THRESHOLD_PERCENT ) ) {
          return WR_STATE_FIND_HEAVIEST_FORK;
      }
    }
    return WR_STATE_LAST_VOTED_FORK_SLOTS;
}

static fd_wen_restart_state_t
fd_wen_restart_find_heaviest_fork( ulong delta_percent ) {
    ulong stake_threshold = progress.last_voted_fork_slots.total_active_stake
                            - progress.last_voted_fork_slots.root_epoch_total_stake * delta_percent / 100UL;

    FD_LOG_NOTICE(( "Stake threshold: %lu", stake_threshold ));
    ulong heaviest_fork_slot = progress.last_voted_fork_slots.root;
    for ( ulong offset = 0; offset < LAST_VOTED_FORK_MAX_SLOTS; offset++ ) {
        if( progress.last_voted_fork_slots.offset_to_acc_stake[offset]>=stake_threshold ) {
            heaviest_fork_slot = progress.last_voted_fork_slots.root + offset;
        }
    }

    FD_LOG_NOTICE(( "Heaviest fork slot:%lu\nLocal root slot:%lu", heaviest_fork_slot, progress.last_voted_fork_slots.root ));

    /* TODO */
    /* Repair missing slots and calculate the heaviest_fork_hash for heaviest_fork_slot */
    return WR_STATE_AGREE_ON_HEAVIEST_FORK;
}

void
fd_wen_restart_entry( fd_gossip_restart_last_voted_fork_slots_t * msg ) {
    if( FD_UNLIKELY( state==WR_STATE_INIT ) ) {
      /* TODO */
      /* Join the blockstore and get the root */
      progress.last_voted_fork_slots.root = 1664;
      progress.last_voted_fork_slots.blockstore = NULL;

      /* TODO */
      /* Load the tower from a file */
      /* Get progress.last_voted_fork_slots.my_last_voted_fork_slots by
       * iterating the blockstore backwards from tower.last_vote_slot() */

      /* TODO */
      /* Send RestartLastVotedForkSlots through the gossip tile */

      /* TODO: use valloc or scratch later */
      static char msg_buf[ 1507456 ] __attribute__(( aligned( 128 )));
      /* fd_valloc_t valloc = fd_scratch_virtual(); */
      /* void* shmem = fd_valloc_malloc( valloc, fd_last_voted_fork_slots_align(), fd_last_voted_fork_slots_footprint( FD_PEER_KEY_MAX ) ); */
      progress.last_voted_fork_slots.pubkey_to_msg = fd_last_voted_fork_slots_join( fd_last_voted_fork_slots_new( msg_buf, FD_PEER_KEY_MAX, 0 ) );
      FD_TEST( progress.last_voted_fork_slots.pubkey_to_msg );

      progress.last_voted_fork_slots.total_active_stake = 0;
      progress.last_voted_fork_slots.root_epoch_total_stake = fd_wen_restart_epoch_stake( progress.last_voted_fork_slots.root, NULL );
      fd_memset( progress.last_voted_fork_slots.offset_to_acc_stake, 0, LAST_VOTED_FORK_MAX_SLOTS * sizeof(ulong) );

      state = WR_STATE_LAST_VOTED_FORK_SLOTS;
    }

    switch ( state ) {
      case WR_STATE_LAST_VOTED_FORK_SLOTS:
        state = fd_wen_restart_last_voted_fork_slots( msg );
        break;
      case WR_STATE_FIND_HEAVIEST_FORK:
        state = fd_wen_restart_find_heaviest_fork( HEAVIEST_FORK_THRESHOLD_DELTA_PERCENT );
        break;
      default:
        FD_LOG_ERR(( "state#%u handler is not implemented yet", state ));
        break;
    }
}
