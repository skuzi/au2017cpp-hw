#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "parser.h"
#include "phonebook.h"


int compar(const void *a, const void *b) {
	human_t *h1 = (human_t*) a;
	human_t *h2 = (human_t*) b;
	return strcmp(h1->family_name, h2->family_name); 
}

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("usage ./main <infile> <outfile>\n");
		return 1;
	}
	phonebook_t *book = malloc(sizeof(phonebook_t));
	book->capacity = 1;
	book->size = 0;
	book->humans = malloc(sizeof(human_t));
	if(load_phonebook_xml(argv[1], book))
		return 1;
	qsort(book->humans, book->size, sizeof(human_t), compar);
	print_phonebook(book);
	srand(time(NULL));
	gen_phonebook(book, rand() % 50);
	save_phonebook_xml(argv[2], book);
	clear_phonebook(book);
	free(book);
}