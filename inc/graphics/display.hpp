#pragma once
#include <stddef.h>
#include <stdint.h>

namespace WamKern::Graphics {
class Display {
   public:
    const inline size_t Width() {
        return _width;
    }

    const inline size_t Height() {
        return _height;
    }

    const inline uint8_t BitDepth() {
        return _bitDepth;
    }

    const inline size_t Stride() {
        return _stride;
    }

   protected:
    size_t _width;
    size_t _height;
    size_t _bitDepth;
    size_t _stride;
};
}  // namespace WamKern::Graphics