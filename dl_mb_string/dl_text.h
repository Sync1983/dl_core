#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
    (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)

#define DL_CHAR_POS(data,pos) *((data) + (pos))
#define DL_CHAR_COMPARE(data1,pos1,data2,pos2)  ( DL_CHAR_POS(data1,(pos1)) == DL_CHAR_POS(data2,(pos2)) )
#define IS_CONTINUE_BYTE(byte) ( (((byte) ^ 0x40) & 0xC0) == 0xC0 )
#define DL_STRING_LENGTH(string) ( ((dl_char)(string)).len )

typedef unsigned long dl_char;

typedef struct {
  unsigned long len;
  unsigned char is_ref;
  dl_char       *data;
} dl_string;

dl_string *     dl_string_make(char *str, unsigned long length);
void inline     dl_string_free(dl_string *str);

void            dl_string_print(dl_string *str);
dl_string *     dl_string_sub_ref(dl_string *string, unsigned long offset, unsigned long length);
unsigned long   dl_string_calculate(dl_string *str1, dl_string *str2);
