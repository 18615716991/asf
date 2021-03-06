/*
  +----------------------------------------------------------------------+
  | API Services Framework                                               |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Jiapeng Fan <fanjiapeng@126.com>                             |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_ASF_H
#define PHP_ASF_H

extern zend_module_entry asf_module_entry;
#define phpext_asf_ptr &asf_module_entry

#define PHP_ASF_VERSION "2.2.5"
#define PHP_ASF_AUTHOR  "fanjiapeng"
#define PHP_ASF_DESCRIPTION "High performance PHP framework written in C, Work so easy."

#ifdef PHP_WIN32
#	define PHP_ASF_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_ASF_API __attribute__ ((visibility("default")))
#else
#	define PHP_ASF_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#ifdef ZTS
#define ASF_G(v) TSRMG(asf_globals_id, zend_asf_globals *, v)
#else
#define ASF_G(v) (asf_globals.v)
#endif

#define ASF_INIT_CLASS(name) ZEND_MODULE_STARTUP_D(asf_ ##name)
#define ASF_INIT(name) ZEND_MODULE_STARTUP_N(asf_ ##name)(INIT_FUNC_ARGS_PASSTHRU)
#define ASF_API_NAME "api"
#define ASF_API_LEN	3

#define asf_router_t	zval
#define asf_route_t		zval
#define asf_service_t	zval
#define asf_loader_t	zval
#define asf_sg_t		zval
#define asf_logger_t	zval
#define asf_db_t		zval
#define asf_disp_t		zval

#define asf_http_req_t	zval
#define asf_http_rep_t	zval

enum logger_type {
    ASF_LOGGER_FILE,
    ASF_LOGGER_SYSLOG,
};

enum db_type {
    ASF_DB_MYSQL,
    ASF_DB_SQLITE,
    ASF_DB_PGSQL,
};

ZEND_BEGIN_MODULE_GLOBALS(asf)
	zend_string *root_path;
	zend_string *log_path;
	zend_string *root_path_route;
	zend_string *bootstrap;
	zend_string *constants;
	zend_string *base_uri;

	zend_string *default_module;
	zend_string *default_service;
	zend_string *default_action;
	zend_string *local_library;

	/* Loader */
	char *last_load_err_full_path;

    /* Router */
	zval		modules;
	zval		*route;
    
    /* Log */
	zval		log_buffer;
	zend_ulong	log_buffer_size;
	zend_ulong	log_buffer_count;
    zend_bool   log_sql; /* Asf_Sql_Log */
    zend_bool   log_err; /* Asf_Err_log */
    zend_bool   log_timeout; /* Asf_Timeout_Log */

	/* Ini */
	char		*environ_name;
	zend_bool	use_namespace;
	zend_ulong	ctype_id;
	zend_bool	use_lcache;

	/* Cache Config */
	HashTable *cache_config_buf;
	zend_ulong cache_config_last_time;
	zend_ulong cache_config_expire;
	zend_ulong cache_config_mtime;
	zend_bool  cache_config_enable;
	
	/* Dump, trace */
	zend_bool debug_dump;
	zend_bool trace_enable;
	zval trace_buf;

	/* Alarm, Execution time, Non-connected time */
	double script_start_time;
	double max_script_time; /* Script execution time */
	double max_db_time; /* MySQL, PgSQL, SQLite */
	double max_cache_time; /* Memcached, Redis, Mongo */
	double max_curl_time; /* Curl */

	/* Run Mode */
	zend_bool cli;

	/* App::setTimeoutHandler */
	zval timeout_func;  /* default value is UNDEF */

    /* Application::errorHandler(), Part of request_uri */
	zend_string *settled_uri;
ZEND_END_MODULE_GLOBALS(asf)

extern ZEND_DECLARE_MODULE_GLOBALS(asf);

#endif	/* PHP_ASF_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
