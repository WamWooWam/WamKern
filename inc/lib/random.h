#pragma once
#include <stdint.h>

// influenced by https://github.com/morinim/xoshiro256ss/

namespace WamKern {
class Random {
   public:
    static uint64_t Next() {
        const uint64_t result_starstar(RotLeft(state[1] * 5, 7) * 9);
        const uint64_t t(state[1] << 17);

        state[2] ^= state[0];
        state[3] ^= state[1];
        state[1] ^= state[2];
        state[0] ^= state[3];

        state[2] ^= t;

        state[3] = RotLeft(state[3], 45);

        return result_starstar;
    }

    template<typename T>
    static T Range(T min, T max) {
        return ((T)Next() % max) + min;
    }

    static inline uint64_t RotLeft(uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

   private:
    static uint64_t seed;
    static uint64_t state[4];
};
}  // namespace WamKern