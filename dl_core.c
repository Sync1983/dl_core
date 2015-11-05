#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend.h"
#include "zend_hash.h"
#include "include/dl_core.h"
#include <dl_mb_string/dl_mb_string.c>

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

dl_array_data * dl_get_array_data(zval **data)
{ 
  HashTable       *sub_array  = (HashTable *)((Z_TYPE_PP(data) == IS_ARRAY) ? Z_ARRVAL_PP(data) : NULL);
  dl_array_data   *result     = NULL;
  zval            **text_val  = NULL;

  if( sub_array == NULL ){
    return NULL;
  }
  
  result = (dl_array_data *) emalloc(sizeof(dl_array_data));

  if( zend_hash_exists(sub_array, "distance", sizeof("distance")) ){
    // Получаем ссылку на элемент массива
    zval **ppdistance = NULL;
    if( ( zend_hash_find(sub_array, "distance", sizeof("distance"), (void **)&ppdistance) != SUCCESS ) ||
        ( Z_TYPE_PP(ppdistance) == IS_NULL ) ){
        efree(result);
        return NULL;                              // Если данных нет - выходим
      }
      // Получаем значение указателя
      result->distance = *ppdistance;
  } else {
    zval *distance;
    // Если элемента нет - создаем его        
    MAKE_STD_ZVAL(distance);
    Z_TYPE_P(distance) = IS_LONG;
        
    //Изначальную длинну выставляем в максимальную ошибку
    Z_LVAL_P(distance) = -1;

    // Добавляем distance элемент в массив
    zend_hash_add(sub_array, "distance", sizeof("distance"), (void **)&distance, sizeof(zval), NULL);
    // Получаем указатель
    result->distance = distance;
  }

  // Получаем текст для сравнения
  // Если текста нет - выходим
  if( ( zend_hash_find(sub_array, ZEND_STRS("text"), (void **)&text_val) != SUCCESS ) ||
      ( Z_TYPE_PP(text_val) != IS_STRING ) ){
        efree(result);
        return NULL;
  }

  // Переводим текст из zval в char
  result->text      = Z_STRVAL_PP(text_val);
  result->text_len  = Z_STRLEN_PP(text_val);
  return result;
}

unsigned long dl_string_calculate(dl_string *str1, dl_string *str2)
{
  ulong N = 0, M = 0, D1 = 0, D2 = 0, D3 = 0, D4 = 0,distance = 0;
  unsigned char symbol_eq;

  N = (str1 == NULL)? 0 : (str1->len );
  M = (str2 == NULL)? 0 : (str2->len );

  if( MIN(N,M) == 0){
    return MAX(N,M);
  }

  symbol_eq = DL_CHAR_COMPARE(str1->data,N-1,str2->data,M-1)? 1 : 0;
  
  if( ( MIN(N,M)>2 ) &&
      ( DL_CHAR_COMPARE(str1->data,N-1,str2->data,M-2) ) &&
      ( DL_CHAR_COMPARE(str1->data,N-2,str2->data,M-1) ) ) {

      str1->len = N-1;
      str2->len = M;
      D1 = dl_string_calculate(str1,str2) + 1;

      str1->len = N-1;
      str2->len = M;
      D2 = dl_string_calculate(str1,str2) + 1;

      str1->len = N-1;
      str2->len = M-1;
      D3 = dl_string_calculate(str1,str2);      
      
      str1->len = N-2;
      str2->len = M-2;
      D4 = dl_string_calculate(str1,str2) + 1;      
                                                        
      if( symbol_eq == 0 ){
        D3 += 1;
      }
                                                              
      distance = MIN(D1,D2);
      distance = MIN(distance,D3);
      distance = MIN(distance,D4);
      
      str1->len = N;
      str2->len = M;
      return distance;
  }

  str1->len = N - 1;
  str2->len = M;
  D1 = dl_string_calculate(str1,str2) + 1;
  
  str1->len = N;
  str2->len = M-1;
  D2 = dl_string_calculate(str1,str2) + 1;
  
  str1->len = N-1;
  str2->len = M-1;
  D3 = dl_string_calculate(str1,str2);  

  if( symbol_eq == 0 ){
    D3 += 1;
  }

  distance = MIN(D1,D2);
  distance = MIN(distance,D3);

  str1->len = N;
  str2->len = M;
  return distance;
}

PHP_FUNCTION(dl_array)
{
  zval  *array    = NULL;
  char  *text     = NULL;
  long  text_len  = 0;
  long  offset    = 0;

  HashTable     *ht_array;
  ulong         min_length = 0;
  dl_string     *p_text         = NULL,
                *p_array_text   = NULL,
                *str1           = NULL,
                *str2           = NULL;

  // Получаем аргументы функции. Внимание! Ошибка в типе аргументов приводет к SEGMENT FAULT
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_DC, "as|l", &array, &text, &text_len, &offset) == FAILURE) {
    RETURN_FALSE;
  }

  // Преобразуем zval в HashTable для удобства работы
  ht_array    = (HashTable *)Z_ARRVAL_P(array);
  // Разбираем многобайтную строку в структуру сравнения
  p_text      = dl_string_make(text, text_len);    

  // Перебираем все элементы массива. Определение см. dl_core.h
  foreach_start(ht_array,key,data,pos)

    dl_array_data *row;

    // Получаем данные или NULL
    row   = dl_get_array_data(data);
    if( row == NULL ){
      // Если данных нет - переходим к следующему элементу
      foreach_continue(ht_array,pos);
    }

    p_array_text  = dl_string_make(row->text, row->text_len);
    min_length    = MIN(p_text->len,p_array_text->len);
    
    // Получаем подстроки с указанного смещения и минимальной длины
    str1 = dl_string_sub_ref(p_text,offset,min_length);
    str2 = dl_string_sub_ref(p_array_text,offset,min_length);

    //dl_string_print(str1);
    //dl_string_print(str2);

    // Вычисляем новое расстояние
    // Если изначально значение только создано - записываем в него расстояние,
    // Иначе - добавляем к уже существующему
    if( Z_LVAL_P(row->distance) == -1 ) {
      Z_LVAL_P(row->distance) = dl_string_calculate(str1, str2);
    } else {
      Z_LVAL_P(row->distance) += dl_string_calculate(str1, str2);
    }
  

    dl_string_free(str1);
    dl_string_free(str2);
    dl_string_free(p_array_text);
    efree(row);

  foreach_end(ht_array,pos)
  
  dl_string_free(p_text);



  RETURN_TRUE;
}