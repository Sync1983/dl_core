#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend.h"
#include "zend_hash.h"
#include "include/dl_core.h"

long dl_core_core(char *S1, char *S2, int N, int M)
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
  zval  *array;
  char  *text;  
  int   text_len;
  long  offset;
  
  HashTable *ht_array, *sub_array;
  char  *text_part;  

  // Получаем аргументы функции. Внимание! Ошибка в типе аргументов приводет к SEGMENT FAULT
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_DC, "asl", &array, &text, &text_len, &offset) == FAILURE) {
    RETURN_FALSE;
  }

  // Преобразуем zval в HashTable для удобства работы
  ht_array = (HashTable *)Z_ARRVAL_P(array);

  // Перебираем все элементы массива. Определение см. dl_core.h
  foreach_start(ht_array,key,data,pos);

    zval          *distance;
    zval          **cmp_val;
    char          *cmp_text;
    uint          cmp_text_len;
    
    // Получаем массив данных или NULL
    sub_array = Z_TYPE_PP(data) == IS_ARRAY ? Z_ARRVAL_PP(data) : NULL;

    if( sub_array == NULL ){
      foreach_continue(ht_array,pos);     // Если данных нет - уходим к след. элементу
    }
    
    if( zend_hash_exists(sub_array, "distance", sizeof("distance")) ){
      // Получаем ссылку на элемент массива
      zval **ppdistance = NULL;
      if( ( zend_hash_find(sub_array, "distance", sizeof("distance"), (void **)&ppdistance) != SUCCESS ) ||
          ( Z_TYPE_PP(ppdistance) == IS_NULL ) ){
        foreach_continue(ht_array,pos);     // Если данных нет - уходим к след. элементу
      }
      // Получаем значение указателя
      distance = *ppdistance;
    } else {
        // Если элемента нет - создаем его        
        // Создадим запись distance для добавления в массив
        MAKE_STD_ZVAL(distance);
        convert_to_long(distance);
        
        //Изначальную длинну выставляем в -1
        Z_LVAL_P(distance) = text_len;

        // Добавляем distance элемент в массив
        zend_hash_add(sub_array, "distance", sizeof("distance"), (void **)&distance, sizeof(zval), NULL);
    }

    // Получаем текст для сравнения
    // Если текста нет - продолжаем со следующим элементом
    if( ( zend_hash_find(sub_array, ZEND_STRS("text"), (void **)&cmp_val) != SUCCESS ) ||
        ( Z_TYPE_PP(cmp_val) != IS_STRING ) ){
        foreach_continue(ht_array,pos);
    }

    // Переводим текст из zval в char
    cmp_text        = Z_STRVAL_PP(cmp_val);
    cmp_text_len    = Z_STRLEN_PP(cmp_val);

    printf(" ====> %s [%d] <> %s [%d] <==== \r\n",text,text_len,cmp_text,cmp_text_len);

    if( cmp_text_len < offset ){
      foreach_continue(ht_array,pos)
    }

    if( (cmp_text_len + offset) < text_len ){
      Z_LVAL_P(distance) += dl_core_core(text, cmp_text + offset, cmp_text_len-offset, cmp_text_len-offset);
      foreach_continue(ht_array,pos)
    }


    long D1 = text_len, D2 = text_len, D3 = text_len;

    text_part = (char *)emalloc(text_len);
    memset(text_part, 0, text_len);

    // Сравниваем прямое совпадение частей
    memcpy(text_part, cmp_text + offset, text_len);
    D1 = dl_core_core(text, cmp_text + offset, text_len,text_len);
    printf("C Str: %.3s Len: %lu\r\n",text_part,D1);

    // Сравниваем совпадение смещенного на 1 символ влево текста ( аналог удаления символа на границе сравнения )
    if( offset > 0){
      //Сравниваем только при условии наличия символа слева
        memcpy(text_part, cmp_text + offset - 1, text_len);
        D2 = dl_core_core(text, cmp_text + offset - 1, text_len,text_len);
        printf("L Str: %.3s Len: %lu\r\n",text_part,D2);
    }

    // Сравниваем совпадение смещенного на 1 символ вправо текста ( аналог добавления символа на границе сравнения )
    if( cmp_text_len > (offset + text_len + 1) ){
      //Сравниваем только при условии наличия символа слева
      memcpy(text_part, cmp_text + offset + 1, text_len);
      D3 = dl_core_core(text, cmp_text + offset + 1, text_len,text_len);
      printf("L Str: %.3s Len: %lu\r\n",text_part,D3);
    }

    efree(text_part);
    // Выбираем наименьшую ошибку сравнений
    D1 = MIN(D1,D2);
    D1 = MIN(D1,D3);

    Z_LVAL_P(distance) += D1;
    
    foreach_end(ht_array,pos)
	
  RETURN_TRUE;
}
