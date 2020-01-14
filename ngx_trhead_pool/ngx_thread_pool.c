/*
 * ngx_thread_pool.c
 *
 *  Created on: Jul 21, 2019
 *      Author: xuxing
 */

#include "ngx_thread_pool.h"


typedef struct {
	void 		*elts;
	ngx_uint_t 	nelts;
	size_t		size;
	ngx_uint_t	malloc;
	ngx_pool_t	*poo;
} ngx_array_t;

typedef struct {
	ngx_array_t		pools;
} ngx_thread_pool_conf_t;

typedef struct {
	ngx_thread_task_t	*first;
	ngx_thread_task_t	**last;
} ngx_thread_pool_queue_t;

#define ngx_thread_pool_queue_init(q)	\
	(q)->first = NULL;					\
	(q)->last = &(q)->first

struct ngx_thread_pool_s {
	ngx_thread_mutex_t			mutex;
	ngx_thread_pool_queue_t		queue;
	ngx_int_t					waiting;
	ngx_thread_cond_t			cond;

	ngx_log_t					*log;
	ngx_str_t					name;
	ngx_uint_t					threads;
	ngx_int_t					max_queue;

	u_char						*file;
	ngx_uint_t					line;
};

static ngx_int_t ngx_thread_pool_init(ngx_thread_pool_t *tp, ngx_log_t *log,
		ngx_pool_t *pool);
static void ngx_thread_pool_destroy(ngx_thread_pool_t *tp);
static void ngx_thread_pool_exit_handler(void *data, ngx_log_t *log);

static void ngx_thread_pool_cycle(void *data);
static void ngx_thread_pool_handler(ngx_event_t *ev);

static char *ngx_thread_pool(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static void *ngx_thread_pool_create_conf(ngx_cycle_t *cycle);
static char *ngx_thread_pool_init_conf(ngx_cycle_t *cycle, void *conf);

static ngx_int_t ngx_thread_pool_init_worker(ngx_cycle_t *cycle);
static void ngx_thread_pool_exit_worker(ngx_cycle_t *cycle);


static ngx_command_t ngx_thread_poool_commands[] = {

	{ ngx_string("thread_pool"),
	  NGX_MAIN_CONF|NGX_DIRECT_CONF|NGX_CONF_TAKE23,
	  ngx_thread_pool,
	  0,
	  0,
	  NULL },

	  ngx_null_command
};

static ngx_core_module_t ngx_thread_pool_module_ctx = {
		ngx_string("thread_pool"),
};

