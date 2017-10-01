#pragma once

#include <stddef.h>
#include <stdlib.h>

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct intrusive_node{
	struct intrusive_node* next;
	struct intrusive_node* prev;
};

typedef struct intrusive_list
{
	struct intrusive_node* head;
	int size;
} clist;

clist* init_list();

void add_node(clist* c, struct intrusive_node* node);

void remove_node(clist* c, struct intrusive_node** node);
	
void clear(clist* c);

int get_length(clist* c);