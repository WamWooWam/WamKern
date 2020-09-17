#include "lib/alloc.h"

extern unsigned long end;

void InitAlloc() {
    currentPtr = &end;
}

void* operator new(size_t count) {
    return malloc(count);
}

void* operator new[](size_t count) {
    return malloc(count);
}

extern "C" {
void* memset(void* mem, int c, size_t count) {
    for (size_t i = 0; i < count; i++) {
        ((unsigned char*)mem)[i] = (unsigned char)c;
    }

    return mem;
}

void* memcpy(void* dest, const void* src, size_t count) {
    for (size_t i = 0; i < count; i++) {
        ((char*)dest)[i] = ((const char*)src)[i];
    }

    return dest;
}

void* memmove(void* dest, const void* src, size_t count) {
    for (size_t i = 0; i < count; i++) {
        size_t j = dest < src ? i : count - 1 - i;
        ((char*)dest)[j] = ((const char*)src)[j];
    }
    return dest;
}

void* sbrk(size_t inc) {
    return (void*)(currentPtr + inc);
}
}