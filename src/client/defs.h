/* Copyright StrongLoop, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef DEFS_H_
#define DEFS_H_

#include "s5.h"
#include <uv.h>
#include "dump_info.h"

#include <assert.h>
#include <stddef.h>      /* size_t, ssize_t */
#include <stdint.h>
#if defined(_MSC_VER)
#include <winsock2.h>
#else
#include <netinet/in.h>  /* sockaddr_in, sockaddr_in6 */
#include <sys/socket.h>  /* sockaddr */
#endif // defined(_MSC_VER)

#include <stdbool.h>

#include "sockaddr_universal.h"
#include "obfs.h"

struct server_config;
struct ssr_client_state;
struct server_env_t;

/* listener.c */
int ssr_run_loop_begin(struct server_config *cf, void(*feedback_state)(struct ssr_client_state *state, void *p), void *p);
void ssr_run_loop_shutdown(struct ssr_client_state *state);

/* client.c */
void client_tunnel_initialize(uv_tcp_t *lx, unsigned int idle_timeout);
void client_shutdown(struct server_env_t *env);

/* getopt.c */
#if !HAVE_UNISTD_H
extern char *optarg;
int getopt(int argc, char * const argv[], const char *options);
#endif

/* This macro looks complicated but it's not: it calculates the address
* of the embedding struct through the address of the embedded struct.
* In other words, if struct A embeds struct B, then we can obtain
* the address of A by taking the address of B and subtracting the
* field offset of B in A.
*/
#if !defined(CONTAINER_OF)
#define CONTAINER_OF(ptr, type, field)                                        \
  ((type *) ((char *) (ptr) - ((char *) &((type *) 0)->field)))
#endif // !defined(CONTAINER_OF)

#endif  /* DEFS_H_ */
