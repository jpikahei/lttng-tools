/*
 * Copyright (C) 2012 - David Goulet <dgoulet@efficios.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License, version 2 only, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _COMMON_UTILS_H
#define _COMMON_UTILS_H

#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

#define KIBI_LOG2 10
#define MEBI_LOG2 20
#define GIBI_LOG2 30

char *utils_resolve_relative(const char *path);
char *utils_expand_path(const char *path);
int utils_create_pipe(int *dst);
int utils_create_pipe_cloexec(int *dst);
int utils_create_pipe_cloexec_nonblock(int *dst);
void utils_close_pipe(int *src);
char *utils_strdupdelim(const char *begin, const char *end);
int utils_set_fd_cloexec(int fd);
int utils_create_pid_file(pid_t pid, const char *filepath);
int utils_mkdir_recursive(const char *path, mode_t mode);
int utils_create_stream_file(const char *path_name, char *file_name, uint64_t size,
		uint64_t count, int uid, int gid, char *suffix);
int utils_rotate_stream_file(char *path_name, char *file_name, uint64_t size,
		uint64_t count, int uid, int gid, int out_fd, uint64_t *new_count,
		int *stream_fd);
int utils_parse_size_suffix(char *str, uint64_t *size);
int utils_get_count_order_u32(uint32_t x);
char *utils_get_home_dir(void);
size_t utils_get_current_time_str(const char *format, char *dst, size_t len);
gid_t utils_get_group_id(const char *name);

#endif /* _COMMON_UTILS_H */
