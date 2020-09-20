#include "lib/memory.h"

#include "kernel/kernel.hpp"

namespace WamKern {
const void* Memory::baseAddress = nullptr;
const void* Memory::maxAddress = 0;
void* Memory::currentPtr = nullptr;

void Memory::Init(const void* baseAddress, ptrdiff_t maxSize) {
    Memory::baseAddress = baseAddress;
    Memory::maxAddress = (const void*)((char*)baseAddress + maxSize);
    Memory::currentPtr = (void*)baseAddress;
}

void* Memory::Increment(size_t inc) {
    char* orig = (char*)currentPtr;
    void* ptr = orig + inc;

    if (currentPtr == nullptr) {
        Kernel::Panic("Memory not initialised!!");
    }

    if (ptr > maxAddress) {
        Kernel::Panic("Requested more memory than available!");
    }

    currentPtr = ptr;
    return orig;
}
}  // namespace WamKern

void* operator new(size_t count) {
    return (void*)WamKern::Memory::Allocate<uint8_t>(count);
}

void* operator new[](size_t count) {
    return (void*)WamKern::Memory::Allocate<uint8_t>(count);
}

void operator delete(void* ptr) {
    WamKern::Memory::Free(ptr);
}

void operator delete[](void* ptr) {
    WamKern::Memory::Free(ptr);
}

extern "C" {
void* memset(void* mem, int32_t c, size_t count) {
    return WamKern::Memory::Set((uint8_t*)mem, (uint8_t)c, count);
}

void* memcpy(void* dest, const void* src, size_t count) {
    return WamKern::Memory::Copy((const uint8_t*)src, (uint8_t*)dest, count);
}

void* memmove(void* dest, const void* src, size_t count) {
    return WamKern::Memory::Move((const uint8_t*)src, (uint8_t*)dest, count);
}

void* memchr(void* ptr, int value, size_t count) {
    uint8_t* p = (uint8_t*)ptr;
    uint8_t i = (uint8_t)i;

    for (size_t x = 0; x < count; x++) {
        if (p[x] == i) return p + x;
    }

    return 0;
}

void* sbrk(size_t inc) {
    return WamKern::Memory::Increment(inc);
}
}