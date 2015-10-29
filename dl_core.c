#include "php.h"
#include "zend_API.h"
#include "include/dl_core.h"

int dl_core_core(char *S1, char *S2, int N, int M)
{
  int D1 = 0, D2 = 0, D3 = 0, D4 = 0,distance = 0;
  
  if( MIN(N,M) <= 0 ){
    return MAX(N,M);    
  }
      
  char AN = S1[N-1];
  char BM = S2[M-1];
        
  if( (N > 2) && (M > 2) ){
               
    char AN1 = S1[N-2];
    char BM1 = S2[M-2];
                        
    if( (AN == BM1) && (AN1 == BM) ){
      
      D1 = dl_core_core(S1,S2,N-1,M) + 1;
      D2 = dl_core_core(S1,S2,N,M-1) + 1;
      D3 = dl_core_core(S1,S2,N-1,M-1);
      D4 = dl_core_core(S1,S2,N-2,M-2) + 1;
                                                        
      if( AN != BM ){
        D3 += 1;
      }
                                                              
      distance = MIN(D1,D2);
      distance = MIN(distance,D3);
      distance = MIN(distance,D4);
                                                        
      return distance;
    }    

  }
            
  D1 = dl_core_core(S1,S2,N-1,M) + 1;
  D2 = dl_core_core(S1,S2,N,M-1) + 1;
  D3 = dl_core_core(S1,S2,N-1,M-1);
                  
  if( AN != BM ){
    D3 += 1;
  }
                    
  distance = MIN(D1,D2);
  distance = MIN(distance,D3);
                        
  return distance;

} 


PHP_FUNCTION(dl_core)
{
  char *S1;
  char *S2;
  int N;
  int M;
  long distance = 0;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &S1, &N, &S2, &M) == FAILURE) {
    RETURN_NULL();
  } 

  distance = dl_core_core(S1,S2,N,M);
	
	RETURN_LONG(distance);
}

PHP_FUNCTION(dl_array)
{
  zval *array, **row;
  zval *sub_array;
  
  zvalue_value  arr_value;
  HashTable     *arr_hash;
  HashPosition  pointer;
  
  int   arr_count;  
  char  *text;  
  char  *text_part;  
  int   text_len;
  int   offset    = 0;
  
  long  distance = 0;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zsl", &array, &text, &text_len, &offset TSRMLS_DC) == FAILURE) {
    RETURN_FALSE;
  } 
  
  //Z_TYPE_PP(array) = IS_ARRAY;
  printf("%p\r\n", array);
  //printf("%p\r\n", Z_ARRVAL_PP(array));
  arr_count   = zend_hash_num_elements(Z_ARRVAL_P(array));
  printf("%d\r\n", arr_count);
  
  arr_hash  = Z_ARRVAL_P(array);
  //arr_count = zend_hash_num_elements(arr_hash);
  
  //text_part = (char *)emalloc(text_len + 2);
  //RETURN_LONG(arr_value.lval);
  //printf("%d", arr_value.lval);
  
  //zend_hash_internal_pointer_reset_ex(arr_hash, &pointer); 
  //      zend_hash_get_current_data_ex(arr_hash, (void**) &row, &pointer) == SUCCESS; 
  //      zend_hash_move_forward_ex(arr_hash, &pointer)) {
  for(  zend_hash_internal_pointer_reset_ex(arr_hash, &pointer); 
        zend_hash_get_current_data_ex(arr_hash, (void**) &row, &pointer) == SUCCESS; 
        zend_hash_move_forward_ex(arr_hash, &pointer)) {
  //  
      sub_array = Z_ARRVAL_PP(row);
      if( Z_TYPE_PP(row) != IS_ARRAY ){
        RETURN_FALSE;
      }
      printf("%d", Z_ARRVAL_PP(row)->nNumOfElements);
      add_assoc_long(Z_ARRVAL_PP(row),'distance',5);
  //  
  //  //RETURN_ZVAL(Z_ARRVAL_PP(row), 1, 0);// add_assoc_long(Z_ARRVAL_PP(row),"distance",5);
  }

  //efree(text_part);
  //distance = dl_core_core(S1,S2,N,M);
	
	RETURN_TRUE;
}
