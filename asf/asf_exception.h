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

#ifndef ASF_EXCEPTION_H
#define ASF_EXCEPTION_H

#define ASF_ERR_STARTUP_FAILED 		900
#define ASF_ERR_ROUTE_FAILED 		901
#define ASF_ERR_DISPATCH_FAILED 	902
#define ASF_ERR_AUTOLOAD_FAILED 	903
#define ASF_ERR_BOOTSTRAP_FAILED    904

#define ASF_ERR_LOADER_FAILED		905
#define ASF_ERR_LOADER_CLASSNAME	906

#define ASF_ERR_NOTFOUND_MODULE 	907
#define ASF_ERR_NOTFOUND_SERVICE	908
#define ASF_ERR_NOTFOUND_ACTION 	909
#define ASF_ERR_DIS_SERVICE         910
#define ASF_ERR_DIS_ACTION          911

#define ASF_ERR_CONSTANTS_FAILED 	912

#define ASF_ERR_NOTFOUND_CONSTANTS_CLASS 	913
#define ASF_ERR_NOTFOUND_CONSTANTS_TABLE 	914
#define ASF_ERR_NOTFOUND_CONSTANTS_PROP		915

#define ASF_ERR_DB_OPTIONS_DSN			916
#define ASF_ERR_DB_OPTIONS_USERNAME		917
#define ASF_ERR_DB_PDO_CE				918
#define ASF_ERR_DB_PREPARE				919
#define ASF_ERR_DB_EXECUTE				920
#define ASF_ERR_DB_TABLE				921
#define ASF_ERR_DB_SET_COLUMN			922
#define ASF_ERR_DB_PARAM				923
#define ASF_ERR_DB_QB                   924

#define ASF_ERR_CONFIG_PARAM            925
#define ASF_ERR_COOKIE_PUBLIC           926

/* cache */
#define ASF_ERR_CACHE_MODULE            930
#define ASF_ERR_CACHE_OPTIONS           931
#define ASF_ERR_CACHE_AUTH              932
#define ASF_ERR_CACHE_OTHERS            933
#define ASF_ERR_CACHE_CONNECT           934

/* 990 ~ 999 : Exception Error Range */
/* 970 ~ 989 : Execution Time Error Range */

extern zend_class_entry *asf_exception_ce;

void asf_trigger_error(int code, char *format, ...);

ASF_INIT_CLASS(exception);

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
