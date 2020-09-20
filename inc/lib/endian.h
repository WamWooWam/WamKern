#pragma once
#include <byteswap.h>
#include <stdint.h>

#ifdef POWERPC
#undef bswap_16
#undef bswap_32

#ifdef __cplusplus
extern "C" {
#endif
// define optimised byteswap functions for PowerPC (GCC doesn't)
static inline uint16_t bswap_16(uint16_t x) {
    uint16_t temp;
    __asm__("sthbrx %0, 0, %1"
            :
            : "r"(x), "r"(&temp));
    return temp;
}

static inline uint32_t bswap_32(uint32_t x) {
    uint32_t temp;
    __asm__("stwbrx %0, 0, %1"
            :
            : "r"(x), "r"(&temp));
    return temp;
}
#ifdef __cplusplus
}
#endif
#endif

class Endian {
   public:
    static inline uint16_t BigToHost(uint16_t x) {
#if BIG_ENDIAN
        return x;
#else
        return bswap_16(x);
#endif
    }

    static inline uint32_t BigToHost(uint32_t x) {
#if BIG_ENDIAN
        return x;
#else
        return bswap_32(x);
#endif
    }

    static inline uint64_t BigToHost(uint64_t x) {
#if BIG_ENDIAN
        return x;
#else
        return bswap_64(x);
#endif
    }

    static inline uint16_t LittleToHost(uint16_t x) {
#if BIG_ENDIAN
        return bswap_16(x);
#else
        return x;
#endif
    }

    static inline uint32_t LittleToHost(uint32_t x) {
#if BIG_ENDIAN
        return bswap_32(x);
#else
        return x;
#endif
    }

    static inline uint64_t LittleToHost(uint64_t x) {
#if BIG_ENDIAN
        return bswap_64(x);
#else
        return x;
#endif
    }

    static inline uint16_t Swap(uint16_t x) {
        return bswap_16(x);
    }

    static inline uint32_t Swap(uint32_t x) {
        return bswap_32(x);
    }

    static inline uint64_t Swap(uint64_t x) {
        return bswap_64(x);
    }
};