#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "position.h"
#include "clist.h"

char* fmt;

typedef struct Context {
    size_t size;
    int stop;
    int (*read)(int* x, int* y, size_t size, FILE* fin);
    size_t (*action)(intrusive_list* list);
    void (*save)(FILE* fout, size_t size, int x, int y);

} Context;

void apply(intrusive_list* list, void (*op)(intrusive_node* node), size_t* len) {
    intrusive_node* head = &list->head;
    intrusive_node* node = head->next;
    for(; node != head; node = node->next){
        op(node);
        (*len)++;
    }
}

size_t print(intrusive_list* list) {
    size_t len = 0;
    apply(list, print_position, &len);
    return len;
}


size_t count(intrusive_list* list) {
    size_t len = 0;
    apply(list, next_position, &len);
    printf("%lu\n", len);
    return len;    
}

void savebin(FILE* fout, size_t size, int x, int y) {
    fwrite(&x, sizeof(char), size, fout);
    fwrite(&y, sizeof(char), size, fout);
}

void savetext(FILE* fout, size_t size, int x, int y) {
   fprintf(fout, "%d %d\n", x, y);
}

int read_bin(int* x, int* y, size_t size, FILE* fin) {
    int cnt = 0;
    cnt += fread(x, sizeof(char), size, fin);
    cnt += fread(y, sizeof(char), size, fin);
    return cnt;
}

int read_text(int* x, int* y, size_t size, FILE* fin) {
    int cnt = 0;
    cnt += fscanf(fin, "%d %d", x, y);
    return cnt;
}

int main(int argc, char* argv[]) {
    Context ctx;
    ctx.action = NULL;

    FILE* fin;
    if(strcmp(argv[1], "loadtext") == 0) {
        ctx.read = read_text;
        ctx.size = sizeof(int);
        fin = fopen(argv[2], "r");
    } else {
        ctx.read = read_bin;
        ctx.size = 3;
        fin = fopen(argv[2], "rb");
    }

    intrusive_list* list = malloc(sizeof(intrusive_list));
    init_list(list);

    int x = 0, y = 0;
    while(!feof(fin)) {
        ctx.read(&x, &y, ctx.size, fin);
        add_position(list, x, y);
    }

    int to_save = 0;
    size_t size_out = 0;

    if(strcmp(argv[3], "print") == 0) {
        fmt = argv[4];
        ctx.action = print;
    }
    else if(strcmp(argv[3], "count") == 0) {
        ctx.action = count;
    }
    else if(strcmp(argv[3], "savetext") == 0) {
        ctx.save = savetext;
        to_save = 1;
        size_out = sizeof(int);
    }
    else if(strcmp(argv[3], "savebin") == 0) {
        ctx.save = savebin;
        to_save = 2;
        size_out = 3;
    }

    if(to_save) {
        FILE* fout = fopen(argv[4], (to_save == 1 ? "w" : "wb"));
        intrusive_node* head = &list->head;
        intrusive_node* node = head->next;
        for(; node != head; node = node->next){
            position_node* pos = get_position(node);
            ctx.save(fout, size_out, pos->x, pos->y);
        }
        fclose(fout);
    } else {
        size_t cnt = ctx.action(list);
        assert(cnt == get_length(list));
    }
    remove_all(list);
    free(list);
    fclose(fin);
}