#include "fd_rewards.h"
#include "math.h"

static double
total(fd_inflation_t* inflation, double year) {
    FD_TEST( year >= 0.0 );
    double tapered = inflation->initial * pow((1.0 - inflation->taper), year);
    return (tapered > inflation->terminal) ? tapered : inflation->terminal;
}

static double
foundation(fd_inflation_t* inflation, double year) {
    return (year < inflation->foundation_term) ? inflation->foundation * total(inflation, year) : 0.0;
}

static double
validator(fd_inflation_t *inflation, double year) {
    return total(inflation, year) - foundation(inflation, year);
}

static FD_FN_CONST ulong
get_inflation_start_slot( void ) {
    /*
        https://github.com/firedancer-io/solana/blob/de02601d73d626edf98ef63efd772824746f2f33/runtime/src/bank.rs#L2313-L2331

        This function takes into the account of two feature flags `pico_inflation` and `full_inflation`
        The original solana function follows the below logic:
        - if `full_inflation` is enabled
            return first slot that `full_inflation` is enabled
        - else
            if `pico_inflation` is enabled
                return first slot that `pico_inflation` is enabled
            else
                return 0
        Since both features are enabled at slot 1 on mainnet since ledger v14, the performant & reasonable thing to do is to return 1 (the slot when full_inflation feature flag is enabled)
    */
    return 1;
}

static ulong
get_inflation_num_slots(fd_firedancer_banks_t * bank) {
    /* https://github.com/firedancer-io/solana/blob/de02601d73d626edf98ef63efd772824746f2f33/runtime/src/bank.rs#L2333-L2342 */
    ulong inflaction_activation_slot = get_inflation_start_slot();
    ulong inflation_start_slot = fd_epoch_slot0(
        &bank->epoch_schedule,
        fd_ulong_sat_sub(
            fd_slot_to_epoch(&bank->epoch_schedule, inflaction_activation_slot, NULL),
            1
            )
        );

    ulong epoch = fd_slot_to_epoch(&bank->epoch_schedule, bank->slot, NULL);

    return fd_epoch_slot0(&bank->epoch_schedule, epoch) - inflation_start_slot;
}


/// for a given stake and vote_state, calculate how many
///   points were earned (credits * stake) and new value
///   for credits_observed were the points paid
static void calculate_stake_points_and_credits (
  fd_stake_history_t * stake_history,
  fd_stake_state_t * stake_state,
  fd_vote_state_versioned_t * vote_state_versioned,
  fd_calculate_stake_points_t * result
) {
    fd_vote_epoch_credits_t * epoch_credits;
    switch (vote_state_versioned->discriminant) {
        case fd_vote_state_versioned_enum_current:
            epoch_credits = vote_state_versioned->inner.current.epoch_credits;
            break;
        case fd_vote_state_versioned_enum_v0_23_5:
            epoch_credits = vote_state_versioned->inner.v0_23_5.epoch_credits;
            break;
        case fd_vote_state_versioned_enum_v1_14_11:
            epoch_credits = vote_state_versioned->inner.v1_14_11.epoch_credits;
            break;
        default:
            __builtin_unreachable();
    }
  ulong credits_in_stake = stake_state->inner.stake.stake.credits_observed;
  ulong credits_in_vote = deq_fd_vote_epoch_credits_t_empty( epoch_credits) ? 0 : deq_fd_vote_epoch_credits_t_peek_tail_const( epoch_credits )->credits;

  result->points = 0;
  result->force_credits_update_with_skipped_reward = credits_in_vote < credits_in_stake;
  if (credits_in_vote < credits_in_stake) {
    result->new_credits_observed = credits_in_vote;
    return;
  }
  if (credits_in_vote == credits_in_stake) {
    // don't hint caller and return current value if credits remain unchanged (= delinquent)
    result->new_credits_observed = credits_in_stake;
    return;
  }

  __uint128_t points = 0;
  ulong new_credits_observed = credits_in_stake;

  for ( deq_fd_vote_epoch_credits_t_iter_t iter = deq_fd_vote_epoch_credits_t_iter_init( epoch_credits ); !deq_fd_vote_epoch_credits_t_iter_done( epoch_credits, iter ); iter = deq_fd_vote_epoch_credits_t_iter_next( epoch_credits, iter ) ) {
    fd_vote_epoch_credits_t * ele = deq_fd_vote_epoch_credits_t_iter_ele(epoch_credits, iter );
    ulong epoch = ele->epoch;
    ulong final_epoch_credits = ele->credits;
    ulong initial_epoch_credits = ele->prev_credits;
    __uint128_t earned_credits = 0;
    if (credits_in_stake < initial_epoch_credits) {
      earned_credits = (__uint128_t)(final_epoch_credits - initial_epoch_credits);
    } else if (credits_in_stake < final_epoch_credits) {
      earned_credits = (__uint128_t)(final_epoch_credits - new_credits_observed);
    }
    FD_LOG_NOTICE(("earned_credits: %lu", earned_credits));
    new_credits_observed = fd_ulong_max(new_credits_observed, final_epoch_credits);

    __uint128_t stake_amount = (__uint128_t)(stake_activating_and_deactivating(&stake_state->inner.stake.stake.delegation, epoch, stake_history, NULL).effective);
    points += stake_amount * earned_credits;
  }
  result->points = points;
  result->new_credits_observed = new_credits_observed;
  return;
}


static void calculate_and_redeem_stake_rewards(
  fd_stake_history_t * stake_history,
  fd_stake_state_t * stake_state,
  fd_vote_state_versioned_t * vote_state_versioned,
  ulong rewarded_epoch,
  fd_point_value_t * point_value,
  fd_calculated_stake_rewards_t * result
) {

    /*
    implements the `calculate_stake_rewards` solana function
    for a given stake and vote_state, calculate what distributions and what updates should be made
    returns a tuple in the case of a payout of:
    * staker_rewards to be distributed
    * voter_rewards to be distributed
    * new value for credits_observed in the stake
    returns None if there's no payout or if any deserved payout is < 1 lamport */
    fd_calculate_stake_points_t stake_points_result;
    calculate_stake_points_and_credits( stake_history, stake_state, vote_state_versioned, &stake_points_result);

    // Drive credits_observed forward unconditionally when rewards are disabled
    // or when this is the stake's activation epoch
    stake_points_result.force_credits_update_with_skipped_reward |= (point_value->rewards == 0);
    stake_points_result.force_credits_update_with_skipped_reward |= (stake_state->inner.stake.stake.delegation.activation_epoch == rewarded_epoch);

    if (stake_points_result.force_credits_update_with_skipped_reward) {
    result->staker_rewards = 0;
    result->voter_rewards = 0;
    result->new_credits_observed = stake_points_result.new_credits_observed;
    return;
    }
    if ( stake_points_result.points == 0 || point_value->points == 0 ) {
    result = NULL;
    return;
    }


    ulong rewards = (ulong)(stake_points_result.points * (__uint128_t)point_value->rewards / (__uint128_t) point_value->points);
    FD_LOG_NOTICE(("stake_points_result.points: %lu", stake_points_result.points));
    FD_LOG_NOTICE(("point_value->rewards: %lu", point_value->rewards));
    FD_LOG_NOTICE(("point_value->points: %lu", point_value->points));
    FD_LOG_NOTICE(("REWARDS REWARDS REWARDS: %lu", rewards));
    fd_commission_split_t split_result;
    fd_vote_commission_split( vote_state_versioned, rewards, &split_result );
    if (split_result.is_split && (split_result.voter_portion == 0 || split_result.staker_portion == 0)) {
    result = NULL;
    return;
    }

    result->staker_rewards = split_result.staker_portion;
    result->voter_rewards = split_result.voter_portion;
    result->new_credits_observed = stake_points_result.new_credits_observed;

    /* implements the `redeem_stake_rewards` solana function */
    stake_state->inner.stake.stake.credits_observed += result->new_credits_observed;
    stake_state->inner.stake.stake.delegation.stake += result->staker_rewards;
    return;
}

int
redeem_rewards( fd_global_ctx_t *               global,
                fd_stake_history_t *            stake_history,
                fd_pubkey_t *                   stake_acc,
                fd_vote_state_versioned_t *     vote_state,
                ulong                           rewarded_epoch,
                fd_point_value_t *              point_value,
                fd_calculated_stake_rewards_t * result ) {

    fd_account_meta_t const * stake_acc_meta = NULL;
    int err = fd_acc_mgr_view( global->acc_mgr, global->funk_txn, stake_acc, NULL, &stake_acc_meta, NULL );
    if( FD_UNLIKELY( err ) ) {
        return err;
    }

    fd_stake_state_t stake_state;
    read_stake_state( global, stake_acc_meta, &stake_state );
    if (!fd_stake_state_is_stake( &stake_state)) {
        return FD_EXECUTOR_INSTR_ERR_INVALID_ACC_DATA;
    }

    calculate_and_redeem_stake_rewards(stake_history, &stake_state, vote_state, rewarded_epoch, point_value, result);
    FD_LOG_NOTICE(("result->staker_rewards: %lu", result->staker_rewards));
    FD_LOG_NOTICE(("result->new_credits_observed: %lu", result->new_credits_observed));
    FD_LOG_NOTICE(("result->voter_rewards: %lu", result->voter_rewards));
    if (result == NULL) {
        // ctx->txn_ctx->custom_err = 0; /* Err(StakeError::NoCreditsToRedeem.into()) */
        return FD_EXECUTOR_INSTR_ERR_CUSTOM_ERR;
    }
    err = write_stake_state( global, stake_acc, &stake_state, 0);
    if (err != 0 ) {
        return err;
    }

    fd_account_meta_t * meta = NULL;
    int read_err = fd_acc_mgr_modify( global->acc_mgr, global->funk_txn, stake_acc, 0, 0UL, NULL, NULL, &meta, NULL );
    FD_TEST( read_err==0 );

    meta->info.lamports += result->staker_rewards;

    return FD_EXECUTOR_INSTR_SUCCESS;
}

int calculate_points(
    fd_stake_state_t * stake_state,
    fd_vote_state_versioned_t * vote_state_versioned,
    fd_stake_history_t * stake_history,
    __uint128_t * result
) {
    if (!fd_stake_state_is_stake( stake_state)) {
        return FD_EXECUTOR_INSTR_ERR_INVALID_ACC_DATA;
    }
    FD_LOG_NOTICE(("calculate_points"));
    fd_calculate_stake_points_t stake_point_result;
    calculate_stake_points_and_credits(stake_history, stake_state, vote_state_versioned, &stake_point_result);
    *result = stake_point_result.points;

    return FD_EXECUTOR_INSTR_SUCCESS;
}


static double
epoch_duration_in_years(
    fd_firedancer_banks_t * bank,
    ulong prev_epoch
) {
    /* get_slots_in_epoch */
    ulong slots_in_epoch = (prev_epoch < bank->epoch_schedule.first_normal_epoch) ?
        1UL << fd_ulong_sat_add(prev_epoch, FD_EPOCH_LEN_MIN_TRAILING_ZERO) :
        bank->epoch_schedule.slots_per_epoch;
    FD_LOG_NOTICE(("epoch_duration_in_years prev_epoch: %lu", prev_epoch));
    FD_LOG_NOTICE(("epoch_duration_in_years bank->epoch_schedule.first_normal_epoch: %lu", bank->epoch_schedule.first_normal_epoch));
    FD_LOG_NOTICE(("epoch_duration_in_years slots_in_epoch: %lu", slots_in_epoch));
    FD_LOG_NOTICE(("epoch_duration_in_years bank->slots_per_year: %f", bank->slots_per_year));
    return (double)slots_in_epoch / (double) bank->slots_per_year;
}

static void
calculate_previous_epoch_inflation_rewards(
    fd_firedancer_banks_t * bank,
    ulong prev_epoch_capitalization,
    ulong prev_epoch,
    prev_epoch_inflation_rewards_t * rewards
) {
    /* https://github.com/firedancer-io/solana/blob/de02601d73d626edf98ef63efd772824746f2f33/runtime/src/bank.rs#L2351-L2376 */


    /* slot_in_year_for_inflation
    https://github.com/firedancer-io/solana/blob/de02601d73d626edf98ef63efd772824746f2f33/runtime/src/bank.rs#L2344-L2349
    */
    ulong num_slots = get_inflation_num_slots(bank);
    double slot_in_year = (double)num_slots / bank->slots_per_year;
    rewards->validator_rate = validator(&bank->inflation, slot_in_year);
    rewards->foundation_rate = foundation(&bank->inflation, slot_in_year);
    rewards->prev_epoch_duration_in_years = epoch_duration_in_years(bank, prev_epoch);
    rewards->validator_rewards = (ulong)(rewards->validator_rate * (double)prev_epoch_capitalization * rewards->prev_epoch_duration_in_years);
    FD_LOG_NOTICE(("validator_rate: %.32f", rewards->validator_rate));
    FD_LOG_NOTICE(("prev_epoch_duration_in_years: %.32f", rewards->prev_epoch_duration_in_years));
    FD_LOG_NOTICE(("prev_epoch_capitalization: %lu", prev_epoch_capitalization));
    FD_LOG_NOTICE(("validator_rewards: %lu", rewards->validator_rewards));
}


/// Sum the lamports of the vote accounts and the delegated stake
static ulong
vote_balance_and_staked(fd_stakes_t * stakes) {
    ulong result = 0;
    for ( fd_vote_accounts_pair_t_mapnode_t * n = fd_vote_accounts_pair_t_map_minimum( stakes->vote_accounts.vote_accounts_pool, stakes->vote_accounts.vote_accounts_root ); n; n = fd_vote_accounts_pair_t_map_successor( stakes->vote_accounts.vote_accounts_pool, n ) ) {
        result += n->elem.value.lamports;
    }

    for ( fd_delegation_pair_t_mapnode_t * n = fd_delegation_pair_t_map_minimum( stakes->stake_delegations_pool, stakes->stake_delegations_root ); n; n = fd_delegation_pair_t_map_successor( stakes->stake_delegations_pool, n ) ) {
        result += n->elem.delegation.stake;
    }

    return result;
}

static void
calculate_reward_points(
    instruction_ctx_t * ctx,
    fd_stake_history_t * stake_history,
    ulong rewards,
    fd_point_value_t * result
) {
    (void)ctx;
    (void)stake_history;
    (void)rewards;
    (void)result;
}
static void
calculate_reward_points_partitioned(
    fd_global_ctx_t * global,
    fd_stake_history_t * stake_history,
    ulong rewards,
    fd_point_value_t * result
) {
    __uint128_t points = 0;
    fd_firedancer_banks_t * bank = &global->bank;
    for ( fd_delegation_pair_t_mapnode_t * n = fd_delegation_pair_t_map_minimum( bank->stakes.stake_delegations_pool, bank->stakes.stake_delegations_root ); n; n = fd_delegation_pair_t_map_successor( bank->stakes.stake_delegations_pool, n ) ) {
        fd_pubkey_t * voter_acc = &n->elem.delegation.voter_pubkey;
        fd_pubkey_t * stake_acc = &n->elem.account;

        fd_vote_accounts_pair_t_mapnode_t key;
        fd_memcpy(&key.elem.key, voter_acc, sizeof(fd_pubkey_t));

        if (fd_vote_accounts_pair_t_map_find(bank->stakes.vote_accounts.vote_accounts_pool, bank->stakes.vote_accounts.vote_accounts_root, &key) == NULL) {
            continue;
        }

        fd_account_meta_t const * meta2 = NULL;
        uchar const *             data  = NULL;
        int read_err = fd_acc_mgr_view( global->acc_mgr, global->funk_txn, voter_acc, NULL, &meta2, &data );
        if( read_err!=0 || 0!=memcmp( &meta2->info.owner, global->solana_vote_program, sizeof(fd_pubkey_t) ) ) {
            continue;
        }

        /* Deserialize vote account */
        fd_bincode_decode_ctx_t decode = {
            .data    = data,
            .dataend = data + meta2->dlen,
            /* TODO: Make this a instruction-scoped allocator */
            .valloc  = global->valloc,
        };
        fd_vote_state_versioned_t vote_state[1] = {0};
        if( FD_UNLIKELY( 0!=fd_vote_state_versioned_decode( vote_state, &decode ) ) )
            FD_LOG_ERR(( "vote_state_versioned_decode failed" ));

        fd_account_meta_t const * stake_acc_meta = NULL;
        FD_TEST( 0==fd_acc_mgr_view( global->acc_mgr, global->funk_txn, stake_acc, NULL, &stake_acc_meta, NULL ) );

        fd_stake_state_t stake_state;
        read_stake_state( global, stake_acc_meta, &stake_state );

        __uint128_t result;
        points += (calculate_points(&stake_state, vote_state, stake_history, &result) == FD_EXECUTOR_INSTR_SUCCESS ? result : 0);

    }
    FD_LOG_NOTICE(("points: %lu", points));
    if (points > 0) {
        result->points = points;
        result->rewards = rewards;
    } else {
        result = NULL;
    }
    return;
}

// return reward info for each vote account
// return account data for each vote account that needs to be stored
// This return value is a little awkward at the moment so that downstream existing code in the non-partitioned rewards code path can be re-used without duplication or modification.
// This function is copied from the existing code path's `store_vote_accounts`.
// The primary differences:
// - we want this fn to have no side effects (such as actually storing vote accounts) so that we
//   can compare the expected results with the current code path
// - we want to be able to batch store the vote accounts later for improved performance/cache updating

/*
Calculates epoch rewards for stake/vote accounts
Returns vote rewards, stake rewards, and the sum of all stake rewards in lamports
*/
static void
calculate_stake_vote_rewards(
    fd_global_ctx_t * global,
    fd_stake_history_t * stake_history,
    ulong rewarded_epoch,
    fd_point_value_t * point_value,
    fd_validator_reward_calculation_t * result
) {
    fd_firedancer_banks_t * bank = &global->bank;
    fd_acc_lamports_t total_stake_rewards = 0;
    fd_stake_reward_t * stake_reward_deq = deq_fd_stake_reward_t_alloc( global->valloc );
    fd_vote_reward_t_mapnode_t * vote_reward_map = fd_vote_reward_t_map_alloc( global->valloc, 30);
    FD_LOG_NOTICE(("calculate_stake_vote_rewards WITHIN"));
    for ( fd_delegation_pair_t_mapnode_t * n = fd_delegation_pair_t_map_minimum( bank->stakes.stake_delegations_pool, bank->stakes.stake_delegations_root ); n; n = fd_delegation_pair_t_map_successor( bank->stakes.stake_delegations_pool, n ) ) {
        fd_pubkey_t * voter_acc = &n->elem.delegation.voter_pubkey;
        fd_pubkey_t * stake_acc = &n->elem.account;

        fd_vote_accounts_pair_t_mapnode_t key;
        fd_memcpy(&key.elem.key, voter_acc, sizeof(fd_pubkey_t));

        if (fd_vote_accounts_pair_t_map_find(bank->stakes.vote_accounts.vote_accounts_pool, bank->stakes.vote_accounts.vote_accounts_root, &key) == NULL) {
            continue;
        }

        fd_account_meta_t const * meta2 = NULL;
        uchar const *             data  = NULL;
        int read_err = fd_acc_mgr_view( global->acc_mgr, global->funk_txn, voter_acc, NULL, &meta2, &data );
        if( read_err!=0 || 0!=memcmp( &meta2->info.owner, global->solana_vote_program, sizeof(fd_pubkey_t) ) ) {
            continue;
        }

        /* Read vote account */
        fd_bincode_decode_ctx_t decode = {
            .data    = data,
            .dataend = data + meta2->dlen,
            /* TODO: Make this a instruction-scoped allocator */
            .valloc  = global->valloc,
        };
        fd_vote_state_versioned_t vote_state_versioned[1] = {0};
        if( fd_vote_state_versioned_decode( vote_state_versioned, &decode ) != 0 ) {
            continue;
        }

        fd_calculated_stake_rewards_t redeemed[1];
        if (redeem_rewards(global, stake_history, stake_acc, vote_state_versioned, rewarded_epoch, point_value, redeemed) != 0) {
            FD_LOG_WARNING(("stake_state::redeem_rewards() failed for %32J", stake_acc->key ));
            continue;
        }
        int err;
        fd_account_meta_t * metadata = (fd_account_meta_t *) fd_acc_mgr_view_raw(global->acc_mgr, global->funk_txn, stake_acc, NULL, &err);
        fd_acc_lamports_t post_lamports = metadata->info.lamports;

        // track total_stake_rewards
        total_stake_rewards += redeemed->staker_rewards;

        // add stake_reward to the collection
        fd_stake_reward_t stake_reward;
        fd_memcpy(&stake_reward.stake_pubkey, stake_acc, sizeof(fd_pubkey_t));
        uchar commission = 0U;
        switch (vote_state_versioned->discriminant) {
            case fd_vote_state_versioned_enum_current:
                commission = (uchar)vote_state_versioned->inner.current.commission;
                break;
            case fd_vote_state_versioned_enum_v0_23_5:
                commission = (uchar)vote_state_versioned->inner.v0_23_5.commission;
                break;
            case fd_vote_state_versioned_enum_v1_14_11:
                commission = (uchar)vote_state_versioned->inner.v1_14_11.commission;
                break;
            default:
                __builtin_unreachable();
        }
        stake_reward.reward_info = (fd_reward_info_t) {
            .reward_type = { .discriminant = fd_reward_type_enum_staking },
            .commission = (uchar)commission,
            .lamports = redeemed->staker_rewards,
            .post_balance = post_lamports
        };
        deq_fd_stake_reward_t_push_tail( stake_reward_deq, stake_reward );
        // track voter rewards
        fd_vote_reward_t_mapnode_t * node = fd_vote_reward_t_map_query(vote_reward_map, *voter_acc, NULL);
        if (node == NULL) {
            node = fd_vote_reward_t_map_insert(vote_reward_map, *voter_acc);
            node->vote_rewards = 0;
            fd_memcpy(&node->vote_pubkey, voter_acc, sizeof(fd_pubkey_t));
            node->commission = (uchar)commission;
        }
        node->vote_rewards = fd_ulong_sat_add(node->vote_rewards, redeemed->voter_rewards);
    } // end of for
    *result = (fd_validator_reward_calculation_t) {
        .total_stake_rewards_lamports = total_stake_rewards,
        .stake_reward_deq = stake_reward_deq,
        .vote_reward_map = vote_reward_map
    };
}

/* Calculate epoch reward and return vote and stake rewards. */
static void
calculate_validator_rewards(
    fd_global_ctx_t * global,
    ulong rewarded_epoch,
    ulong rewards,
    fd_validator_reward_calculation_t * result
) {
    fd_stake_history_t stake_history;
    fd_sysvar_stake_history_read( global, &stake_history);

    fd_point_value_t point_value_result[1] = {0};
    calculate_reward_points_partitioned(global, &stake_history, rewards, point_value_result);
    FD_LOG_NOTICE(("calculate_validator_rewards: point_value_result->points = %lu", point_value_result->points));
    FD_LOG_NOTICE(("calculate_validator_rewards: point_value_result->rewards = %lu", point_value_result->rewards));
    calculate_stake_vote_rewards(global, &stake_history, rewarded_epoch, point_value_result, result);
}


/// Calculate the number of blocks required to distribute rewards to all stake accounts.
// fn get_reward_distribution_num_blocks(&self, rewards: &StakeRewards) -> u64 {
static ulong
get_reward_distribution_num_blocks(
    fd_firedancer_banks_t * bank,
    fd_stake_reward_t * stake_reward_deq
) {
    if (bank->epoch_schedule.warmup && fd_slot_to_epoch(&bank->epoch_schedule, bank->slot, NULL) < bank->epoch_schedule.first_normal_epoch) {
        return 1;
    }
    ulong total_stake_accounts = deq_fd_stake_reward_t_cnt(stake_reward_deq);
    ulong num_chunks = total_stake_accounts / (ulong)STAKE_ACCOUNT_STORES_PER_BLOCK + (total_stake_accounts % STAKE_ACCOUNT_STORES_PER_BLOCK != 0);
    num_chunks = fd_ulong_max(num_chunks, 1);
    num_chunks = fd_ulong_min(
        fd_ulong_max(
            bank->epoch_schedule.slots_per_epoch / (ulong)MAX_FACTOR_OF_REWARD_BLOCKS_IN_EPOCH,
            1),
        1);
    return num_chunks;
}

static void
hash_rewards_into_partitions(
    fd_firedancer_banks_t * bank,
    fd_stake_reward_t * stake_reward_deq,
    ulong num_partitions,
    fd_stake_rewards_vector_t * result
) {
    fd_siphash13_t  _sip[1] = {0};
    fd_siphash13_t * hasher = fd_siphash13_init( _sip, 0UL, 0UL );
    hasher = fd_siphash13_append( hasher, bank->banks_hash.hash, sizeof(fd_hash_t));

    fd_stake_rewards_vector_new( result );
    for (ulong i = 0; i < num_partitions; ++i) {
        fd_stake_rewards_t new_partition;
        fd_stake_rewards_new(&new_partition);
        fd_stake_rewards_vector_push( result, new_partition);
    }
    for (
        deq_fd_stake_reward_t_iter_t iter = deq_fd_stake_reward_t_iter_init(stake_reward_deq );
        !deq_fd_stake_reward_t_iter_done( stake_reward_deq, iter );
        iter =  deq_fd_stake_reward_t_iter_next( stake_reward_deq, iter)
    ) {
        fd_stake_reward_t * ele =  deq_fd_stake_reward_t_iter_ele( stake_reward_deq, iter );
        /* hash_address_to_partition: find partition index (0..partitions) by hashing `address` with the `hasher` */
        fd_siphash13_append( hasher, (const uchar *) ele->stake_pubkey.key, sizeof(fd_pubkey_t));
        ulong hash64 = fd_siphash13_fini(hasher);
        /* hash_to_partition */
        ulong partition_index = (ulong)(
            (__uint128_t) num_partitions *
            (__uint128_t) hash64 /
            ((__uint128_t)ULONG_MAX + 1)
        );
        FD_LOG_NOTICE(("partition idx={%lu}", partition_index));
        fd_stake_rewards_push(&result->elems[partition_index], ele);
    }
}

// Calculate rewards from previous epoch to prepare for partitioned distribution.
void
calculate_rewards_for_partitioning(
    fd_global_ctx_t * global,
    ulong prev_epoch,
    fd_partitioned_rewards_calculation_t * result
) {
    prev_epoch_inflation_rewards_t rewards;
    fd_firedancer_banks_t * bank = &global->bank;
    calculate_previous_epoch_inflation_rewards(bank, bank->capitalization, prev_epoch, &rewards);

    ulong old_vote_balance_and_staked = vote_balance_and_staked(&bank->stakes);

    fd_validator_reward_calculation_t validator_result[1] = {0};
    calculate_validator_rewards(global, prev_epoch, rewards.validator_rewards, validator_result);
    FD_LOG_NOTICE(("calculate_rewards_for_partitioning: total_stake_rewards_lamports = %lu", validator_result->total_stake_rewards_lamports));

    ulong num_partitions = get_reward_distribution_num_blocks(&global->bank, validator_result->stake_reward_deq);
    FD_LOG_NOTICE(("calculate_rewards_for_partitioning: num_partitions = %lu", num_partitions));

    fd_stake_rewards_vector_t hash_rewards_result[1] = {0};
    hash_rewards_into_partitions(&global->bank, validator_result->stake_reward_deq, num_partitions, hash_rewards_result);
    *result = (fd_partitioned_rewards_calculation_t) {
        .vote_account_rewards = validator_result->vote_reward_map,
        .stake_rewards_by_partition = hash_rewards_result,
        .total_stake_rewards_lamports = validator_result->total_stake_rewards_lamports,
        .old_vote_balance_and_staked = old_vote_balance_and_staked,
        .validator_rewards = rewards.validator_rewards,
        .validator_rate = rewards.validator_rate,
        .foundation_rate = rewards.foundation_rate,
        .prev_epoch_duration_in_years = rewards.prev_epoch_duration_in_years,
        .capitalization = bank->capitalization
    };
}

static void
update_reward_history(
    fd_firedancer_banks_t * bank,
    fd_stake_rewards_t * stake_rewards,
    fd_vote_reward_t_mapnode_t * vote_reward_map
) {
    (void) bank;
    (void) stake_rewards;
    (void) vote_reward_map;
    // let additional_reserve = stake_rewards.len() + vote_rewards.len();
    // let mut rewards = self.rewards.write().unwrap();
    // rewards.reserve(additional_reserve);
    // rewards.append(&mut vote_rewards);
    // stake_rewards
    //     .into_iter()
    //     .filter(|x| x.get_stake_reward() > 0)
    //     .for_each(|x| rewards.push((x.stake_pubkey, x.stake_reward_info)));
    return;
}
// Calculate rewards from previous epoch and distribute vote rewards
void calculate_rewards_and_distribute_vote_rewards(
    fd_firedancer_banks_t * self,
    fd_global_ctx_t * global,
    ulong prev_epoch,
    fd_calculate_rewards_and_distribute_vote_rewards_result_t * result
) {
    fd_partitioned_rewards_calculation_t rewards_calc_result[1] = {0};
    calculate_rewards_for_partitioning(global, prev_epoch,  rewards_calc_result);
    FD_LOG_NOTICE((
        "calculate_rewards_and_distribute_vote_rewards: %lu, %lu, %lu",
        rewards_calc_result->total_stake_rewards_lamports,
        rewards_calc_result->old_vote_balance_and_staked,
        rewards_calc_result->validator_rewards
    ));
    /* TODO: update_reward_history */
    update_reward_history(self, NULL, rewards_calc_result->vote_account_rewards);

    // This is for vote rewards only.
    ulong new_vote_balance_and_staked = vote_balance_and_staked(&self->stakes);
    ulong validator_rewards_paid = fd_ulong_sat_sub(new_vote_balance_and_staked, rewards_calc_result->old_vote_balance_and_staked);

    // verify that we didn't pay any more than we expected to
    FD_TEST( rewards_calc_result->validator_rewards >= fd_ulong_sat_add(validator_rewards_paid, rewards_calc_result->total_stake_rewards_lamports));

    FD_LOG_NOTICE((
        "distributed vote rewards: %lu out of %lu, remaining %lu",
        validator_rewards_paid,
        rewards_calc_result->validator_rewards,
        rewards_calc_result->total_stake_rewards_lamports
    ));

    self->capitalization += validator_rewards_paid;

    /*
    // only useful for logging
    ulong active_stake = 0;
    for ( fd_stake_history_epochentry_pair_t_mapnode_t * n = fd_stake_history_epochentry_pair_t_map_minimum( bank->stakes.stake_history.entries_pool, bank->stakes.stake_history.entries_root ); n; n = fd_stake_history_epochentry_pair_t_map_successor( bank->stakes.stake_history.entries_pool, n ) ) {
        if (bank->stakes.stake_history.entries_pool->elem.epoch == prev_epoch) {
            active_stake = bank->stakes.stake_history.entries_pool->elem.entry.effective;
            break;
        }
    }
    */
    result->total_rewards = fd_ulong_sat_add(validator_rewards_paid,  rewards_calc_result->total_stake_rewards_lamports);
    result->distributed_rewards = validator_rewards_paid;
    result->stake_rewards_by_partition = rewards_calc_result->stake_rewards_by_partition;
}

// pay_validator_rewards_with_thread_pool
/* Load, calculate and payout epoch rewards for stake and vote accounts */
void
pay_validator_rewards(
    instruction_ctx_t * ctx,
    ulong rewarded_epoch,
    ulong rewards
) {
    fd_stake_history_t stake_history;
    fd_sysvar_stake_history_read( ctx->global, &stake_history);

    fd_point_value_t *point_value_result = NULL;
    calculate_reward_points(ctx, &stake_history, rewards, point_value_result);
    (void) rewarded_epoch;
    // redeem_rewards(ctx, &stake_history, fd_pubkey_t *stake_acc, fd_vote_state_versioned_t *vote_state, ulong rewarded_epoch, point_value_result, fd_calculated_stake_rewards_t *result);
}

// update rewards based on the previous epoch
// no thread pool version below
void
update_rewards(
    fd_global_ctx_t * global,
    ulong prev_epoch
) {
    (void) global;
    (void) prev_epoch;
}

// begin_partitioned_rewards
/* Begin the process of calculating and distributing rewards. This process can take multiple slots. */
void
begin_partitioned_rewards(
    fd_firedancer_banks_t * self,
    fd_global_ctx_t * global,
    ulong parent_epoch,
    fd_epoch_reward_status_t * result
) {
    fd_calculate_rewards_and_distribute_vote_rewards_result_t rewards_result[1] = {0};
    calculate_rewards_and_distribute_vote_rewards(
        self,
        global,
        parent_epoch,
        rewards_result
    );
    ulong credit_end_exclusive = self->block_height + REWARD_CALCULATION_NUM_BLOCK + rewards_result->stake_rewards_by_partition->cnt;

    // self.set_epoch_reward_status_active(stake_rewards_by_partition);
    result->is_active = 1;
    result->stake_rewards_by_partition = rewards_result->stake_rewards_by_partition;
    result->start_block_height = self->block_height;
    FD_LOG_NOTICE((
        "begin_partitioned_rewards: %lu, %lu, %lu",
        result->start_block_height,
        credit_end_exclusive,
        rewards_result->total_rewards
    ));
    // create EpochRewards sysvar that holds the balance of undistributed rewards with
    // (total_rewards, distributed_rewards, credit_end_exclusive), total capital will increase by (total_rewards - distributed_rewards)
    fd_sysvar_epoch_rewards_init( global, rewards_result->total_rewards, rewards_result->distributed_rewards, credit_end_exclusive);
}

/* Process reward distribution for the block if it is inside reward interval. */
void
distribute_partitioned_epoch_rewards(
    fd_firedancer_banks_t * self,
    fd_global_ctx_t * global,
    fd_epoch_reward_status_t * epoch_reward_status
) {
    /* make sure we are inside the reward interval */
    if ( !epoch_reward_status->is_active ) {
        return;
    }

    ulong credit_start = epoch_reward_status->start_block_height + REWARD_CALCULATION_NUM_BLOCK;
    ulong credit_end_exclusive = credit_start + epoch_reward_status->stake_rewards_by_partition->cnt;
    if (self->block_height >= credit_start && self->block_height < credit_end_exclusive) {
        ulong partition_index = self->block_height - credit_start;
        ulong total_rewards_in_lamports = 0UL;
        fd_stake_rewards_t this_partition_stake_rewards = epoch_reward_status->stake_rewards_by_partition->elems[partition_index];
        for (uint i = 0; i < this_partition_stake_rewards.cnt; ++i) {
            total_rewards_in_lamports = fd_ulong_sat_add(total_rewards_in_lamports, this_partition_stake_rewards.elems[i]->reward_info.lamports);
            // store rewards into accounts
            fd_account_meta_t * acc_meta = NULL;
            FD_TEST( 0==fd_acc_mgr_modify( global->acc_mgr, global->funk_txn, &this_partition_stake_rewards.elems[i]->stake_pubkey, 0, 0UL, NULL, NULL, &acc_meta, NULL ));
            acc_meta->info.lamports += this_partition_stake_rewards.elems[i]->reward_info.lamports;
        }

        // increase total capitalization by the distributed rewards
        self->capitalization = fd_ulong_sat_add(self->capitalization, total_rewards_in_lamports);

        // decrease distributed capital from epoch rewards sysvar
        fd_sysvar_epoch_rewards_update( global, total_rewards_in_lamports );

        // update reward history for this partitioned distribution
        // self.update_reward_history_in_partition(this_partition_stake_rewards);
    }

    if ( fd_ulong_sat_sub(self->block_height, 1) >= credit_end_exclusive ) {
        // deactivate epoch reward status
        epoch_reward_status->is_active = 0;
    }

}
