#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend.h"
#include "zend_hash.h"
#include "include/dl_core.h"
#include "include/dl_text.h"


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

DL_PCHAR dl_string_sub(DL_PCHAR str, unsigned long start, unsigned long end)
{
  return NULL;
}

unsigned long dl_string_calculate(DL_PCMP compare)
{
  dl_cmp_str      *S1 = compare->S1, 
                  *S2 = compare->S2;
  DL_PCHAR        sub_str1;
  DL_PCHAR        sub_str2;
  unsigned long   sub_str1_len, 
                  sub_str2_len;
  
  if( (S1 == NULL)          || (S2 == NULL) ||
      (S1->from >= S1->to)  || (S2->from >= S2->to) ){
    return -1;
  }

  sub_str1_len  = S1->to - S1->from;
  sub_str2_len  = S2->to - S2->from;

  sub_str1 = dl_string_sub(S1->str, S1->from, S1->to);
  sub_str2 = dl_string_sub(S2->str, S2->from, S2->to);



  return 55;
}

PHP_FUNCTION(dl_array)
{
  zval  *array;
  char  *text;
  long  text_len;
  long  offset    = 0;

  HashTable     *ht_array;
  char          *text_part;
  DL_PCHAR      p_text;
  DL_PCHAR      p_array_text;
  DL_PCMP_STR   p_text_cmp;
  DL_PCMP_STR   p_array_cmp;
  DL_PCMP       compare;

  // Получаем аргументы функции. Внимание! Ошибка в типе аргументов приводет к SEGMENT FAULT
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_DC, "as|l", &array, &text, &text_len, &offset) == FAILURE) {
    RETURN_FALSE;
  }

  // Преобразуем zval в HashTable для удобства работы
  ht_array    = (HashTable *)Z_ARRVAL_P(array);
  // Разбираем многобайтную строку в структуру сравнения
  p_text      = dl_string_parse(text, text_len);
  // Создаем описание строки для сравнения
  DL_MAKE_COMPARE_STR(p_text_cmp);  
  p_text_cmp->str   = p_text;
  p_text_cmp->from  = offset;

  if( offset > dl_string_length(p_text) ){
    // Если смещение больше длины текста, то выходим
    DL_FREE_COMPARE_STR(p_text_cmp);
    dl_string_free(p_text);
    RETURN_FALSE;
  }

  p_text_cmp->to    = dl_string_length(p_text) - offset;

  // Создаем описание данных для сравнения
  DL_MAKE_COMPARE(compare);
  compare->S1       = p_text_cmp;
  compare->S2       = NULL;

  dl_string_print(p_text);

  // Перебираем все элементы массива. Определение см. dl_core.h
  foreach_start(ht_array,key,data,pos);
  
    dl_array_data *row;  
    
    // Получаем данные или NULL
    row   = dl_get_array_data(data);
    if( row == NULL ){
      // Если данных нет - переходим к следующему элементу
      foreach_continue(ht_array,pos);
    }
    
    p_array_text      = dl_string_parse(row->text, row->text_len);
    // Создаем строку сравнения из данных массива
    DL_MAKE_COMPARE_STR(p_array_cmp);
    p_array_cmp->str  = p_array_text;
    p_array_cmp->from = offset;

    if( dl_string_length(p_array_text) < offset ){
      DL_FREE_COMPARE_STR(p_array_cmp);
      dl_string_free(p_array_text);
      foreach_continue(ht_array,pos);
    }

    p_array_cmp->to   = dl_string_length(p_array_text) - offset;

    // Для сравнения выбираем наименьший остаток между текстом сравнения и текстом массива
    p_array_cmp->to   = MIN(p_text_cmp->to,p_array_cmp->to);
    // Заполняем стурктуру сравнения ссылкой на новую строку поиска
    compare->S2       = p_array_cmp;
  
    // Вычисляем новое расстояние
    // Если изначально значение только создано - записываем в него расстояние,
    // Иначе - добавляем к уже существующему
    if( Z_LVAL_P(row->distance) == -1 ) {
      Z_LVAL_P(row->distance) = dl_string_calculate(compare);
    } else {
      Z_LVAL_P(row->distance) += dl_string_calculate(compare);
    }

    dl_string_print(p_array_text);

    // Освобождаем память с данными
    dl_string_free(p_array_text);
    DL_FREE_COMPARE_STR(p_array_cmp);
    compare->S2       = NULL;
    efree(row);

    /*if( cmp_text_len < offset ){
      foreach_continue(ht_array,pos)
    }

    if( (cmp_text_len + offset) < text_len ){
      //Z_LVAL_P(distance) += dl_core_core(text, cmp_text + offset, cmp_text_len-offset, cmp_text_len-offset);
      foreach_continue(ht_array,pos)
    }


    //long D1 = text_len, D2 = text_len, D3 = text_len;

    //text_part = (char *)emalloc(text_len);
    //memset(text_part, 0, text_len);

    // Сравниваем прямое совпадение частей
    //memcpy(text_part, cmp_text + offset, text_len);
    //D1 = dl_core_core(text, cmp_text + offset, text_len,text_len);
    /*printf("C Str: %.3s Len: %lu\r\n",text_part,D1);

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
    }*/

    //efree(text_part);
    // Выбираем наименьшую ошибку сравнений
    //D1 = MIN(D1,D2);
    //D1 = MIN(D1,D3);

    //Z_LVAL_P(distance) += D1;
    
  foreach_end(ht_array,pos)

  // Очищаем данные
  dl_string_free(p_text);
  DL_FREE_COMPARE_STR(compare->S1);
  DL_FREE_COMPARE(compare);

  RETURN_TRUE;
}

dl_char * dl_string_parse(char *str, unsigned long length)
{
  unsigned long pos     = 0,
                str_pos = 0,
                byte_cnt= 0;
  unsigned char symbol  = 0,
                bit_cnt = 0;
  dl_char       *root   = NULL,
                *item   = NULL;

  if ( length == 0 ) {
    return NULL;
  }
  
  str_pos = 0;
  
  while( pos < length ){
    // Создаем указатель на символ
    // Если указатель на текущий элемент пустой, то создаем указатель на корень и текущий элемент
    if( item != NULL ) {
      DL_MAKE_PCHAR( PDL_NEXT(item) );
      PDL_NEXT(item)->prev = item;
      item = PDL_NEXT(item);
    } else {
      DL_MAKE_PCHAR(root);
      item = root;
      root->prev = NULL;
    }    
    // Следующйи элемент объявляем пустым и запоминаем номер текущего симовла
    PDL_NEXT(item)  = NULL;
    PDL_POS(item)   = str_pos++;
    // Берем следующий символ
    symbol = str[pos];

    // Для символа со старшим битом =0 запоминаем сам символ и продолжаем разбор
    if( !(symbol & 0x80) ){
      PDL_DATA(item)  = (unsigned int) symbol;
      PDL_LEN(item)   = 1;
      pos ++;
      continue;
    }
    // Для символа со старшим битом =1 считаем количество использованных байт
    bit_cnt       = 0;
    byte_cnt      = 1;                              // Разбираемый байт уже считается за значащий
    PDL_LEN(item) = 0;
    // Пока старший бит =1 - увеличиваем счетчик значащих байт
    while( symbol & 0x80 ){
      PDL_LEN(item)++;
      bit_cnt++;
      symbol <<= 1;
      // Если проверили все биты байта - берем следующий бит
      if( bit_cnt >= 7 ) {
        symbol    = str[pos++];
        byte_cnt++;                                 // Учитываем полное количество байт длины
        // Проверяем состояние старших двух бит - 10 означает продолжение последовательности
        if( (symbol & 0x80) && (symbol ^ 0x40) ){
          symbol <<= 2;                             // Если биты присутствуют - пропускаем их
        }
        bit_cnt = 0;
      }
    }

    // Посчитали длину. Оставщаяся часть symbol - значащая
    if( PDL_LEN(item) > 4 ){
      // По спецификации UTF-8 используются значения до 4-х байтов длинной.
      // Все символы с большей длинной считаем равнозначными
      // ВНИМАНИЕ!!! Может привести к ошибке!
      PDL_DATA(item) = 0x00;
      pos += PDL_LEN(item)-byte_cnt;
      continue;
    }

    // Сохраняем первый символ
    symbol          = str[pos++ - byte_cnt + 1];
    PDL_DATA(item)  = symbol;
    byte_cnt        = 0;
    // Добавляем все остальные символы    
    while( ++byte_cnt < PDL_LEN(item) ) {
      symbol = str[pos++];                      // Берем следующий за последним байтом с длиной и т.д.
      PDL_DATA(item) <<= 8;
      PDL_DATA(item) |= symbol;                 // Сохраняем значащие символы из остальных байт        
    }
  
  }  
  return root;  
}

void dl_string_free(DL_PCHAR str)
{
  DL_PCHAR next;

  while( str ) {
    next = PDL_NEXT(str);
    DL_FREE_PCHAR(str);
    str = next;
  }
  return;
}

unsigned long dl_string_length(DL_PCHAR str)
{
  if( !str ) {
    return 0;
  }

  while( PDL_NEXT(str) ) {
    str = (DL_PCHAR) PDL_NEXT(str);
  }

  return PDL_POS(str) + 1;
}

void dl_string_print(DL_PCHAR str)
{
  if( str == NULL) {
    printf("String is NULL\r\n");
  }
  while( str ){
    printf("Position: %lu ByteLength: %lu Data: 0x%xh \r\n", PDL_POS(str), PDL_LEN(str), PDL_DATA(str) );
    str = PDL_NEXT(str);
  }

  return; 
}


