#pragma once
#include <stdint.h>
#include <dlmalloc/malloc.h>

#ifdef __cplusplus

static unsigned long* currentPtr = nullptr;

void* operator new(size_t count);
void* operator new[](size_t count);
void operator delete(void* ptr);
void operator delete[](void* ptr); 

extern "C" {
#endif

void* memset(void* m, int32_t c, size_t count);
void* memcpy(void* d, const void* s, size_t count);
void* memmove(void* d, const void* s, size_t n);
void* sbrk(size_t inc);

#ifdef __cplusplus
}
#endif