#include "test_str.h"
#include "str.h"
void test(char *a, char *b){
   char dest[80] = "";
   strcpy(dest, a);
   printstr(dest);
   char *cat = strcat(dest, b);
   printstr(cat);
   size_t len = strlen(cat);
   printf("%zu\n", len);
   int cmp = strcmp(a, b);
   printf("%d\n", cmp);
}
   
