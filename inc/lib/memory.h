#pragma once
#include <dlmalloc/malloc.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus

class Memory {
   public:
    static void Init(const void* baseAddress, ptrdiff_t maxSize);
    static void* Increment(size_t count);
    static const void* GetBaseAddress() noexcept;

    template <typename T>
    static T* Allocate(size_t count);
    static void Free(void* ptr);

   private:
    static const void* baseAddress;
    static void* currentPtr;
    static ptrdiff_t maxSize;
};

void* operator new(size_t count);
void* operator new[](size_t count);
void operator delete(void* ptr);
void operator delete[](void* ptr);

extern "C" {
#endif

#define alloca(x) __builtin_alloca(x)

void* memset(void* m, int32_t c, size_t count);
void* memcpy(void* d, const void* s, size_t count);
void* memmove(void* d, const void* s, size_t n);
void* sbrk(size_t inc);

#ifdef __cplusplus
}
#endif