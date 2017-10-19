#pragma once
#include "phonebook.h"

void start_element(void *data, const char *element, const char **attribute);
void end_element(void *data, const char *element);
void handle_data(void *data, const char *content, int length);
int parse_xml(char *buff, size_t buff_size, const char *filename, phonebook_t *book);