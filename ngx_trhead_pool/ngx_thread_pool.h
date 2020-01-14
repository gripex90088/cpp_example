/*
 * ngx_thread_pool.h
 *
 *  Created on: Jul 21, 2019
 *      Author: xuxing
 */

#ifndef NGX_THREAD_POOL_H_
#define NGX_THREAD_POOL_H_

/*
 * uintptr_t header file
 */
#include <stdint.h>

/*
 * u_char header file
 */
#include <sys/types.h>
/**
 * C++ include <cstddef>
 * size_t header file
 */
#include <stddef.h>
#include <pthread.h>


typedef uintptr_t	ngx_uint_t;
typedef intptr_t	ngx_int_t;

struct ngx_command_s {
    ngx_str_t             name;
    ngx_uint_t            type;
    char               *(*set)(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
    ngx_uint_t            conf;
    ngx_uint_t            offset;
    void                 *post;
};

typedef struct ngx_thread_task_s 	ngx_thread_task_t;
typedef struct ngx_log_s			ngx_log_t;
typedef struct ngx_event_s			ngx_event_t;
typedef struct ngx_conf_s			ngx_conf_t;
typedef	struct ngx_cycle_s			ngx_cycle_t;
typedef struct ngx_pool_s			ngx_pool_t;
typedef struct ngx_command_s		ngx_command_t;
typedef struct {
	size_t	len;
	u_char	*data;
} ngx_str_t;


typedef pthread_mutex_t	ngx_thread_mutex_t;
typedef pthread_cond_t	ngx_thread_cond_t;

struct ngx_thread_task_s {
	ngx_thread_task_t	*next;
	ngx_uint_t			id;
	void				*ctx;
	void				(*handler)(void *data, ngx_log_t * log);
	ngx_event_t			event;
};
typedef struct ngx_thread_pool_s  ngx_thread_pool_t;

#define NGX_CONF_TAKE2		0x00000004
#define NGX_CONF_TAKE3		0x00000008
#define NGX_MAIN_CONF		0x01000000
#define NGX_DIRECT_CONF		0x00010000
#define NGX_CONF_TAKE23		(NGX_CONF_TAKE2|NGX_CONF_TAKE3)

#define ngx_string(str)		{sizeof(str)-1, (u_char *) str }
#define ngx_null_string		{0, NULL}

#define ngx_null_command	{ngx_null_string, 0, NULL, 0, 0, NULL }

typedef struct {
	ngx_str_t			name;
	void 				*(*create_conf)(ngx_cycle_t *cycle);
	char				*(*init_conf)(ngx_cycle_t *cycle, void *conf);
} ngx_core_module_t;


ngx_thread_pool_t *ngx_thread_pool_add(ngx_conf_t *cf, ngx_str_t *name);
ngx_thread_pool_t *ngx_thread_pool_get(ngx_cycle_t *cycle, ngx_str_t *name);

ngx_thread_task_t *ngx_thread_task_alloc(ngx_pool_t *pool, size_t size);
ngx_int_t	ngx_thread_task_post(ngx_thread_pool_t *tp, ngx_thread_task_t *task);

#endif /* NGX_THREAD_POOL_H_ */
