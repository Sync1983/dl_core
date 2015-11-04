
#define DL_MAKE_PCHAR(name) (name) = (dl_char *) emalloc(sizeof(dl_char)); \
                            memset( (name) ,0,sizeof(dl_char));
#define DL_FREE_PCHAR(name) efree( (name) );

#define DL_MAKE_COMPARE_STR(name) (name) = (DL_PCMP_STR) emalloc(sizeof(dl_cmp_str));\
                            memset( (name) , 0, sizeof(dl_cmp_str));
#define DL_FREE_COMPARE_STR(name) efree( (name) );
 
#define DL_MAKE_COMPARE(name) (name) = (dl_cmp *) emalloc(sizeof(dl_cmp));\
                            memset( (name) , 0, sizeof(dl_cmp));
#define DL_FREE_COMPARE(name) efree( (name) );

#define DL_POS(name)  (name).pos
#define DL_LEN(name)  (name).len
#define DL_DATA(name) (name).data
#define DL_NEXT(name) (name).next

#define PDL_POS(name)  DL_POS(*name)
#define PDL_LEN(name)  DL_LEN(*name)
#define PDL_DATA(name) DL_DATA(*name)
#define PDL_NEXT(name) DL_NEXT(*name)

#define DL_PCHAR dl_char *
#define DL_PCMP_STR dl_cmp_str *    
#define DL_PCMP dl_cmp *

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

typedef struct dl_char{
  unsigned long   pos; 
  unsigned long   len; 
  unsigned int    data;
  struct dl_char  *next;
  struct dl_char  *prev;
} dl_char;

typedef struct dl_cmp_str{
  DL_PCHAR        str;
  unsigned long   from;
  unsigned long   to;
} dl_cmp_str;

typedef struct dl_cmp{
  dl_cmp_str    *S1;
  dl_cmp_str    *S2;
} dl_cmp;

dl_char * dl_string_parse(char *str, unsigned long length);
void dl_string_free(DL_PCHAR str);

unsigned long dl_string_length(DL_PCHAR str);
unsigned long dl_string_calculate(DL_PCMP compare);
DL_PCHAR dl_string_sub(DL_PCHAR str, unsigned long start, unsigned long end);

void dl_string_print(DL_PCHAR str);
