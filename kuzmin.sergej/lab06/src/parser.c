#include <expat.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "phonebook.h"

#define BUFFER_SIZE 100000

void start_element(void *data, const char *element, const char **attribute) {
    phonebook_t *book = *((phonebook_t**)data);
    //printf("start_element %s", element);
    //int i = 0;
    //for (i = 0; attribute[i]; i += 2) {
    //    printf(" %s= %s ", attribute[i], attribute[i + 1]);
    //}
    //printf("\n");
    if(!strcmp(element, "phone")) {
        book->human_to_add.add_size = 0;
    }
    else if(!strcmp(element, "human")) {
        init_human(&(book->human_to_add));
        size_t len = strlen(attribute[1]) + 1;
        char* Name = malloc(len);
        strncpy(Name, attribute[1], len);
        char* pch = strtok(Name, " ");
        strncpy(book->human_to_add.name, pch, strlen(pch));
        pch = strtok(NULL, " ");
        strncpy(book->human_to_add.middle_name, pch, strlen(pch));
        pch = strtok(NULL, " ");
        strncpy(book->human_to_add.family_name, pch, strlen(pch));
        free(Name);
    }
}

void end_element(void *data, const char *element) {
    //printf("end_element %s\n", element);
    phonebook_t *book = *((phonebook_t**)data);
    if(!strcmp(element, "phone")) {
        strncpy(book->human_to_add.phones[book->human_to_add.phones_cnt++], book->human_to_add.phone_to_add, strlen(book->human_to_add.phone_to_add));
        //printf("phone =  %s\n", book->human_to_add.phones[book->human_to_add.phones_cnt - 1]);
        //printf("size = %zu\n", book->human_to_add.phones_cnt);

    }
    else if(!strcmp(element, "human")) {
        if(book == NULL)
            exit(0);
        push_back_human(book, &(book->human_to_add));
    }
}

void handle_data(void *data, const char *content, int length) {
    phonebook_t *book = *((phonebook_t**)data);
    char *tmp = malloc(length + 1);
    strncpy(tmp, content, length);
    tmp[length] = '\0';
    for(int i = 0; i < length; i++){
        if(tmp[i] >= '0' && tmp[i] <= '9'){
            book->human_to_add.phone_to_add[book->human_to_add.add_size++] = tmp[i];
        }
    }
    free(tmp);
}

int parse_xml(char *buff, size_t buff_size, const char *filename, phonebook_t *book) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file %s\n", filename);
        return 1;
    }

    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetUserData(parser, &book);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);

    memset(buff, 0, buff_size);

    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), buff_size, fp);
        done = len < buff_size;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));

            XML_ParserFree(parser);
            fclose(fp);
            return 2;
        }
    } while (!done);

    XML_ParserFree(parser);
    fclose(fp);

    return 0;
}