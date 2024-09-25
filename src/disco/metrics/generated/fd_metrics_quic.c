/* THIS FILE IS GENERATED BY gen_metrics.py. DO NOT HAND EDIT. */
#include "fd_metrics_quic.h"

const fd_metrics_meta_t FD_METRICS_QUIC[FD_METRICS_QUIC_TOTAL] = {
    DECLARE_METRIC_COUNTER( QUIC_TILE, QUIC_FRAGMENT_RECEIVE ),
    DECLARE_METRIC_COUNTER( QUIC_TILE, QUIC_FRAGMENT_DROP ),
    DECLARE_METRIC_COUNTER( QUIC_TILE, QUIC_TRANSACTION_RECEIVE ),
    DECLARE_METRIC_COUNTER( QUIC_TILE, QUIC_PACKET_TOO_SMALL ),
    DECLARE_METRIC_COUNTER( QUIC_TILE, NON_QUIC_PACKET_TOO_SMALL ),
    DECLARE_METRIC_COUNTER( QUIC_TILE, NON_QUIC_PACKET_TOO_LARGE ),
    DECLARE_METRIC_COUNTER( QUIC_TILE, NON_QUIC_TRANSACTION_RECEIVE ),
    DECLARE_METRIC_COUNTER( QUIC, RECEIVED_PACKETS ),
    DECLARE_METRIC_COUNTER( QUIC, RECEIVED_BYTES ),
    DECLARE_METRIC_COUNTER( QUIC, SENT_PACKETS ),
    DECLARE_METRIC_COUNTER( QUIC, SENT_BYTES ),
    DECLARE_METRIC_GAUGE( QUIC, CONNECTIONS_ACTIVE ),
    DECLARE_METRIC_COUNTER( QUIC, CONNECTIONS_CREATED ),
    DECLARE_METRIC_COUNTER( QUIC, CONNECTIONS_CLOSED ),
    DECLARE_METRIC_COUNTER( QUIC, CONNECTIONS_ABORTED ),
    DECLARE_METRIC_COUNTER( QUIC, CONNECTIONS_RETRIED ),
    DECLARE_METRIC_COUNTER( QUIC, CONNECTION_ERROR_NO_SLOTS ),
    DECLARE_METRIC_COUNTER( QUIC, CONNECTION_ERROR_TLS_FAIL ),
    DECLARE_METRIC_COUNTER( QUIC, CONNECTION_ERROR_RETRY_FAIL ),
    DECLARE_METRIC_COUNTER( QUIC, HANDSHAKES_CREATED ),
    DECLARE_METRIC_COUNTER( QUIC, HANDSHAKE_ERROR_ALLOC_FAIL ),
    DECLARE_METRIC_COUNTER( QUIC, STREAM_OPENED_BIDI_CLIENT ),
    DECLARE_METRIC_COUNTER( QUIC, STREAM_OPENED_BIDI_SERVER ),
    DECLARE_METRIC_COUNTER( QUIC, STREAM_OPENED_UNI_CLIENT ),
    DECLARE_METRIC_COUNTER( QUIC, STREAM_OPENED_UNI_SERVER ),
    DECLARE_METRIC_COUNTER( QUIC, STREAM_CLOSED_BIDI_CLIENT ),
    DECLARE_METRIC_COUNTER( QUIC, STREAM_CLOSED_BIDI_SERVER ),
    DECLARE_METRIC_COUNTER( QUIC, STREAM_CLOSED_UNI_CLIENT ),
    DECLARE_METRIC_COUNTER( QUIC, STREAM_CLOSED_UNI_SERVER ),
    DECLARE_METRIC_GAUGE( QUIC, STREAM_ACTIVE_BIDI_CLIENT ),
    DECLARE_METRIC_GAUGE( QUIC, STREAM_ACTIVE_BIDI_SERVER ),
    DECLARE_METRIC_GAUGE( QUIC, STREAM_ACTIVE_UNI_CLIENT ),
    DECLARE_METRIC_GAUGE( QUIC, STREAM_ACTIVE_UNI_SERVER ),
    DECLARE_METRIC_COUNTER( QUIC, STREAM_RECEIVED_EVENTS ),
    DECLARE_METRIC_COUNTER( QUIC, STREAM_RECEIVED_BYTES ),
};
