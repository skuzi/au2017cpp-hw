#include "mergesort.h"

int cmpInt(void* aa, void* bb){
	int* a = aa;
	int* b = bb;
	return (*a - *b);
}

int cmpChr(void* aa, void* bb){
	char* a = aa;
	char* b = bb;
	return (*a - *b);
}

int strcmp1(void* s1, void* s2){
	char** str1 = s1;
	char** str2 = s2;
	return strcmp(*str1, *str2); 
}

int main(int argc, char* argv[]) {
	if(argv[2] == NULL){
		printf("\n");
		return 0;
	}
	if(strcmp(argv[1], "int") == 0){
		int* arr = malloc(sizeof(int) * (argc - 2));
		int* begin = arr;
		for(int i = 1; i < argc - 1; i++)
			arr[i - 1] = atoi(argv[i + 1]);
		mergesort(begin, argc - 2, sizeof(int), cmpInt);

		for(int i = 0; i < argc - 2; i++)
			printf("%d ", arr[i]);
		free(begin);
	}
	else if(strcmp(argv[1], "char") == 0){
		char* arr = malloc(sizeof(char) * (argc - 2));
		char* begin = arr;
		
		for(int i = 1; i < argc - 1; i++)
			arr[i - 1] = argv[i + 1][0];

		mergesort(begin, argc - 2, sizeof(char), cmpChr);

		for(int i = 0; i < argc - 2; i++)
			printf("%c ", arr[i]);
		free(begin);
	}
	else if(strcmp(argv[1], "str") == 0){
		char** arr = malloc(sizeof(char*) * (argc - 2));
		char** begin = arr;

		for(int i = 1; i < argc - 1; i++){
			arr[i - 1] = malloc(sizeof(char*) * strlen(argv[i + 1]));
			strcpy(arr[i - 1], argv[i + 1]);
		}

		mergesort(begin, argc - 2, sizeof(char*), strcmp1);

		for(int i = 0; i < argc - 2; i++)
			printf("%s ", arr[i]), free(arr[i]);
		free(begin);
	}
	return 0;
}