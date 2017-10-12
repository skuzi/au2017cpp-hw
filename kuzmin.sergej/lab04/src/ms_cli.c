#include "mergesort.h"

struct Context{
	int size;
	void (*read)(void* arr, char* args);
	int (*cmp)(void* a, void* b);
	void (*print)(void* arr);
};

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


int cmpStr(void* s1, void* s2){
	char** str1 = s1;
	char** str2 = s2;
	return strcmp(*str1, *str2); 
}

void read_int(void* arr, char* args){
	*((int*)arr) = atoi(args);
}

void read_char(void* arr, char* args){
	*((char*)arr) = *args;
}

void read_str(void* arr, char* args){
	*((char**)arr) = args;
}

void print_char(void* arr){
	printf("%c", *((char*)arr));
}

void print_str(void* arr){
	printf("%s", *((char**)arr));
}

void print_int(void* arr){
	printf("%d", *((int*)arr));
}

int main(int argc, char* argv[]) {
	int n = argc - 2;
	struct Context* ctx = malloc(sizeof(struct Context));
	if(strcmp(argv[1], "int") == 0){
		ctx->read = read_int;
		ctx->print = print_int;
		ctx->cmp = cmpInt;
		ctx->size = sizeof(int);
	}
	else if(strcmp(argv[1], "char") == 0){
		ctx->read = read_char;
		ctx->print = print_char;
		ctx->cmp = cmpChr;
		ctx->size = sizeof(char);
	}
	else if(strcmp(argv[1], "str") == 0){
		ctx->read = read_str;
		ctx->print = print_str;
		ctx->cmp = cmpStr;
		ctx->size = sizeof(char*);
	}

	void* arr = malloc(n * ctx->size);
	for(int i = 0; i < n; i++)
		ctx->read(arr + i * ctx->size, argv[i + 2]);
	mergesort(arr, n, ctx->size, ctx->cmp);
	for(int i = 0; i < n; i++){
		ctx->print(arr + i * ctx->size);
		printf(" ");
	}
	free(arr);
	free(ctx);
	return 0;
}