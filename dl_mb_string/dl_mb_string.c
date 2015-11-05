#include "php.h"
#include "dl_text.h"

dl_string * dl_string_make(char* str, unsigned long length)
{
  dl_string  *string  = NULL;
  ulong       pos     = 0;
  ulong       data    = 0;
  char        symbol  = 0;  
  ulong       cur_pos = 0;
  
  string          = (dl_string *) emalloc(sizeof(dl_string));
  string->is_ref  = 0;
  string->data    = (dl_char *)   emalloc( sizeof(dl_char)*length);
  memset(string->data, 0, sizeof(dl_char)*length);
  
  //cur_pos = string->data;
  pos = 0;
  while( pos < length ) {    
    symbol = str[pos];    
    // Проверяем старший бит
    if( symbol & 0x80 ){
      // Если он =1, значит символ многобайтовый
      data    = 0;
      // Переносим данные из байтовой строки в структуру до тех пор,
      //   пока следующий символ имеет признак продолжения строки
      // ВНИМАНИЕ!!! Спец-я UTF-8 рекомендует использовать до 4-х байт
      //   Количество байт больше 4-х будет обрезано до последних байт
      do{        
        data <<= 8;
        data += (unsigned char)symbol;
        symbol = str[++pos];
      }while(IS_CONTINUE_BYTE(symbol));
      DL_CHAR_POS(string->data,cur_pos++) = (dl_char) data;      
    } else {
      // Если он =0, то переписываем значение позиции
      // И переходим к следующему элементу
      DL_CHAR_POS(string->data,cur_pos++) = (dl_char) symbol;
      pos++;
    }
  }
  string->len = cur_pos;
  return string;
  
}

void inline dl_string_free(dl_string *string)
{
  if( string == NULL ){
    return;
  }
  
  if( string->is_ref == 0 ){
    efree(string->data);
    string->data = NULL;
  }
  efree(string);
  string = NULL;
}

void dl_string_print(dl_string *string)
{
  ulong pos = 0;
  
  if( string == NULL){
    printf("String is empty\r\n");
    return;
  }

  printf("String length [%lu] Bytes: ",string->len);
  for(;pos < string->len; pos++){
    printf("0x%X ",(uint) *(string->data + pos) );
  }
  printf("\r\n");
  
}

dl_string * dl_string_sub_ref(dl_string *string, unsigned long offset, unsigned long length)
{
  dl_string *new_string = NULL;
  
  if( (string == NULL) ||
      (string->len == 0) ||
      (offset >= string->len) ||
      (length == 0) ) {
    return NULL;
  }
  
  new_string = (dl_string *) emalloc(sizeof(dl_string));
  memset(new_string,0,sizeof(dl_string));
  new_string->is_ref = 1;
  new_string->len = MIN(string->len - offset, length);
  new_string->data = string->data + offset;
  return new_string;
}