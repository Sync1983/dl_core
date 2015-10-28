/* 
 * File:   dl_core.h
 * Author: sync1983
 *
 * Created on 28 октября 2015 г., 13:28
 */

#ifndef DL_CORE_H
#define DL_CORE_H

#include "php.h"
#include "zend_modules.h"
#include "zend_API.h"

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_FUNCTION(dl_core);
PHP_FUNCTION(dl_array);

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

static zend_function_entry dl_core_functions[] = {
    PHP_FE(dl_core, NULL)
    PHP_FE(dl_array, NULL)    
    {NULL, NULL, NULL}
};

zend_module_entry dl_core_module_entry = {
    STANDARD_MODULE_HEADER,
    "dl_core",
    dl_core_functions,
    NULL,                     //PHP_MINIT(dl_core),
    NULL,                     //PHP_MSHUTDOWN(dl_core),
    NULL,                     //PHP_RINIT(dl_core),
    NULL,
    NULL,
    "0.1",
    STANDARD_MODULE_PROPERTIES
};


ZEND_GET_MODULE(dl_core)


#endif /* DL_CORE_H */