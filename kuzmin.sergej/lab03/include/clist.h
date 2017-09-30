#pragma once
#include <stdio.h>
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

//REALIZATION OF INTRUSIVE LIST

struct intrusive_node{
	struct intrusive_node *next = NULL;
	struct intrusive_node *prev = NULL;
};


struct position_node{
	int x, y;
	intrusive_node *node;
};


typedef struct intrusive_list{
	struct intrusive_node *head = NULL;
	int size = 0;
	void add_node(struct intrusive_node *node){
		if(head != NULL){
			node->prev = head;
			node->next = NULL;
			head->next = node;
		}
		head = node;
	}


	void add(int x, int y){
		struct position_node *new_node = malloc(sizeof(struct position_node));
		new_node->x = x;
		new_node->y = y;
		add_node(&new_node->node);
		size++;
	}


	void remove(int x, int y){
		struct intrusive_node *last = head;
		while(last != NULL){
			struct position_node *item = container_of(last, position_node, intrusive_node);
			if(item->x == x && item->y == y){
				if(last->prev != NULL){
					last->prev->next = last->next;
					last->next->prev = last->prev;
				}
				else{
					last->prev->next = NULL;
					head = last->prev; 
				}
				last = last->prev;
				size--;
				free(item);
			}
		}
	}


	void print(){
		struct intrusive_node *last = head;
		while(last != NULL){
			struct position_node *item = container_of(last, position_node, intrusive_node);
			printf("(%d %d) ", item->x, item->y);
			last = last->prev;
		}
		printf("\n");
	}


	void clear(){
		while(head != NULL){
			struct intrusive_node *last = head->prev;
			free(container_of(head, position_node, intrusive_node));
			head = last;
		}
		size = 0;
	}


	int len(){
		return size;
	}

} clist;