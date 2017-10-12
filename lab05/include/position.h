#ifndef _POSITION_12102014_
#define _POSITION_12102014_

#include "clist.h"

typedef struct position_node {
    int x;
    int y;
    intrusive_node node;
} position_node;

void remove_position(intrusive_list* list, int x, int y);

position_node* get_position(intrusive_node* node);

void add_position(intrusive_list* list, int x, int y);

void show_all_positions(intrusive_list* list, char* fmt);

void next_position(intrusive_node* node, char* fmt);

void print_position(intrusive_node* node, char* fmt);

void remove_all(intrusive_list* list);

#endif