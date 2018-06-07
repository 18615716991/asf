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

#ifndef ASF_DEBUG_DUMP_ABSDUMP_H
#define ASF_DEBUG_DUMP_ABSDUMP_H

#define ASF_DEBUG_DUMP_PRONAME_MODE "_m"

/* {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_asf_zval_dump, 0, 0, 1)
	ZEND_ARG_VARIADIC_INFO(0, vars)
ZEND_END_ARG_INFO()
/* }}} */

extern zend_class_entry *asf_debug_dump_abstractdump_ce;

ASF_INIT_CLASS(debug_dump_abstractdump);

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
