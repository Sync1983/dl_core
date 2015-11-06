#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend.h"
#include "zend_hash.h"
#include "include/dl_core.h"
#include <dl_mb_string/dl_mb_string.c>

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
  long  delta_len = 0;
  long  offset    = 0;
  long  length    = 0;

  HashTable     *ht_array;
  ulong         min_length      = 0;
  dl_string     *p_text         = NULL,
                *p_array_text   = NULL,
                *str1           = NULL,
                *str2           = NULL;

  // Получаем аргументы функции. Внимание! Ошибка в типе аргументов приводет к SEGMENT FAULT
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_DC, "as|ll", &array, &text, &text_len, &offset, &length) == FAILURE) {
    RETURN_LONG(-1);
  }

  // Преобразуем zval в HashTable для удобства работы
  ht_array    = (HashTable *)Z_ARRVAL_P(array);
  // Разбираем многобайтную строку в структуру сравнения
  p_text      = dl_string_make(text, text_len);
  length      = (length == 0)? p_text->len : length;
  min_length  = (ulong) -1;
  // Перебираем все элементы массива. Определение см. dl_core.h
  foreach_start(ht_array,key,data,pos)

    dl_array_data *row;

    // Получаем данные или NULL
    row   = dl_get_array_data(data);
    if( row == NULL ){
      // Если данных нет - переходим к следующему элементу
      efree(row);
      foreach_continue(ht_array,pos);
    }

    p_array_text  = dl_string_make(row->text, row->text_len);    
    
    // Получаем подстроки с указанного смещения и минимальной длины
    str1 = dl_string_sub_ref(p_text,      offset,length);
    str2 = dl_string_sub_ref(p_array_text,offset,length);

    if( (p_array_text != NULL ) && (p_array_text->len < length) ) {
      delta_len = length - p_array_text->len;
    }

    // Вычисляем новое расстояние
    // Если изначально значение только создано - записываем в него расстояние,
    // Иначе - добавляем к уже существующему
    if( Z_LVAL_P(row->distance) == -1 ) {
      Z_LVAL_P(row->distance) = dl_string_calculate(str1, str2) + delta_len;
    } else {
      Z_LVAL_P(row->distance) += dl_string_calculate(str1, str2) + delta_len;
    }  

    if( Z_LVAL_P(row->distance) < min_length ){
      min_length = Z_LVAL_P(row->distance);
    }

    dl_string_free(str1);
    dl_string_free(str2);
    dl_string_free(p_array_text);
    efree(row);

  foreach_end(ht_array,pos)
  dl_string_free(p_text);

  RETURN_LONG(min_length);
}

PHP_FUNCTION(dl_filter)
{
  zval  *array    = NULL;
  ulong  bound    = 0;
  ulong  length   = 0;

  HashTable     *ht_array;
  zval          *new_array;
  dl_array_data *row;
  ulong  count   = 0;

  MAKE_STD_ZVAL(new_array);
  array_init(new_array);

  // Получаем аргументы функции. Внимание! Ошибка в типе аргументов приводет к SEGMENT FAULT
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_DC, "al|l", &array, &bound, &length) == FAILURE) {
    RETURN_LONG(-1);
  }

  // Преобразуем zval в HashTable для удобства работы
  ht_array    = (HashTable *)Z_ARRVAL_P(array);

  foreach_start(ht_array,key,data,pos)
          
    row   = dl_get_array_data(data);
    if( (row == NULL) ||
        (Z_LVAL_P(row->distance) > bound) ){
      // Если данных нет или расстояние больше граничного значения
      //  переходим к следующему элементу
      efree(row);
      foreach_continue(ht_array,pos);
    }

    if( (length > 0) && ( count >= length) ){
      efree(row);
      break;
    }

    /*zval *new_element;
    MAKE_STD_ZVAL(new_element);
    *new_element = **data;
    zval_copy_ctor(new_element);*/
    //zval_add_ref(data);
    add_index_zval(new_array,count++,*data);
    efree(row);
  foreach_end(ht_array,pos)
          
  RETVAL_ZVAL(new_array, 0, 0);
  efree(new_array);
}