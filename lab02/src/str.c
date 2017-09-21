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
   while (*str1 && *str2) {
    if (*str1 < *str2)
      return -1;
    if (*str1 > *str2)
      return 1;
    ++str1; ++str2;
  }
  return 0;
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
