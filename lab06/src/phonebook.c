#include "phonebook.h"
#include "names.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


int load_phonebook_xml(const char *filename, phonebook_t *book) {
	srand(time(NULL));
	char* buffer = malloc(10000);
	int ret = parse_xml(buffer, 10000, filename, book);
	free(buffer);
	return ret;
}

void indent(FILE *f, size_t size) {
	for(int i = 0; i < size; i++)
		fprintf(f, "    ");
}

int save_phonebook_xml(const char *filename, phonebook_t *book) {
	FILE *fout = fopen(filename, "w");
	if(fout == NULL) {
 		printf("Failed to open file %s\n", filename);
        return 1;	
    }
    fprintf(fout, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<phonebook>\n");
    size_t ind = 1;
    for(int i = 0; i < book->size; i++) {
    	indent(fout, ind++);
    	fprintf(fout, "<human name=\"%s %s %s\">\n", book->humans[i].name, book->humans[i].middle_name, book->humans[i].family_name);
    	for(int j = 0; j < book->humans[i].phones_cnt; j++) {
    		indent(fout, ind);
    		fprintf(fout, "<phone>%s</phone>\n", book->humans[i].phones[j]);
    	}
    	indent(fout, --ind);
    	fprintf(fout, "</human>\n");
    }
    fprintf(fout, "</phonebook>");
    fclose(fout);
	return 0;
}

void print_phonebook(phonebook_t *book) {
	printf("%zu\n", book->size);
	for(int i = 0; i < book->size; i++) {
		printf("name: %s\n", book->humans[i].name);
		printf("middle name: %s\n", book->humans[i].middle_name);
		printf("family name: %s\n", book->humans[i].family_name);
		for(int j = 0; j < book->humans[i].phones_cnt; j++) {
			printf("phone: %s\n", book->humans[i].phones[j]);
		}
		if(i != book->size - 1)
			printf("\n");
	}
}

void gen_phonebook(phonebook_t *book, size_t size) {
	clear_phonebook(book);
	book->humans = malloc(sizeof(human_t));
	for(int i = 0; i < size; i++) {
		human_t *human = malloc(sizeof(human_t));
		init_human(human);
		strcpy(human->family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);
		strcpy(human->name, kNames[rand() % NAMES_CNT]);
		strcpy(human->middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
		size_t PhonesCnt = rand() % 10 + 1;
		human->phones_cnt = PhonesCnt;
		for(int j = 0; j < PhonesCnt; j++) {
			size_t PhoneSize = rand() % 20 + 1;
			for(int k = 0; k < PhoneSize; k++) {
				human->phones[j][k] = (rand() % 10) + '0';
			}
		}
		push_back_human(book, human);
		free(human);
	}
}

void clear_phonebook(phonebook_t *book) {
	free(book->humans);
	book->size = 0;
	book->capacity = 1;
}

human_t get_human(phonebook_t *book, char* family_name) {
	for(int i = 0; i < book->size; i++) {
		if(!strcmp(book->humans[i].family_name, family_name))
			return book->humans[i];
	}
	exit(EXIT_FAILURE);
}

void push_back_human(phonebook_t *book, human_t *human) {
	if(book->size == book->capacity) {
		//printf("%zu\n", book->capacity);
		book->capacity *= 2;
		book->humans = realloc(book->humans, book->capacity * sizeof(human_t));
	}
	book->humans[book->size++] = *human;
}

void init_human(human_t *human) {
	human->phones_cnt = 0;
	human->add_size = 0;
	memset(human->phone_to_add, 0, 21);
    memset(human->family_name, 0, 256);
    memset(human->middle_name, 0, 256);
    memset(human->name, 0, 256);
    memset(human->phones, 0, 10*21);
}