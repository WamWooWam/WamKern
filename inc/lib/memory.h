#pragma once
#include <dlmalloc/malloc.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#include "kernel/kernellog.hpp"

namespace WamKern {

class Memory {
   public:
    Memory() = delete;
    Memory(Memory&) = delete;
    Memory(Memory&&) = delete;

    static void Init(const void* baseAddress, ptrdiff_t maxSize);
    static void* Increment(size_t count);

    static inline const void* BaseAddress() noexcept {
        return baseAddress;
    }
    static inline const void* TopAddress() noexcept {
        return maxAddress;
    }

    template <typename T>
    static inline T* Allocate(size_t count, bool clear = true) {
        //KernelLogF("Allocating %d bytes", count * sizeof(T));

#ifdef TEST
        return clear ? (T*)dlcalloc(count, sizeof(T)) : (T*)dlmalloc(count * sizeof(T));
#else
        return clear ? (T*)calloc(count, sizeof(T)) : (T*)malloc(count * sizeof(T));
#endif
    }

    template <typename T>
    static inline T* Set(T* dest, T c, size_t count) {
        for (size_t i = 0; i < count; i++) {
            ((T*)dest)[i] = c;
        }

        return dest;
    }

    template <typename T>
    static inline T* Copy(const T* src, T* dest, size_t count) {
        for (size_t i = 0; i < count; i++) {
            dest[i] = src[i];
        }

        return dest;
    }

    template <typename T>
    static inline T* Move(const T* src, T* dest, size_t count) {
        for (size_t i = 0; i < count; i++) {
            size_t j = dest < src ? i : count - 1 - i;
            dest[j] = src[j];
        }
        return dest;
    }

    static void Free(void* ptr) {
        //KernelLogF("Freeing ptr 0x%x", ptr);

#ifdef TEST
        return dlfree(ptr);
#else
        return free(ptr);
#endif
    }

   private:
    static const void* baseAddress;
    static const void* maxAddress;
    static void* currentPtr;
};

}  // namespace WamKern

void* operator new(size_t count);
void* operator new[](size_t count);
void operator delete(void* ptr);
void operator delete[](void* ptr);

extern "C" {
#endif

#ifndef alloca
#define alloca(x) __builtin_alloca(x)
#endif

void* memset(void* m, int32_t c, size_t count);
void* memcpy(void* d, const void* s, size_t count);
void* memmove(void* d, const void* s, size_t n);
void* memchr(void* ptr, int value, size_t count);
void* sbrk(size_t inc);


#ifdef __cplusplus
}
#endif