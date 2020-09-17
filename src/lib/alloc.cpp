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

void operator delete(void* ptr) {
    return free(ptr);
}

void operator delete[](void* ptr) {
    return free(ptr);
}

extern "C" {
void* memset(void* mem, int32_t c, size_t count) {
    for (size_t i = 0; i < count; i++) {
        ((uint8_t*)mem)[i] = (uint8_t)c;
    }

    return mem;
}

void* memcpy(void* dest, const void* src, size_t count) {
    for (size_t i = 0; i < count; i++) {
        ((uint8_t*)dest)[i] = ((const uint8_t*)src)[i];
    }

    return dest;
}

void* memmove(void* dest, const void* src, size_t count) {
    for (size_t i = 0; i < count; i++) {
        size_t j = dest < src ? i : count - 1 - i;
        ((uint8_t*)dest)[j] = ((const uint8_t*)src)[j];
    }
    return dest;
}

void* sbrk(size_t inc) {
    return (void*)(currentPtr + inc);
}
}