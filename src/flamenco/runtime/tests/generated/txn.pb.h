/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.9-dev */

#ifndef PB_ORG_SOLANA_SEALEVEL_V1_TXN_PB_H_INCLUDED
#define PB_ORG_SOLANA_SEALEVEL_V1_TXN_PB_H_INCLUDED

#include "../../../nanopb/pb_firedancer.h"
#include "context.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
/* Message header contains the counts of required readonly and signatures */
typedef struct fd_exec_test_message_header {
    uint32_t num_required_signatures;
    uint32_t num_readonly_signed_accounts;
    uint32_t num_readonly_unsigned_accounts;
} fd_exec_test_message_header_t;

/* The instruction a transaction executes */
typedef struct fd_exec_test_compiled_instruction {
    /* Index into the message pubkey array */
    uint32_t program_id_index;
    /* Indexes into the message pubkey array */
    pb_size_t accounts_count;
    uint32_t *accounts;
    pb_bytes_array_t *data;
} fd_exec_test_compiled_instruction_t;

/* List of address table lookups used to load additional accounts for a transaction */
typedef struct fd_exec_test_message_address_table_lookup {
    pb_byte_t account_key[32];
    pb_size_t writable_indexes_count;
    uint32_t *writable_indexes;
    pb_size_t readonly_indexes_count;
    uint32_t *readonly_indexes;
} fd_exec_test_message_address_table_lookup_t;

/* Addresses loaded with on-chain lookup tables */
typedef struct fd_exec_test_loaded_addresses {
    pb_callback_t writable;
    pb_callback_t readonly;
} fd_exec_test_loaded_addresses_t;

/* Message contains the transaction data */
typedef struct fd_exec_test_transaction_message {
    /* Whether this is a legacy message or not */
    bool is_legacy;
    bool has_header;
    fd_exec_test_message_header_t header;
    /* Vector of pubkeys */
    pb_size_t account_keys_count;
    pb_bytes_array_t **account_keys;
    /* Data associated with the accounts referred above. Not all accounts need to be here. */
    pb_size_t account_shared_data_count;
    struct fd_exec_test_acct_state *account_shared_data;
    /* The instructions this transaction executes */
    pb_size_t instructions_count;
    struct fd_exec_test_compiled_instruction *instructions;
    /* Not available in legacy message */
    pb_size_t address_table_lookups_count;
    struct fd_exec_test_message_address_table_lookup *address_table_lookups;
    /* Not available in legacy messages */
    bool has_loaded_addresses;
    fd_exec_test_loaded_addresses_t loaded_addresses;
} fd_exec_test_transaction_message_t;

/* A valid verified transaction */
typedef struct fd_exec_test_sanitized_transaction {
    /* The transaction information */
    bool has_message;
    fd_exec_test_transaction_message_t message;
    /* The message hash */
    pb_bytes_array_t *message_hash;
    /* Is this a voting transaction? */
    bool is_simple_vote_tx;
    /* The signatures needed in the transaction */
    pb_size_t signatures_count;
    pb_bytes_array_t **signatures;
} fd_exec_test_sanitized_transaction_t;

/* This Transaction context be used to fuzz either `load_execute_and_commit_transactions`,
 `load_and_execute_transactions` in `bank.rs` or `load_and_execute_sanitized_transactions`
 in `svm/transaction_processor.rs` */
typedef struct fd_exec_test_txn_context {
    /* The transaction data */
    bool has_tx;
    fd_exec_test_sanitized_transaction_t tx;
    /* The maximum age allowed for this transaction */
    uint64_t max_age;
    /* The limit of bytes allowed for this transaction to load */
    uint64_t log_messages_byte_limit;
    bool has_epoch_ctx;
    fd_exec_test_epoch_context_t epoch_ctx;
    bool has_slot_ctx;
    fd_exec_test_slot_context_t slot_ctx;
} fd_exec_test_txn_context_t;

/* The resulting state of an account after a transaction */
typedef struct fd_exec_test_resulting_state {
    pb_size_t acct_states_count;
    struct fd_exec_test_acct_state *acct_states;
    pb_size_t rent_debits_count;
    struct fd_exec_test_rent_debits *rent_debits;
    uint64_t transaction_rent;
} fd_exec_test_resulting_state_t;

/* The rent state for an account after a transaction */
typedef struct fd_exec_test_rent_debits {
    pb_byte_t pubkey[32];
    int64_t rent_collected;
} fd_exec_test_rent_debits_t;

/* The execution results for a transaction */
typedef struct fd_exec_test_txn_result {
    /* Whether this transaction was executed */
    bool executed;
    /* Whether there was a sanitization error */
    bool sanitization_error;
    /* The state of each account after the transaction */
    bool has_resulting_state;
    fd_exec_test_resulting_state_t resulting_state;
    uint64_t rent;
    /* If an executed transaction has no error */
    bool is_ok;
    /* The transaction status (error code) */
    uint32_t status;
    /* The return data from this transaction, if any */
    pb_bytes_array_t *return_data;
    /* Number of executed compute units */
    uint64_t executed_units;
    /* The change in accounts data len for this transaction */
    int64_t accounts_data_len_delta;
} fd_exec_test_txn_result_t;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define FD_EXEC_TEST_MESSAGE_HEADER_INIT_DEFAULT {0, 0, 0}
#define FD_EXEC_TEST_COMPILED_INSTRUCTION_INIT_DEFAULT {0, 0, NULL, NULL}
#define FD_EXEC_TEST_MESSAGE_ADDRESS_TABLE_LOOKUP_INIT_DEFAULT {{0}, 0, NULL, 0, NULL}
#define FD_EXEC_TEST_LOADED_ADDRESSES_INIT_DEFAULT {{{NULL}, NULL}, {{NULL}, NULL}}
#define FD_EXEC_TEST_TRANSACTION_MESSAGE_INIT_DEFAULT {0, false, FD_EXEC_TEST_MESSAGE_HEADER_INIT_DEFAULT, 0, NULL, 0, NULL, 0, NULL, 0, NULL, false, FD_EXEC_TEST_LOADED_ADDRESSES_INIT_DEFAULT}
#define FD_EXEC_TEST_SANITIZED_TRANSACTION_INIT_DEFAULT {false, FD_EXEC_TEST_TRANSACTION_MESSAGE_INIT_DEFAULT, NULL, 0, 0, NULL}
#define FD_EXEC_TEST_TXN_CONTEXT_INIT_DEFAULT    {false, FD_EXEC_TEST_SANITIZED_TRANSACTION_INIT_DEFAULT, 0, 0, false, FD_EXEC_TEST_EPOCH_CONTEXT_INIT_DEFAULT, false, FD_EXEC_TEST_SLOT_CONTEXT_INIT_DEFAULT}
#define FD_EXEC_TEST_RESULTING_STATE_INIT_DEFAULT {0, NULL, 0, NULL, 0}
#define FD_EXEC_TEST_RENT_DEBITS_INIT_DEFAULT    {{0}, 0}
#define FD_EXEC_TEST_TXN_RESULT_INIT_DEFAULT     {0, 0, false, FD_EXEC_TEST_RESULTING_STATE_INIT_DEFAULT, 0, 0, 0, NULL, 0, 0}
#define FD_EXEC_TEST_MESSAGE_HEADER_INIT_ZERO    {0, 0, 0}
#define FD_EXEC_TEST_COMPILED_INSTRUCTION_INIT_ZERO {0, 0, NULL, NULL}
#define FD_EXEC_TEST_MESSAGE_ADDRESS_TABLE_LOOKUP_INIT_ZERO {{0}, 0, NULL, 0, NULL}
#define FD_EXEC_TEST_LOADED_ADDRESSES_INIT_ZERO  {{{NULL}, NULL}, {{NULL}, NULL}}
#define FD_EXEC_TEST_TRANSACTION_MESSAGE_INIT_ZERO {0, false, FD_EXEC_TEST_MESSAGE_HEADER_INIT_ZERO, 0, NULL, 0, NULL, 0, NULL, 0, NULL, false, FD_EXEC_TEST_LOADED_ADDRESSES_INIT_ZERO}
#define FD_EXEC_TEST_SANITIZED_TRANSACTION_INIT_ZERO {false, FD_EXEC_TEST_TRANSACTION_MESSAGE_INIT_ZERO, NULL, 0, 0, NULL}
#define FD_EXEC_TEST_TXN_CONTEXT_INIT_ZERO       {false, FD_EXEC_TEST_SANITIZED_TRANSACTION_INIT_ZERO, 0, 0, false, FD_EXEC_TEST_EPOCH_CONTEXT_INIT_ZERO, false, FD_EXEC_TEST_SLOT_CONTEXT_INIT_ZERO}
#define FD_EXEC_TEST_RESULTING_STATE_INIT_ZERO   {0, NULL, 0, NULL, 0}
#define FD_EXEC_TEST_RENT_DEBITS_INIT_ZERO       {{0}, 0}
#define FD_EXEC_TEST_TXN_RESULT_INIT_ZERO        {0, 0, false, FD_EXEC_TEST_RESULTING_STATE_INIT_ZERO, 0, 0, 0, NULL, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define FD_EXEC_TEST_MESSAGE_HEADER_NUM_REQUIRED_SIGNATURES_TAG 1
#define FD_EXEC_TEST_MESSAGE_HEADER_NUM_READONLY_SIGNED_ACCOUNTS_TAG 2
#define FD_EXEC_TEST_MESSAGE_HEADER_NUM_READONLY_UNSIGNED_ACCOUNTS_TAG 3
#define FD_EXEC_TEST_COMPILED_INSTRUCTION_PROGRAM_ID_INDEX_TAG 1
#define FD_EXEC_TEST_COMPILED_INSTRUCTION_ACCOUNTS_TAG 2
#define FD_EXEC_TEST_COMPILED_INSTRUCTION_DATA_TAG 3
#define FD_EXEC_TEST_MESSAGE_ADDRESS_TABLE_LOOKUP_ACCOUNT_KEY_TAG 1
#define FD_EXEC_TEST_MESSAGE_ADDRESS_TABLE_LOOKUP_WRITABLE_INDEXES_TAG 2
#define FD_EXEC_TEST_MESSAGE_ADDRESS_TABLE_LOOKUP_READONLY_INDEXES_TAG 3
#define FD_EXEC_TEST_LOADED_ADDRESSES_WRITABLE_TAG 1
#define FD_EXEC_TEST_LOADED_ADDRESSES_READONLY_TAG 2
#define FD_EXEC_TEST_TRANSACTION_MESSAGE_IS_LEGACY_TAG 1
#define FD_EXEC_TEST_TRANSACTION_MESSAGE_HEADER_TAG 2
#define FD_EXEC_TEST_TRANSACTION_MESSAGE_ACCOUNT_KEYS_TAG 3
#define FD_EXEC_TEST_TRANSACTION_MESSAGE_ACCOUNT_SHARED_DATA_TAG 4
#define FD_EXEC_TEST_TRANSACTION_MESSAGE_INSTRUCTIONS_TAG 5
#define FD_EXEC_TEST_TRANSACTION_MESSAGE_ADDRESS_TABLE_LOOKUPS_TAG 6
#define FD_EXEC_TEST_TRANSACTION_MESSAGE_LOADED_ADDRESSES_TAG 7
#define FD_EXEC_TEST_SANITIZED_TRANSACTION_MESSAGE_TAG 1
#define FD_EXEC_TEST_SANITIZED_TRANSACTION_MESSAGE_HASH_TAG 2
#define FD_EXEC_TEST_SANITIZED_TRANSACTION_IS_SIMPLE_VOTE_TX_TAG 3
#define FD_EXEC_TEST_SANITIZED_TRANSACTION_SIGNATURES_TAG 4
#define FD_EXEC_TEST_TXN_CONTEXT_TX_TAG          1
#define FD_EXEC_TEST_TXN_CONTEXT_MAX_AGE_TAG     2
#define FD_EXEC_TEST_TXN_CONTEXT_LOG_MESSAGES_BYTE_LIMIT_TAG 3
#define FD_EXEC_TEST_TXN_CONTEXT_EPOCH_CTX_TAG   4
#define FD_EXEC_TEST_TXN_CONTEXT_SLOT_CTX_TAG    5
#define FD_EXEC_TEST_RESULTING_STATE_ACCT_STATES_TAG 1
#define FD_EXEC_TEST_RESULTING_STATE_RENT_DEBITS_TAG 2
#define FD_EXEC_TEST_RESULTING_STATE_TRANSACTION_RENT_TAG 3
#define FD_EXEC_TEST_RENT_DEBITS_PUBKEY_TAG      1
#define FD_EXEC_TEST_RENT_DEBITS_RENT_COLLECTED_TAG 2
#define FD_EXEC_TEST_TXN_RESULT_EXECUTED_TAG     1
#define FD_EXEC_TEST_TXN_RESULT_SANITIZATION_ERROR_TAG 2
#define FD_EXEC_TEST_TXN_RESULT_RESULTING_STATE_TAG 3
#define FD_EXEC_TEST_TXN_RESULT_RENT_TAG         4
#define FD_EXEC_TEST_TXN_RESULT_IS_OK_TAG        5
#define FD_EXEC_TEST_TXN_RESULT_STATUS_TAG       6
#define FD_EXEC_TEST_TXN_RESULT_RETURN_DATA_TAG  7
#define FD_EXEC_TEST_TXN_RESULT_EXECUTED_UNITS_TAG 8
#define FD_EXEC_TEST_TXN_RESULT_ACCOUNTS_DATA_LEN_DELTA_TAG 9

/* Struct field encoding specification for nanopb */
#define FD_EXEC_TEST_MESSAGE_HEADER_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   num_required_signatures,   1) \
X(a, STATIC,   SINGULAR, UINT32,   num_readonly_signed_accounts,   2) \
X(a, STATIC,   SINGULAR, UINT32,   num_readonly_unsigned_accounts,   3)
#define FD_EXEC_TEST_MESSAGE_HEADER_CALLBACK NULL
#define FD_EXEC_TEST_MESSAGE_HEADER_DEFAULT NULL

#define FD_EXEC_TEST_COMPILED_INSTRUCTION_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   program_id_index,   1) \
X(a, POINTER,  REPEATED, UINT32,   accounts,          2) \
X(a, POINTER,  SINGULAR, BYTES,    data,              3)
#define FD_EXEC_TEST_COMPILED_INSTRUCTION_CALLBACK NULL
#define FD_EXEC_TEST_COMPILED_INSTRUCTION_DEFAULT NULL

#define FD_EXEC_TEST_MESSAGE_ADDRESS_TABLE_LOOKUP_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FIXED_LENGTH_BYTES, account_key,       1) \
X(a, POINTER,  REPEATED, UINT32,   writable_indexes,   2) \
X(a, POINTER,  REPEATED, UINT32,   readonly_indexes,   3)
#define FD_EXEC_TEST_MESSAGE_ADDRESS_TABLE_LOOKUP_CALLBACK NULL
#define FD_EXEC_TEST_MESSAGE_ADDRESS_TABLE_LOOKUP_DEFAULT NULL

#define FD_EXEC_TEST_LOADED_ADDRESSES_FIELDLIST(X, a) \
X(a, CALLBACK, REPEATED, FIXED_LENGTH_BYTES, writable,          1) \
X(a, CALLBACK, REPEATED, FIXED_LENGTH_BYTES, readonly,          2)
#define FD_EXEC_TEST_LOADED_ADDRESSES_CALLBACK pb_default_field_callback
#define FD_EXEC_TEST_LOADED_ADDRESSES_DEFAULT NULL

#define FD_EXEC_TEST_TRANSACTION_MESSAGE_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, BOOL,     is_legacy,         1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  header,            2) \
X(a, POINTER,  REPEATED, BYTES,    account_keys,      3) \
X(a, POINTER,  REPEATED, MESSAGE,  account_shared_data,   4) \
X(a, POINTER,  REPEATED, MESSAGE,  instructions,      5) \
X(a, POINTER,  REPEATED, MESSAGE,  address_table_lookups,   6) \
X(a, STATIC,   OPTIONAL, MESSAGE,  loaded_addresses,   7)
#define FD_EXEC_TEST_TRANSACTION_MESSAGE_CALLBACK NULL
#define FD_EXEC_TEST_TRANSACTION_MESSAGE_DEFAULT NULL
#define fd_exec_test_transaction_message_t_header_MSGTYPE fd_exec_test_message_header_t
#define fd_exec_test_transaction_message_t_account_shared_data_MSGTYPE fd_exec_test_acct_state_t
#define fd_exec_test_transaction_message_t_instructions_MSGTYPE fd_exec_test_compiled_instruction_t
#define fd_exec_test_transaction_message_t_address_table_lookups_MSGTYPE fd_exec_test_message_address_table_lookup_t
#define fd_exec_test_transaction_message_t_loaded_addresses_MSGTYPE fd_exec_test_loaded_addresses_t

#define FD_EXEC_TEST_SANITIZED_TRANSACTION_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  message,           1) \
X(a, POINTER,  SINGULAR, BYTES,    message_hash,      2) \
X(a, STATIC,   SINGULAR, BOOL,     is_simple_vote_tx,   3) \
X(a, POINTER,  REPEATED, BYTES,    signatures,        4)
#define FD_EXEC_TEST_SANITIZED_TRANSACTION_CALLBACK NULL
#define FD_EXEC_TEST_SANITIZED_TRANSACTION_DEFAULT NULL
#define fd_exec_test_sanitized_transaction_t_message_MSGTYPE fd_exec_test_transaction_message_t

#define FD_EXEC_TEST_TXN_CONTEXT_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  tx,                1) \
X(a, STATIC,   SINGULAR, UINT64,   max_age,           2) \
X(a, STATIC,   SINGULAR, UINT64,   log_messages_byte_limit,   3) \
X(a, STATIC,   OPTIONAL, MESSAGE,  epoch_ctx,         4) \
X(a, STATIC,   OPTIONAL, MESSAGE,  slot_ctx,          5)
#define FD_EXEC_TEST_TXN_CONTEXT_CALLBACK NULL
#define FD_EXEC_TEST_TXN_CONTEXT_DEFAULT NULL
#define fd_exec_test_txn_context_t_tx_MSGTYPE fd_exec_test_sanitized_transaction_t
#define fd_exec_test_txn_context_t_epoch_ctx_MSGTYPE fd_exec_test_epoch_context_t
#define fd_exec_test_txn_context_t_slot_ctx_MSGTYPE fd_exec_test_slot_context_t

#define FD_EXEC_TEST_RESULTING_STATE_FIELDLIST(X, a) \
X(a, POINTER,  REPEATED, MESSAGE,  acct_states,       1) \
X(a, POINTER,  REPEATED, MESSAGE,  rent_debits,       2) \
X(a, STATIC,   SINGULAR, UINT64,   transaction_rent,   3)
#define FD_EXEC_TEST_RESULTING_STATE_CALLBACK NULL
#define FD_EXEC_TEST_RESULTING_STATE_DEFAULT NULL
#define fd_exec_test_resulting_state_t_acct_states_MSGTYPE fd_exec_test_acct_state_t
#define fd_exec_test_resulting_state_t_rent_debits_MSGTYPE fd_exec_test_rent_debits_t

#define FD_EXEC_TEST_RENT_DEBITS_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FIXED_LENGTH_BYTES, pubkey,            1) \
X(a, STATIC,   SINGULAR, INT64,    rent_collected,    2)
#define FD_EXEC_TEST_RENT_DEBITS_CALLBACK NULL
#define FD_EXEC_TEST_RENT_DEBITS_DEFAULT NULL

#define FD_EXEC_TEST_TXN_RESULT_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, BOOL,     executed,          1) \
X(a, STATIC,   SINGULAR, BOOL,     sanitization_error,   2) \
X(a, STATIC,   OPTIONAL, MESSAGE,  resulting_state,   3) \
X(a, STATIC,   SINGULAR, UINT64,   rent,              4) \
X(a, STATIC,   SINGULAR, BOOL,     is_ok,             5) \
X(a, STATIC,   SINGULAR, UINT32,   status,            6) \
X(a, POINTER,  SINGULAR, BYTES,    return_data,       7) \
X(a, STATIC,   SINGULAR, UINT64,   executed_units,    8) \
X(a, STATIC,   SINGULAR, INT64,    accounts_data_len_delta,   9)
#define FD_EXEC_TEST_TXN_RESULT_CALLBACK NULL
#define FD_EXEC_TEST_TXN_RESULT_DEFAULT NULL
#define fd_exec_test_txn_result_t_resulting_state_MSGTYPE fd_exec_test_resulting_state_t

extern const pb_msgdesc_t fd_exec_test_message_header_t_msg;
extern const pb_msgdesc_t fd_exec_test_compiled_instruction_t_msg;
extern const pb_msgdesc_t fd_exec_test_message_address_table_lookup_t_msg;
extern const pb_msgdesc_t fd_exec_test_loaded_addresses_t_msg;
extern const pb_msgdesc_t fd_exec_test_transaction_message_t_msg;
extern const pb_msgdesc_t fd_exec_test_sanitized_transaction_t_msg;
extern const pb_msgdesc_t fd_exec_test_txn_context_t_msg;
extern const pb_msgdesc_t fd_exec_test_resulting_state_t_msg;
extern const pb_msgdesc_t fd_exec_test_rent_debits_t_msg;
extern const pb_msgdesc_t fd_exec_test_txn_result_t_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define FD_EXEC_TEST_MESSAGE_HEADER_FIELDS &fd_exec_test_message_header_t_msg
#define FD_EXEC_TEST_COMPILED_INSTRUCTION_FIELDS &fd_exec_test_compiled_instruction_t_msg
#define FD_EXEC_TEST_MESSAGE_ADDRESS_TABLE_LOOKUP_FIELDS &fd_exec_test_message_address_table_lookup_t_msg
#define FD_EXEC_TEST_LOADED_ADDRESSES_FIELDS &fd_exec_test_loaded_addresses_t_msg
#define FD_EXEC_TEST_TRANSACTION_MESSAGE_FIELDS &fd_exec_test_transaction_message_t_msg
#define FD_EXEC_TEST_SANITIZED_TRANSACTION_FIELDS &fd_exec_test_sanitized_transaction_t_msg
#define FD_EXEC_TEST_TXN_CONTEXT_FIELDS &fd_exec_test_txn_context_t_msg
#define FD_EXEC_TEST_RESULTING_STATE_FIELDS &fd_exec_test_resulting_state_t_msg
#define FD_EXEC_TEST_RENT_DEBITS_FIELDS &fd_exec_test_rent_debits_t_msg
#define FD_EXEC_TEST_TXN_RESULT_FIELDS &fd_exec_test_txn_result_t_msg

/* Maximum encoded size of messages (where known) */
/* fd_exec_test_CompiledInstruction_size depends on runtime parameters */
/* fd_exec_test_MessageAddressTableLookup_size depends on runtime parameters */
/* fd_exec_test_LoadedAddresses_size depends on runtime parameters */
/* fd_exec_test_TransactionMessage_size depends on runtime parameters */
/* fd_exec_test_SanitizedTransaction_size depends on runtime parameters */
/* fd_exec_test_TxnContext_size depends on runtime parameters */
/* fd_exec_test_ResultingState_size depends on runtime parameters */
/* fd_exec_test_TxnResult_size depends on runtime parameters */
#define FD_EXEC_TEST_MESSAGE_HEADER_SIZE         18
#define FD_EXEC_TEST_RENT_DEBITS_SIZE            45
#define ORG_SOLANA_SEALEVEL_V1_TXN_PB_H_MAX_SIZE FD_EXEC_TEST_RENT_DEBITS_SIZE

/* Mapping from canonical names (mangle_names or overridden package name) */
#define org_solana_sealevel_v1_MessageHeader fd_exec_test_MessageHeader
#define org_solana_sealevel_v1_CompiledInstruction fd_exec_test_CompiledInstruction
#define org_solana_sealevel_v1_MessageAddressTableLookup fd_exec_test_MessageAddressTableLookup
#define org_solana_sealevel_v1_LoadedAddresses fd_exec_test_LoadedAddresses
#define org_solana_sealevel_v1_TransactionMessage fd_exec_test_TransactionMessage
#define org_solana_sealevel_v1_SanitizedTransaction fd_exec_test_SanitizedTransaction
#define org_solana_sealevel_v1_TxnContext fd_exec_test_TxnContext
#define org_solana_sealevel_v1_ResultingState fd_exec_test_ResultingState
#define org_solana_sealevel_v1_RentDebits fd_exec_test_RentDebits
#define org_solana_sealevel_v1_TxnResult fd_exec_test_TxnResult
#define ORG_SOLANA_SEALEVEL_V1_MESSAGE_HEADER_INIT_DEFAULT FD_EXEC_TEST_MESSAGE_HEADER_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_COMPILED_INSTRUCTION_INIT_DEFAULT FD_EXEC_TEST_COMPILED_INSTRUCTION_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_MESSAGE_ADDRESS_TABLE_LOOKUP_INIT_DEFAULT FD_EXEC_TEST_MESSAGE_ADDRESS_TABLE_LOOKUP_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_LOADED_ADDRESSES_INIT_DEFAULT FD_EXEC_TEST_LOADED_ADDRESSES_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_TRANSACTION_MESSAGE_INIT_DEFAULT FD_EXEC_TEST_TRANSACTION_MESSAGE_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_SANITIZED_TRANSACTION_INIT_DEFAULT FD_EXEC_TEST_SANITIZED_TRANSACTION_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_TXN_CONTEXT_INIT_DEFAULT FD_EXEC_TEST_TXN_CONTEXT_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_RESULTING_STATE_INIT_DEFAULT FD_EXEC_TEST_RESULTING_STATE_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_RENT_DEBITS_INIT_DEFAULT FD_EXEC_TEST_RENT_DEBITS_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_TXN_RESULT_INIT_DEFAULT FD_EXEC_TEST_TXN_RESULT_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_MESSAGE_HEADER_INIT_ZERO FD_EXEC_TEST_MESSAGE_HEADER_INIT_ZERO
#define ORG_SOLANA_SEALEVEL_V1_COMPILED_INSTRUCTION_INIT_ZERO FD_EXEC_TEST_COMPILED_INSTRUCTION_INIT_ZERO
#define ORG_SOLANA_SEALEVEL_V1_MESSAGE_ADDRESS_TABLE_LOOKUP_INIT_ZERO FD_EXEC_TEST_MESSAGE_ADDRESS_TABLE_LOOKUP_INIT_ZERO
#define ORG_SOLANA_SEALEVEL_V1_LOADED_ADDRESSES_INIT_ZERO FD_EXEC_TEST_LOADED_ADDRESSES_INIT_ZERO
#define ORG_SOLANA_SEALEVEL_V1_TRANSACTION_MESSAGE_INIT_ZERO FD_EXEC_TEST_TRANSACTION_MESSAGE_INIT_ZERO
#define ORG_SOLANA_SEALEVEL_V1_SANITIZED_TRANSACTION_INIT_ZERO FD_EXEC_TEST_SANITIZED_TRANSACTION_INIT_ZERO
#define ORG_SOLANA_SEALEVEL_V1_TXN_CONTEXT_INIT_ZERO FD_EXEC_TEST_TXN_CONTEXT_INIT_ZERO
#define ORG_SOLANA_SEALEVEL_V1_RESULTING_STATE_INIT_ZERO FD_EXEC_TEST_RESULTING_STATE_INIT_ZERO
#define ORG_SOLANA_SEALEVEL_V1_RENT_DEBITS_INIT_ZERO FD_EXEC_TEST_RENT_DEBITS_INIT_ZERO
#define ORG_SOLANA_SEALEVEL_V1_TXN_RESULT_INIT_ZERO FD_EXEC_TEST_TXN_RESULT_INIT_ZERO

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
