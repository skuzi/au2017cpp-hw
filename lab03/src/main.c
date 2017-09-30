#include "clist.h"
#include <stdlib.h>

int main() {
	clist *s = malloc(sizeof(clist));
	s->size = 0;
	s->head = NULL;
	char *command = (char*)malloc(sizeof(char) * 5);
	while (1) {
		scanf("%s", command);
		if (strcmp(command, "add") == 0) {
			int x, y;
			scanf("%d%d", &x, &y);
			add(s, x, y);
		}
		else
			if (strcmp(command, "rm") == 0) {
				int x, y;
				scanf("%d%d", &x, &y);
				rm(s, x, y);
			}
			else
				if (strcmp(command, "rma") == 0) {
					clear(s);
				}
				else
					if (strcmp(command, "print") == 0) {
						print(s);
					}
					else
						if (strcmp(command, "len") == 0) {
							printf("%d\n", sz(s));
						}
						else
							if (strcmp(command, "exit") == 0) {
								exit(0);
							}
							else
								printf("Unknown command\n");
	}
	free(s);
	free(command);
}