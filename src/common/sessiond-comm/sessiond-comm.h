/*
 * Copyright (C) 2011 - David Goulet <david.goulet@polymtl.ca>
 *                      Julien Desfossez <julien.desfossez@polymtl.ca>
 *                      Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2 only,
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*
 * This header is meant for liblttng and libust internal use ONLY. These
 * declarations should NOT be considered stable API.
 */

#ifndef _LTTNG_SESSIOND_COMM_H
#define _LTTNG_SESSIOND_COMM_H

#define _GNU_SOURCE
#include <limits.h>
#include <lttng/lttng.h>
#include <lttng/snapshot-internal.h>
#include <common/compat/socket.h>
#include <common/uri.h>
#include <common/defaults.h>
#include <common/compat/uuid.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/un.h>

#include "inet.h"
#include "inet6.h"
#include "unix.h"

/* Queue size of listen(2) */
#define LTTNG_SESSIOND_COMM_MAX_LISTEN 64

/* Maximum number of FDs that can be sent over a Unix socket */
#define LTTCOMM_MAX_SEND_FDS           4

/*
 * Get the error code index from 0 since LTTCOMM_OK start at 1000
 */
#define LTTCOMM_ERR_INDEX(code) (code - LTTCOMM_CONSUMERD_COMMAND_SOCK_READY)

enum lttcomm_sessiond_command {
	/* Tracer command */
	LTTNG_ADD_CONTEXT                   = 0,
	LTTNG_CALIBRATE                     = 1,
	LTTNG_DISABLE_CHANNEL               = 2,
	LTTNG_DISABLE_EVENT                 = 3,
	LTTNG_DISABLE_ALL_EVENT             = 4,
	LTTNG_ENABLE_CHANNEL                = 5,
	LTTNG_ENABLE_EVENT                  = 6,
	LTTNG_ENABLE_ALL_EVENT              = 7,
	/* Session daemon command */
	LTTNG_CREATE_SESSION                = 8,
	LTTNG_DESTROY_SESSION               = 9,
	LTTNG_LIST_CHANNELS                 = 10,
	LTTNG_LIST_DOMAINS                  = 11,
	LTTNG_LIST_EVENTS                   = 12,
	LTTNG_LIST_SESSIONS                 = 13,
	LTTNG_LIST_TRACEPOINTS              = 14,
	LTTNG_REGISTER_CONSUMER             = 15,
	LTTNG_START_TRACE                   = 16,
	LTTNG_STOP_TRACE                    = 17,
	LTTNG_LIST_TRACEPOINT_FIELDS        = 18,

	/* Consumer */
	LTTNG_DISABLE_CONSUMER              = 19,
	LTTNG_ENABLE_CONSUMER               = 20,
	LTTNG_SET_CONSUMER_URI              = 21,
	LTTNG_ENABLE_EVENT_WITH_FILTER      = 22,
	LTTNG_ENABLE_EVENT_WITH_EXCLUSION   = 23,
	LTTNG_DATA_PENDING                  = 24,
	LTTNG_SNAPSHOT_ADD_OUTPUT           = 25,
	LTTNG_SNAPSHOT_DEL_OUTPUT           = 26,
	LTTNG_SNAPSHOT_LIST_OUTPUT          = 27,
	LTTNG_SNAPSHOT_RECORD               = 28,
	LTTNG_CREATE_SESSION_SNAPSHOT       = 29,
	LTTNG_CREATE_SESSION_LIVE           = 30,
};

enum lttcomm_relayd_command {
	RELAYD_ADD_STREAM                   = 1,
	RELAYD_CREATE_SESSION               = 2,
	RELAYD_START_DATA                   = 3,
	RELAYD_UPDATE_SYNC_INFO             = 4,
	RELAYD_VERSION                      = 5,
	RELAYD_SEND_METADATA                = 6,
	RELAYD_CLOSE_STREAM                 = 7,
	RELAYD_DATA_PENDING                 = 8,
	RELAYD_QUIESCENT_CONTROL            = 9,
	RELAYD_BEGIN_DATA_PENDING           = 10,
	RELAYD_END_DATA_PENDING             = 11,
	RELAYD_ADD_INDEX                    = 12,
	RELAYD_SEND_INDEX                   = 13,
	RELAYD_CLOSE_INDEX                  = 14,
	/* Live-reading commands. */
	RELAYD_LIST_SESSIONS                = 15,
};

/*
 * lttcomm error code.
 */
enum lttcomm_return_code {
	LTTCOMM_CONSUMERD_COMMAND_SOCK_READY = 1,   /* Command socket ready */
	LTTCOMM_CONSUMERD_SUCCESS_RECV_FD,          /* Success on receiving fds */
	LTTCOMM_CONSUMERD_ERROR_RECV_FD,            /* Error on receiving fds */
	LTTCOMM_CONSUMERD_ERROR_RECV_CMD,           /* Error on receiving command */
	LTTCOMM_CONSUMERD_POLL_ERROR,               /* Error in polling thread */
	LTTCOMM_CONSUMERD_POLL_NVAL,                /* Poll on closed fd */
	LTTCOMM_CONSUMERD_POLL_HUP,                 /* All fds have hungup */
	LTTCOMM_CONSUMERD_EXIT_SUCCESS,             /* Consumerd exiting normally */
	LTTCOMM_CONSUMERD_EXIT_FAILURE,             /* Consumerd exiting on error */
	LTTCOMM_CONSUMERD_OUTFD_ERROR,              /* Error opening the tracefile */
	LTTCOMM_CONSUMERD_SPLICE_EBADF,             /* EBADF from splice(2) */
	LTTCOMM_CONSUMERD_SPLICE_EINVAL,            /* EINVAL from splice(2) */
	LTTCOMM_CONSUMERD_SPLICE_ENOMEM,            /* ENOMEM from splice(2) */
	LTTCOMM_CONSUMERD_SPLICE_ESPIPE,            /* ESPIPE from splice(2) */
	LTTCOMM_CONSUMERD_ENOMEM,                   /* Consumer is out of memory */
	LTTCOMM_CONSUMERD_ERROR_METADATA,           /* Error with metadata. */
	LTTCOMM_CONSUMERD_FATAL,                    /* Fatal error. */
	LTTCOMM_CONSUMERD_RELAYD_FAIL,              /* Error on remote relayd */

	/* MUST be last element */
	LTTCOMM_NR,						/* Last element */
};

/* lttng socket protocol. */
enum lttcomm_sock_proto {
	LTTCOMM_SOCK_UDP,
	LTTCOMM_SOCK_TCP,
};

/*
 * Index in the net_families array below. Please keep in sync!
 */
enum lttcomm_sock_domain {
	LTTCOMM_INET      = 0,
	LTTCOMM_INET6     = 1,
};

enum lttcomm_metadata_command {
	LTTCOMM_METADATA_REQUEST = 1,
};

/*
 * Commands sent from the consumerd to the sessiond to request if new metadata
 * is available. This message is used to find the per UID _or_ per PID registry
 * for the channel key. For per UID lookup, the triplet
 * bits_per_long/uid/session_id is used. On lookup failure, we search for the
 * per PID registry indexed by session id ignoring the other values.
 */
struct lttcomm_metadata_request_msg {
	uint64_t session_id; /* Tracing session id */
	uint64_t session_id_per_pid; /* Tracing session id for per-pid */
	uint32_t bits_per_long; /* Consumer ABI */
	uint32_t uid;
	uint64_t key; /* Metadata channel key. */
} LTTNG_PACKED;

struct lttcomm_sockaddr {
	enum lttcomm_sock_domain type;
	union {
		struct sockaddr_in sin;
		struct sockaddr_in6 sin6;
	} addr;
} LTTNG_PACKED;

struct lttcomm_sock {
	int32_t fd;
	enum lttcomm_sock_proto proto;
	struct lttcomm_sockaddr sockaddr;
	const struct lttcomm_proto_ops *ops;
} LTTNG_PACKED;

/*
 * Relayd sock. Adds the protocol version to use for the communications with
 * the relayd.
 */
struct lttcomm_relayd_sock {
	struct lttcomm_sock sock;
	uint32_t major;
	uint32_t minor;
} LTTNG_PACKED;

struct lttcomm_net_family {
	int family;
	int (*create) (struct lttcomm_sock *sock, int type, int proto);
};

struct lttcomm_proto_ops {
	int (*bind) (struct lttcomm_sock *sock);
	int (*close) (struct lttcomm_sock *sock);
	int (*connect) (struct lttcomm_sock *sock);
	struct lttcomm_sock *(*accept) (struct lttcomm_sock *sock);
	int (*listen) (struct lttcomm_sock *sock, int backlog);
	ssize_t (*recvmsg) (struct lttcomm_sock *sock, void *buf, size_t len,
			int flags);
	ssize_t (*sendmsg) (struct lttcomm_sock *sock, void *buf, size_t len,
			int flags);
};

/*
 * Data structure received from lttng client to session daemon.
 */
struct lttcomm_session_msg {
	uint32_t cmd_type;	/* enum lttcomm_sessiond_command */
	struct lttng_session session;
	struct lttng_domain domain;
	union {
		struct {
			char channel_name[LTTNG_SYMBOL_NAME_LEN];
			char name[NAME_MAX];
		} LTTNG_PACKED disable;
		/* Event data */
		struct {
			char channel_name[LTTNG_SYMBOL_NAME_LEN];
			struct lttng_event event;
			/* Length of following bytecode for filter. */
			uint32_t bytecode_len;
			/* exclusion data */
			uint32_t exclusion_count;
			/*
			 * After this structure, the following variable-length
			 * items are transmitted:
			 * - char exclusion_names[LTTNG_SYMBOL_NAME_LEN][exclusion_count]
			 * - unsigned char filter_bytecode[bytecode_len]
			 */
		} LTTNG_PACKED enable;
		/* Create channel */
		struct {
			struct lttng_channel chan;
		} LTTNG_PACKED channel;
		/* Context */
		struct {
			char channel_name[LTTNG_SYMBOL_NAME_LEN];
			struct lttng_event_context ctx;
		} LTTNG_PACKED context;
		/* Use by register_consumer */
		struct {
			char path[PATH_MAX];
		} LTTNG_PACKED reg;
		/* List */
		struct {
			char channel_name[LTTNG_SYMBOL_NAME_LEN];
		} LTTNG_PACKED list;
		struct lttng_calibrate calibrate;
		/* Used by the set_consumer_url and used by create_session also call */
		struct {
			/* Number of lttng_uri following */
			uint32_t size;
		} LTTNG_PACKED uri;
		struct {
			struct lttng_snapshot_output output;
		} LTTNG_PACKED snapshot_output;
		struct {
			uint32_t wait;
			struct lttng_snapshot_output output;
		} LTTNG_PACKED snapshot_record;
		struct {
			uint32_t nb_uri;
			unsigned int timer_interval;	/* usec */
		} LTTNG_PACKED session_live;
	} u;
} LTTNG_PACKED;

#define LTTNG_FILTER_MAX_LEN	65536

/*
 * Filter bytecode data. The reloc table is located at the end of the
 * bytecode. It is made of tuples: (uint16_t, var. len. string). It
 * starts at reloc_table_offset.
 */
#define LTTNG_FILTER_PADDING	32
struct lttng_filter_bytecode {
	uint32_t len;	/* len of data */
	uint32_t reloc_table_offset;
	uint64_t seqnum;
	char padding[LTTNG_FILTER_PADDING];
	char data[0];
} LTTNG_PACKED;

/*
 * Event exclusion data. At the end of the structure, there will actually
 * by zero or more names, where the actual number of names is given by
 * the 'count' item of the structure.
 */
#define LTTNG_EVENT_EXCLUSION_PADDING	32
struct lttng_event_exclusion {
	uint32_t count;
	char padding[LTTNG_EVENT_EXCLUSION_PADDING];
	char names[LTTNG_SYMBOL_NAME_LEN][0];
} LTTNG_PACKED;

/*
 * Data structure for the response from sessiond to the lttng client.
 */
struct lttcomm_lttng_msg {
	uint32_t cmd_type;	/* enum lttcomm_sessiond_command */
	uint32_t ret_code;	/* enum lttcomm_return_code */
	uint32_t pid;		/* pid_t */
	uint32_t data_size;
	/* Contains: trace_name + data */
	char payload[];
} LTTNG_PACKED;

struct lttcomm_lttng_output_id {
	uint32_t id;
} LTTNG_PACKED;

/*
 * lttcomm_consumer_msg is the message sent from sessiond to consumerd
 * to either add a channel, add a stream, update a stream, or stop
 * operation.
 */
struct lttcomm_consumer_msg {
	uint32_t cmd_type;	/* enum consumerd_command */
	union {
		struct {
			uint64_t channel_key;
			uint64_t session_id;
			char pathname[PATH_MAX];
			uint32_t uid;
			uint32_t gid;
			uint64_t relayd_id;
			/* nb_init_streams is the number of streams open initially. */
			uint32_t nb_init_streams;
			char name[LTTNG_SYMBOL_NAME_LEN];
			/* Use splice or mmap to consume this fd */
			enum lttng_event_output output;
			int type; /* Per cpu or metadata. */
			uint64_t tracefile_size; /* bytes */
			uint32_t tracefile_count; /* number of tracefiles */
			/* If the channel's streams have to be monitored or not. */
			uint32_t monitor;
			/* timer to check the streams usage in live mode (usec). */
			unsigned int live_timer_interval;
		} LTTNG_PACKED channel; /* Only used by Kernel. */
		struct {
			uint64_t stream_key;
			uint64_t channel_key;
			int32_t cpu;	/* On which CPU this stream is assigned. */
			/* Tells the consumer if the stream should be or not monitored. */
			uint32_t no_monitor;
		} LTTNG_PACKED stream;	/* Only used by Kernel. */
		struct {
			uint64_t net_index;
			enum lttng_stream_type type;
			/* Open socket to the relayd */
			struct lttcomm_relayd_sock sock;
			/* Tracing session id associated to the relayd. */
			uint64_t session_id;
			/* Relayd session id, only used with control socket. */
			uint64_t relayd_session_id;
		} LTTNG_PACKED relayd_sock;
		struct {
			uint64_t net_seq_idx;
		} LTTNG_PACKED destroy_relayd;
		struct {
			uint64_t session_id;
		} LTTNG_PACKED data_pending;
		struct {
			uint64_t subbuf_size;			/* bytes */
			uint64_t num_subbuf;			/* power of 2 */
			int32_t overwrite;			/* 1: overwrite, 0: discard */
			uint32_t switch_timer_interval;		/* usec */
			uint32_t read_timer_interval;		/* usec */
			unsigned int live_timer_interval;		/* usec */
			int32_t output;				/* splice, mmap */
			int32_t type;				/* metadata or per_cpu */
			uint64_t session_id;			/* Tracing session id */
			char pathname[PATH_MAX];		/* Channel file path. */
			char name[LTTNG_SYMBOL_NAME_LEN];	/* Channel name. */
			uint32_t uid;				/* User ID of the session */
			uint32_t gid;				/* Group ID ot the session */
			uint64_t relayd_id;			/* Relayd id if apply. */
			uint64_t key;				/* Unique channel key. */
			unsigned char uuid[UUID_LEN];	/* uuid for ust tracer. */
			uint32_t chan_id;			/* Channel ID on the tracer side. */
			uint64_t tracefile_size;	/* bytes */
			uint32_t tracefile_count;	/* number of tracefiles */
			uint64_t session_id_per_pid;	/* Per-pid session ID. */
			/* Tells the consumer if the stream should be or not monitored. */
			uint32_t monitor;
			/*
			 * For UST per UID buffers, this is the application UID of the
			 * channel.  This can be different from the user UID requesting the
			 * channel creation and used for the rights on the stream file
			 * because the application can be in the tracing for instance.
			 */
			uint32_t ust_app_uid;
		} LTTNG_PACKED ask_channel;
		struct {
			uint64_t key;
		} LTTNG_PACKED get_channel;
		struct {
			uint64_t key;
		} LTTNG_PACKED destroy_channel;
		struct {
			uint64_t key;	/* Metadata channel key. */
			uint64_t target_offset;	/* Offset in the consumer */
			uint64_t len;	/* Length of metadata to be received. */
		} LTTNG_PACKED push_metadata;
		struct {
			uint64_t key;	/* Metadata channel key. */
		} LTTNG_PACKED close_metadata;
		struct {
			uint64_t key;	/* Metadata channel key. */
		} LTTNG_PACKED setup_metadata;
		struct {
			uint64_t key;	/* Channel key. */
		} LTTNG_PACKED flush_channel;
		struct {
			char pathname[PATH_MAX];
			/* Indicate if the snapshot goes on the relayd or locally. */
			uint32_t use_relayd;
			uint32_t metadata;		/* This a metadata snapshot. */
			uint64_t relayd_id;		/* Relayd id if apply. */
			uint64_t key;
			uint64_t max_stream_size;
		} LTTNG_PACKED snapshot_channel;
	} u;
} LTTNG_PACKED;

/*
 * Status message returned to the sessiond after a received command.
 */
struct lttcomm_consumer_status_msg {
	enum lttng_error_code ret_code;
} LTTNG_PACKED;

struct lttcomm_consumer_status_channel {
	enum lttng_error_code ret_code;
	uint64_t key;
	unsigned int stream_count;
} LTTNG_PACKED;

#ifdef HAVE_LIBLTTNG_UST_CTL

#include <lttng/ust-abi.h>

/*
 * Data structure for the commands sent from sessiond to UST.
 */
struct lttcomm_ust_msg {
	uint32_t handle;
	uint32_t cmd;
	union {
		struct lttng_ust_channel channel;
		struct lttng_ust_stream stream;
		struct lttng_ust_event event;
		struct lttng_ust_context context;
		struct lttng_ust_tracer_version version;
	} u;
} LTTNG_PACKED;

/*
 * Data structure for the response from UST to the session daemon.
 * cmd_type is sent back in the reply for validation.
 */
struct lttcomm_ust_reply {
	uint32_t handle;
	uint32_t cmd;
	uint32_t ret_code;	/* enum lttcomm_return_code */
	uint32_t ret_val;	/* return value */
	union {
		struct {
			uint64_t memory_map_size;
		} LTTNG_PACKED channel;
		struct {
			uint64_t memory_map_size;
		} LTTNG_PACKED stream;
		struct lttng_ust_tracer_version version;
	} u;
} LTTNG_PACKED;

#endif /* HAVE_LIBLTTNG_UST_CTL */

extern const char *lttcomm_get_readable_code(enum lttcomm_return_code code);

extern int lttcomm_init_inet_sockaddr(struct lttcomm_sockaddr *sockaddr,
		const char *ip, unsigned int port);
extern int lttcomm_init_inet6_sockaddr(struct lttcomm_sockaddr *sockaddr,
		const char *ip, unsigned int port);

extern struct lttcomm_sock *lttcomm_alloc_sock(enum lttcomm_sock_proto proto);
extern int lttcomm_create_sock(struct lttcomm_sock *sock);
extern struct lttcomm_sock *lttcomm_alloc_sock_from_uri(struct lttng_uri *uri);
extern void lttcomm_destroy_sock(struct lttcomm_sock *sock);
extern struct lttcomm_sock *lttcomm_alloc_copy_sock(struct lttcomm_sock *src);
extern void lttcomm_copy_sock(struct lttcomm_sock *dst,
		struct lttcomm_sock *src);

/* Relayd socket object. */
extern struct lttcomm_relayd_sock *lttcomm_alloc_relayd_sock(
		struct lttng_uri *uri, uint32_t major, uint32_t minor);

extern int lttcomm_setsockopt_rcv_timeout(int sock, unsigned int msec);
extern int lttcomm_setsockopt_snd_timeout(int sock, unsigned int msec);

extern void lttcomm_init(void);
/* Get network timeout, in milliseconds */
extern unsigned long lttcomm_get_network_timeout(void);

#endif	/* _LTTNG_SESSIOND_COMM_H */
