/* 
 * File:   dl_core.h
 * Author: sync1983
 *
 * Created on 28 октября 2015 г., 13:28
 */

#ifndef DL_CORE_H
#define DL_CORE_H

#ifdef ZTS
  #include "TSRM.h"
#endif

#define PHP_DL_CORE_VERSION "0.1"

PHP_FUNCTION(dl_core);
PHP_FUNCTION(dl_array);

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define foreach_start(array,key,data,pointer)   \
  HashPosition  pointer;                        \
  zval   *key, **data;                           \
  zend_hash_internal_pointer_reset_ex(          \
    (array),                                    \
    &pointer);                                  \
  while ( zend_hash_get_current_data_ex(        \
              (array ),                         \
              (void **)&data,                   \
              &pointer                          \
            ) == SUCCESS) {                    
    
#define foreach_continue(array,pointer)         \
  zend_hash_move_forward_ex(        \
    (array),                        \
    &pointer);                      \
    continue;

#define foreach_end(array, pointer) \
  zend_hash_move_forward_ex(        \
    (array),                        \
    &pointer);                      \
  }


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
    PHP_DL_CORE_VERSION,
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(dl_core)
//#ifdef COMPILE_DL_HELLO
//#endif

#endif /* DL_CORE_H */