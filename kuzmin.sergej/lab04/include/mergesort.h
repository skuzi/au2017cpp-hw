#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int mergesort (void* base, size_t num, size_t size, int (*compar)(void*, void*));