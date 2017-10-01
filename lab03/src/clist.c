#include "clist.h"


//REALIZATION OF INTRUSIVE LIST

clist* init_list(){
	clist* s = malloc(sizeof(clist));
	s->size = 0;
	s->head = NULL;
	return s;
}


void add_node(clist* s, struct intrusive_node* node) {
	node->prev = NULL;
	node->next = NULL;
	if (s->head != NULL) {
		node->prev = s->head;
		node->next = NULL;
		s->head->next = node;
	}
	s->head = node;
}


void remove_node(clist* s, struct intrusive_node** last){
	if ((*last)->next != NULL)
			(*last)->next->prev = (*last)->prev;
	else
		s->head = (*last)->prev;
	if ((*last)->prev != NULL)
		(*last)->prev->next = (*last)->next;
	s->size--;
	*last = (*last)->prev;
}


int get_length(clist* s) {
	return s->size;
}