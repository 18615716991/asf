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

#ifndef ASF_FUNC_H
#define ASF_FUNC_H

#define ASF_FAST_STRING_PTR_DTOR_P(z) zend_string_release(Z_STR_P(z))
#define ASF_FAST_STRING_PTR_DTOR(z) zend_string_release(Z_STR(z))
#define ASF_FUNC_PRONAME_CONNECT_INFO "_connect_info"

enum TRACE_ID {
    ASF_TRACE_MYSQL,
    ASF_TRACE_REDIS,
    ASF_TRACE_MEMCACHED,
    ASF_TRACE_PGSQL,
    ASF_TRACE_SQLITE,
    ASF_TRACE_CURL,
    ASF_TRACE_SCRIPT
};

_Bool asf_func_isempty(const char *s);

/* Logger */
_Bool asf_func_shutdown_buffer();

void asf_func_set_cur_module(char *module);

/* Driver */
zend_class_entry *asf_find_driver(const char *class_name, unsigned int class_name_len);

void asf_func_format_args(zval *args, zval **retval, size_t *arg_count);

/* Cache Config */
void asf_func_config_persistent_hash_destroy(HashTable *ht);
double asf_func_gettimeofday();

/* trace */
double asf_func_trace_gettime();
void asf_func_trace_str_add(uint trace_id, double start_time, char *method, size_t method_len,
        uint32_t param_count, zval params[], zval *retval);
void asf_func_trace_zval_add(uint trace_id, double start_time, zval *method,
        uint32_t param_count, zval params[], zval *retval);

#define ASF_FUNC_REGISTER_SHUTDOWN_FUNCTION_CLOSE(this_ptr, need_refcount) { \
    ASF_FUNC_CALL_PHP_FUNC(this_ptr, "register_shutdown_function", "close", 5, NULL, need_refcount); \
}

#define ASF_FUNC_CALL_PHP_FUNC(self, php_method, method, method_len, ret, need_refcount) do { /*{{{*/ \
    zval handler; \
    array_init(&handler); \
    if (need_refcount) { \
        Z_TRY_ADDREF_P(self); \
    } \
    add_index_zval(&handler, 0, self); \
    add_index_stringl(&handler, 1, method, method_len); \
    zend_call_method_with_1_params(NULL, NULL, NULL, php_method, ret, &handler); \
    zval_ptr_dtor(&handler); \
} while(0)
/* }}} */

#define ASF_CALL_USER_FUNCTION_EX(self, method, method_len, retval, args_i, args) do { /*{{{*/ \
    zval zmn; \
    ZVAL_STRINGL(&zmn, method, method_len); \
    call_user_function_ex(&Z_OBJCE_P(self)->function_table, self, &zmn, retval, args_i, args, 1, NULL); \
    ASF_FAST_STRING_PTR_DTOR(zmn); \
} while(0)
/* }}} */

#define ASF_FUNC_REGISTER_SHUTDOWN_FUNCTION(class_name, method, method_len) do { /*{{{*/ \
    zval handler; \
    array_init(&handler); \
    add_index_str(&handler, 0, class_name); \
    add_index_stringl(&handler, 1, method, method_len); \
    zend_call_method_with_1_params(NULL, NULL, NULL, "register_shutdown_function", NULL, &handler); \
    zval_ptr_dtor(&handler); \
} while (0)
/* }}} */

php_stream *asf_func_fopen(const char *fpath, size_t fpath_len, zend_string *dpath);

int asf_func_array_isset(const zval *arr, const zval *index);
int asf_func_array_del(const zval *arr, const zval *index);
zval *asf_func_array_fetch(const zval *arr, const zval *index);
_Bool asf_func_alarm_stats(uint trace_id, double start_time, char *method, zval *params, zval *this_ptr);

#define ASF_METHOD_CALL(trace_id, name, zsname) /*{{{*/ \
PHP_METHOD(name, __call) \
{ \
    zval *function_name = NULL; \
    zval *args = NULL, *real_args = NULL; \
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "za", &function_name, &args) == FAILURE) { \
        return; \
    } \
    zval *self = getThis(); \
    zval *handler = zend_read_property(name ## _ce, self, ZEND_STRL(zsname), 1, NULL); \
    if (UNEXPECTED(Z_TYPE_P(handler) != IS_OBJECT)) { \
        RETURN_FALSE; \
    } \
    size_t arg_count = 0; \
    (void)asf_func_format_args(args, &real_args, &arg_count); \
    double start_time = asf_func_trace_gettime(); \
    zend_string *func = zval_get_string(function_name); \
    call_user_function_ex(&Z_OBJCE_P(handler)->function_table, handler, function_name, return_value, arg_count, real_args, 1, NULL); \
    (void)asf_func_alarm_stats(trace_id, start_time, ZSTR_VAL(func), real_args, self); \
    (void)asf_func_trace_zval_add(trace_id, start_time, function_name, arg_count, real_args, return_value); \
    if (arg_count > 0) { \
        efree(real_args); \
    } \
    /* When the method is not found, the result is 'UNKNOWN:0' */ \
    if (Z_ISUNDEF_P(return_value)) { \
        php_error_docref(NULL, E_WARNING, "Method name '%s' not found", ZSTR_VAL(func)); \
        ZVAL_FALSE(return_value); \
    } \
    zend_string_release(func); \
} \
/* }}} */

void asf_func_timeout_db(double start_time, const char *type, char *method);
_Bool asf_func_trace_clear();

void asf_log_adapter_write_file(const char *fname, size_t fname_len, const char *method, uint method_len, const char *msg, size_t msg_len);

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
