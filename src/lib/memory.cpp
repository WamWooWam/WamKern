#include "lib/memory.h"

#include "kernel/kernel.hpp"

const void* Memory::baseAddress = nullptr;
void* Memory::currentPtr = nullptr;
ptrdiff_t Memory::maxSize = 0;

void Memory::Init(const void* baseAddress, ptrdiff_t maxSize) {
    Memory::baseAddress = baseAddress;
    Memory::maxSize = maxSize;

    Memory::currentPtr = (void*)baseAddress;
}

void* Memory::Increment(size_t inc) {
    if (currentPtr == nullptr) {
        WamKern::Kernel::Panic("Memory not initialised!!");
    }

    if (((ptrdiff_t)currentPtr + inc) - (ptrdiff_t)baseAddress > maxSize) {
        WamKern::Kernel::Panic("Requested more memory than available!");
    }

    void* ptr = currentPtr;
    currentPtr = (void*)((uint8_t*)currentPtr + inc);
    return ptr;
}

const void* Memory::GetBaseAddress() noexcept {
    return Memory::baseAddress;
}

template <typename T>
T* Memory::Allocate(size_t count) {
#ifdef TEST
    return (T*)dlmalloc(count * sizeof(T));
#else
    return (T*)malloc(count * sizeof(T));
#endif
}

void Memory::Free(void* ptr) {
#ifdef TEST
    return dlfree(ptr);
#else
    return free(ptr);
#endif
}

void* operator new(size_t count) {
    return (void*)Memory::Allocate<uint8_t>(count);
}

void* operator new[](size_t count) {
    return (void*)Memory::Allocate<uint8_t>(count);
}

void operator delete(void* ptr) {
    Memory::Free(ptr);
}

void operator delete[](void* ptr) {
    Memory::Free(ptr);
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
    return Memory::Increment(inc);
}
}