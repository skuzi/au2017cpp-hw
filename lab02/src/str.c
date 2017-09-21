#include "str.h"
//#include <stdio.h>

char * strcpy(char * destination, char * source){
   char * begin = destination;
   while((*destination++ = *source++));
   *destination = '\0';
   return begin;
}

char * strcat(char * str1, char * str2){
   char * begin = str1;
   while(*str1)
      str1++;
   while((*str1++ = *str2++));
   *str1 = '\0';
   return begin;
}

int strcmp(char * str1, char * str2){
   char *f = str1, *s = str2;
   while(*str1++ == *str2++){
      *f = *str1;
      *s = *str2;
   }
   return (*f - *s);
}

size_t strlen(char * str){
   char * p = str;
   while(*p++);
   return (size_t)(p - str - 1);
}

void printstr(char * s){
   while(*s){
      printf("%c", *s++);
   }
   printf("\n");
}
