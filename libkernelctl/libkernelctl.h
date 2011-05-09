/*
 * Copyright (C) 2011 - Julien Desfossez <julien.desfossez@polymtl.ca>
 *                      Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef _LTT_LIBKERNELCTL_H
#define _LTT_LIBKERNELCTL_H

#include <lttng/lttng.h>

int kernctl_create_channel(int fd, struct lttng_channel *chops);
int kernctl_create_event(int fd, struct lttng_event *ev);
int kernctl_create_session(int fd);
int kernctl_create_stream(int fd);
int kernctl_get_max_subbuf_size(int fd, unsigned long *len);
int kernctl_get_mmap_len(int fd, unsigned long *len);
int kernctl_get_mmap_read_offset(int fd, unsigned long *len);
int kernctl_get_next_subbuf(int fd);
int kernctl_get_padded_subbuf_size(int fd, unsigned long *len);
int kernctl_get_subbuf(int fd, unsigned long *len);
int kernctl_get_subbuf_size(int fd, unsigned long *len);
int kernctl_put_next_subbuf(int fd);
int kernctl_put_subbuf(int fd);
int kernctl_snapshot(int fd);
int kernctl_snapshot_get_consumed(int fd, unsigned long *len);
int kernctl_snapshot_get_produced(int fd, unsigned long *len);
int kernctl_start_session(int fd);
int kernctl_stop_session(int fd);

#endif /* _LTT_LIBKERNELCTL_H */
