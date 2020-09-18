#include "lib/memory.h"

#include "kernel/kernel.hpp"

namespace WamKern {
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
        Kernel::Panic("Memory not initialised!!");
    }

    if (((ptrdiff_t)currentPtr + inc) - (ptrdiff_t)baseAddress > maxSize) {
        Kernel::Panic("Requested more memory than available!");
    }

    void* ptr = currentPtr;
    currentPtr = (void*)((uint8_t*)currentPtr + inc);
    return ptr;
}

const void* Memory::GetBaseAddress() noexcept {
    return Memory::baseAddress;
}

template <typename T>
T* Memory::Allocate(size_t count, bool clear) {
    KernelLogF("Allocating %d bytes", count * sizeof(T));

#ifdef TEST
    return clear ? (T*)dlcalloc(count, sizeof(T)) : (T*)dlmalloc(count * sizeof(T));
#else
    return clear ? (T*)calloc(count, sizeof(T)) : (T*)malloc(count * sizeof(T));
#endif
}

void Memory::Free(void* ptr) {
    KernelLogF("Freeing ptr 0x%x", ptr);

#ifdef TEST
    return dlfree(ptr);
#else
    return free(ptr);
#endif
}

template <typename T>
T* Memory::Set(T* dest, T c, size_t count) {
    for (size_t i = 0; i < count; i++) {
        ((T*)dest)[i] = c;
    }

    return dest;
}
template <typename T>
T* Memory::Copy(const T* src, T* dest, size_t count) {
    for (size_t i = 0; i < count; i++) {
        dest[i] = src[i];
    }

    return dest;
}

template <typename T>
T* Memory::Move(const T* src, T* dest, size_t count) {
    for (size_t i = 0; i < count; i++) {
        size_t j = dest < src ? i : count - 1 - i;
        dest[j] = src[j];
    }
    return dest;
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

void* sbrk(size_t inc) {
    return WamKern::Memory::Increment(inc);
}
}