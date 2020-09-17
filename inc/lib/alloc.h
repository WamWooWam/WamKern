#pragma once
#include <dlmalloc/malloc.h>

#ifdef __cplusplus

static unsigned long* currentPtr = nullptr;

void* operator new(size_t count);
void* operator new[](size_t count);
void InitAlloc();

extern "C" {
#endif

void* memset(void* m, int c, size_t count);
void* memcpy(void* d, const void* s, size_t count);
void* memmove(void* d, const void* s, size_t n);
void* sbrk(size_t inc);

#ifdef __cplusplus
}
#endif