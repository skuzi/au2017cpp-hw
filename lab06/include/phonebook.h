#pragma once

#include <stddef.h>

typedef struct human_s {
    char name[256];
    char middle_name[256];
    char family_name[256];
    char phones[10][21];
    size_t phones_cnt;
    char phone_to_add[21];
    size_t add_size;
} human_t;

typedef struct phonebook_s {
    human_t *humans;
    human_t human_to_add;
    size_t size;
    size_t capacity;
} phonebook_t;

int load_phonebook_xml(const char *filename, phonebook_t *book);
int save_phonebook_xml(const char *filename, phonebook_t *book);
void print_phonebook(phonebook_t *book);
void gen_phonebook(phonebook_t *book, size_t size);
void clear_phonebook(phonebook_t *book);
human_t get_human(phonebook_t *book, char* family_name);
void init_human(human_t *human);
void push_back_human(phonebook_t *book, human_t *human);
