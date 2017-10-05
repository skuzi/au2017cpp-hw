#include "mergesort.h"

static void* mem_cpy(void* dst, void* src, size_t cnt) {
	char* to = (char*) dst;
	char* from = (char*) src;
	for(int i = 0; i < cnt; i++)
		*(to + i) = *(from + i);
	return dst;
}

static void* merge(void* a, size_t sz_a, void* b, size_t sz_b, size_t size, int (*compar)(void*, void*)) {
	void* c = malloc((sz_a + sz_b) * size);
	void* last_a = a + sz_a * size;
	void* last_b = b + sz_b * size;
	void* aa = a;
	void* bb = b;
	void* cc = c;
	while(aa != last_a || bb != last_b){
		if(aa == last_a)
			mem_cpy(cc, bb, size), bb += size;
		else if(bb == last_b)
			mem_cpy(cc, aa, size), aa += size;
		else if(compar(aa, bb) < 0)
			mem_cpy(cc, aa, size), aa += size;
		else
			mem_cpy(cc, bb, size), bb += size;
		cc += size;
	}
	return c;
}

int mergesort (void* base, size_t num, size_t size, int (*compar)(void*, void*)) {
	if(num == 1)
		return 0;
	int m = num / 2;
	mergesort(base, m, size, compar);
	mergesort(base + m * size, m + (num & 1), size, compar);
	void* c = merge(base, m, base + m * size, m + (num & 1), size, compar);
	mem_cpy(base, c, num * size);
	free(c);
	return 0;
}
