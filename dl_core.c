#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

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
  zval  **array;  
  char  *text;  
  int   text_len;
  int   offset    = 0;
  
  HashTable *ht_array;
  zval  *sub_array;
  char  *text_part;  
  long  distance = 0;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "As|l", &array, &text, &text_len, &offset) == FAILURE) {
    RETURN_FALSE;
  }   
   
  text_part = (char *)emalloc(text_len + 2);
  
  ht_array = (HashTable *)Z_ARRVAL_PP(array);  
  foreach_start(ht_array,key,data,pos);
          
    //sub_array = data;
    /*if( Z_TYPE_P(sub_array) != IS_ARRAY ){
      RETURN_FALSE;
    }*/
    //printf("%d", Z_TYPE_P(data));
    //add_assoc_long(sub_array, "distance" ,5);
    
  foreach_end(ht_array,pos)
  
  efree(text_part);
  //distance = dl_core_core(S1,S2,N,M);
	
	RETURN_TRUE;
}
