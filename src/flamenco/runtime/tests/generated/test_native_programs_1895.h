#include "../fd_tests.h"
int test_1895(fd_executor_test_suite_t *suite) {
  fd_executor_test_t test;
  fd_memset( &test, 0, FD_EXECUTOR_TEST_FOOTPRINT );
  test.disable_cnt = 1;
  test.bt = "   2: solana_stake_program::stake_instruction::tests::test_split_100_percent_of_source_to_account_with_lamports             at ./src/stake_instruction.rs:5546:28   3: solana_stake_program::stake_instruction::tests::test_split_100_percent_of_source_to_account_with_lamports::old_warmup_cooldown             at ./src/stake_instruction.rs:5485:5   4: solana_stake_program::stake_instruction::tests::test_split_100_percent_of_source_to_account_with_lamports::old_warmup_cooldown::{{closure}}             at ./src/stake_instruction.rs:5485:5   5: core::ops::function::FnOnce::call_once             at /rustc/84c898d65adf2f39a5a98507f1fe0ce10a2b8dbc/library/core/src/ops/function.rs:250:5";
  test.test_name = "stake_instruction::tests::test_split_100_percent_of_source_to_account_with_lamports::old_warmup_cooldown";
  test.test_number = 1895;
  test.sysvar_cache.clock = "";
  test.sysvar_cache.epoch_schedule = "";
  test.sysvar_cache.epoch_rewards = "";
  test.sysvar_cache.fees = "";
  test.sysvar_cache.rent = "mA0AAAAAAAAAAAAAAAAAQDI=";
  test.sysvar_cache.slot_hashes = "";
  test.sysvar_cache.stake_history = "";
  test.sysvar_cache.slot_history = "";
  if (fd_executor_test_suite_check_filter(suite, &test)) return -9999;
  ulong test_accs_len = 3;
  fd_executor_test_acc_t* test_accs = fd_alloca( 1UL, FD_EXECUTOR_TEST_ACC_FOOTPRINT * test_accs_len );
  fd_memset( test_accs, 0, FD_EXECUTOR_TEST_ACC_FOOTPRINT * test_accs_len );


  uchar disabled_features[] = { 160 };
  test.disable_feature = disabled_features;
            
 // {'clock': '', 'epoch_schedule': '', 'epoch_rewards': '', 'fees': '', 'rent': 'mA0AAAAAAAAAAAAAAAAAQDI=', 'slot_hashes': '', 'recent_blockhashes': '', 'stake_history': '', 'last_restart_slot': ''}
  fd_executor_test_acc_t* test_acc = test_accs;
  fd_base58_decode_32( "7bxy69Uj2tomyb2z5XotPch28bDaXVk3tR9jwH42y2ep",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "Stake11111111111111111111111111111111111111",  (uchar *) &test_acc->owner);
  fd_base58_decode_32( "Stake11111111111111111111111111111111111111",  (uchar *) &test_acc->result_owner);
  test_acc->lamports        = 1002282880UL;
  test_acc->result_lamports = 0UL;
  test_acc->executable      = 0;
  test_acc->result_executable= 0;
  test_acc->rent_epoch      = 0;
  test_acc->result_rent_epoch      = 0;
  static uchar const fd_flamenco_native_prog_test_1895_acc_0_data[] = { 0x02,0x00,0x00,0x00,0x80,0xd5,0x22,0x00,0x00,0x00,0x00,0x00,0x62,0x1b,0x26,0xb5,0x99,0x47,0xc2,0x7f,0xc5,0x23,0x03,0x38,0xc0,0x98,0x03,0xd4,0x73,0x41,0x2c,0x78,0xd8,0x07,0x1a,0x52,0x0e,0xd7,0x7e,0x67,0x4f,0x71,0x09,0x65,0x62,0x1b,0x26,0xb5,0x99,0x47,0xc2,0x7f,0xc5,0x23,0x03,0x38,0xc0,0x98,0x03,0xd4,0x73,0x41,0x2c,0x78,0xd8,0x07,0x1a,0x52,0x0e,0xd7,0x7e,0x67,0x4f,0x71,0x09,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xca,0x9a,0x3b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xd0,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->data            = fd_flamenco_native_prog_test_1895_acc_0_data;
  test_acc->data_len        = 200UL;
  static uchar const fd_flamenco_native_prog_test_1895_acc_0_post_data[] = { 0x00,0x00,0x00,0x00,0x80,0xd5,0x22,0x00,0x00,0x00,0x00,0x00,0x62,0x1b,0x26,0xb5,0x99,0x47,0xc2,0x7f,0xc5,0x23,0x03,0x38,0xc0,0x98,0x03,0xd4,0x73,0x41,0x2c,0x78,0xd8,0x07,0x1a,0x52,0x0e,0xd7,0x7e,0x67,0x4f,0x71,0x09,0x65,0x62,0x1b,0x26,0xb5,0x99,0x47,0xc2,0x7f,0xc5,0x23,0x03,0x38,0xc0,0x98,0x03,0xd4,0x73,0x41,0x2c,0x78,0xd8,0x07,0x1a,0x52,0x0e,0xd7,0x7e,0x67,0x4f,0x71,0x09,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xd0,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->result_data     = fd_flamenco_native_prog_test_1895_acc_0_post_data;
  test_acc->result_data_len = 200UL;
  test_acc++;
  fd_base58_decode_32( "3h54LYH7V5JRPBXw3Cw5HAgnvnn2iBAYW4N6hgjyXghw",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "Stake11111111111111111111111111111111111111",  (uchar *) &test_acc->owner);
  fd_base58_decode_32( "Stake11111111111111111111111111111111111111",  (uchar *) &test_acc->result_owner);
  test_acc->lamports        = 1002282880UL;
  test_acc->result_lamports = 2004565760UL;
  test_acc->executable      = 0;
  test_acc->result_executable= 0;
  test_acc->rent_epoch      = 0;
  test_acc->result_rent_epoch      = 0;
  static uchar const fd_flamenco_native_prog_test_1895_acc_1_data[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->data            = fd_flamenco_native_prog_test_1895_acc_1_data;
  test_acc->data_len        = 200UL;
  static uchar const fd_flamenco_native_prog_test_1895_acc_1_post_data[] = { 0x02,0x00,0x00,0x00,0x80,0xd5,0x22,0x00,0x00,0x00,0x00,0x00,0x62,0x1b,0x26,0xb5,0x99,0x47,0xc2,0x7f,0xc5,0x23,0x03,0x38,0xc0,0x98,0x03,0xd4,0x73,0x41,0x2c,0x78,0xd8,0x07,0x1a,0x52,0x0e,0xd7,0x7e,0x67,0x4f,0x71,0x09,0x65,0x62,0x1b,0x26,0xb5,0x99,0x47,0xc2,0x7f,0xc5,0x23,0x03,0x38,0xc0,0x98,0x03,0xd4,0x73,0x41,0x2c,0x78,0xd8,0x07,0x1a,0x52,0x0e,0xd7,0x7e,0x67,0x4f,0x71,0x09,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xca,0x9a,0x3b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xd0,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->result_data     = fd_flamenco_native_prog_test_1895_acc_1_post_data;
  test_acc->result_data_len = 200UL;
  test_acc++;
  fd_base58_decode_32( "SysvarRent111111111111111111111111111111111",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "Sysvar1111111111111111111111111111111111111",  (uchar *) &test_acc->owner);
  fd_base58_decode_32( "Sysvar1111111111111111111111111111111111111",  (uchar *) &test_acc->result_owner);
  test_acc->lamports        = 1UL;
  test_acc->result_lamports = 1UL;
  test_acc->executable      = 0;
  test_acc->result_executable= 0;
  test_acc->rent_epoch      = 0;
  test_acc->result_rent_epoch      = 0;
  static uchar const fd_flamenco_native_prog_test_1895_acc_2_data[] = { 0x98,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x32 };
  test_acc->data            = fd_flamenco_native_prog_test_1895_acc_2_data;
  test_acc->data_len        = 17UL;
  static uchar const fd_flamenco_native_prog_test_1895_acc_2_post_data[] = { 0x98,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x32 };
  test_acc->result_data     = fd_flamenco_native_prog_test_1895_acc_2_post_data;
  test_acc->result_data_len = 17UL;
  test_acc++;
  fd_base58_decode_32( "Stake11111111111111111111111111111111111111",  (unsigned char *) &test.program_id);
  static uchar const fd_flamenco_native_prog_test_1895_raw[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x03,0x62,0x1b,0x26,0xb5,0x99,0x47,0xc2,0x7f,0xc5,0x23,0x03,0x38,0xc0,0x98,0x03,0xd4,0x73,0x41,0x2c,0x78,0xd8,0x07,0x1a,0x52,0x0e,0xd7,0x7e,0x67,0x4f,0x71,0x09,0x65,0x27,0xfb,0x31,0xaf,0x60,0xda,0xd4,0x8e,0x3d,0x25,0x4b,0xb7,0x42,0x05,0xf6,0x76,0x11,0x8d,0xbf,0x93,0x7e,0xec,0x3a,0xb4,0x62,0xe3,0xee,0xd8,0xa4,0x1d,0xa4,0xf2,0x06,0xa1,0xd8,0x17,0x91,0x37,0x54,0x2a,0x98,0x34,0x37,0xbd,0xfe,0x2a,0x7a,0xb2,0x55,0x7f,0x53,0x5c,0x8a,0x78,0x72,0x2b,0x68,0xa4,0x9d,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x02,0x00,0x01,0x0c,0x03,0x00,0x00,0x00,0x80,0x9f,0xbd,0x3b,0x00,0x00,0x00,0x00 };
  test.raw_tx = fd_flamenco_native_prog_test_1895_raw;
  test.raw_tx_len = 215UL;
  test.expected_result = 0;
  test.custom_err = 0;

  test.accs_len = test_accs_len;
  test.accs = test_accs;

  return fd_executor_run_test( &test, suite );
}
