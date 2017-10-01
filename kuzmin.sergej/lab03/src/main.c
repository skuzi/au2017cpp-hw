#include "clist.h"
#include <stdio.h>
#include <string.h>

struct position_node {
	int x, y;
	struct intrusive_node node;
};


void add(clist* s, int x, int y) {
	struct position_node* new_node = malloc(sizeof(struct position_node));
	new_node->x = x;
	new_node->y = y;
	add_node(s, &new_node->node);
	s->size++;
}


void rm(clist* s, int x, int y) {
	struct intrusive_node* last = s->head;
	while (last != NULL) {
		struct position_node* item = container_of(last, struct position_node, node);
		if (item->x == x && item->y == y) {
			remove_node(s, &last);
			free(item);
		} else
			last = last->prev;
	}
	if (s->size == 0)
		s->head = NULL;	
}


void print(clist* s) {
	struct intrusive_node* last = s->head;
	while (last != NULL) {
		struct position_node* item = container_of(last, struct position_node, node);
		printf("(%d %d) ", item->x, item->y);
		last = last->prev;
	}
	printf("\n");
}

void clear(clist* s) {
	while (s->head != NULL) {
		struct intrusive_node* last = s->head->prev;
		free(container_of(s->head, struct position_node, node));
		s->head = last;
	}
	s->size = 0;
	s->head = NULL;
}

int main() {
	clist* s = init_list();
	char* command = (char*)malloc(sizeof(char)*  100);
	while (1) {
		if(scanf("%s", command));
		if (strcmp(command, "add") == 0) {
			int x, y;
			if(scanf("%d%d", &x, &y));
			add(s, x, y);
		}
		else if (strcmp(command, "rm") == 0) {
				
				int x, y;
				if(scanf("%d%d", &x, &y));
				rm(s, x, y);
			}
		else if (strcmp(command, "rma") == 0) {
				clear(s);
			}
		else if (strcmp(command, "print") == 0) {
				print(s);
			}
		else if (strcmp(command, "len") == 0) {
				printf("%d\n", get_length(s));
			}
		else if (strcmp(command, "exit") == 0) {
				clear(s);
				free(s);
				free(command);
				exit(0);
			}
		else
			printf("Unknown command\n");
	}
}