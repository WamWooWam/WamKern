#pragma once
#include <stddef.h>
#include <stdint.h>

#include "lib/memory.h"

namespace WamKern::Graphics {
class Display {
   public:
    Display(size_t width, size_t height, uint8_t bitDepth, size_t stride, uintptr_t frontBuffer) {
        _width = width;
        _height = height;
        _bitDepth = bitDepth;
        _stride = stride;
        _bufferSize = stride * height;
        _frontBuffer = (uintptr_t)frontBuffer;
        _backBuffer = (uintptr_t)malloc(_bufferSize);
    }

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

    const inline void* FrontBuffer() {
        return (void*)_frontBuffer;
    }

    const inline void* BackBuffer() {
        return (void*)_backBuffer;
    }

    void Clear(uint8_t col);
    void FillRect(size_t x, size_t y, size_t width, size_t height, uint8_t col);
    void Present();

   protected:
    size_t _width;
    size_t _height;
    uint8_t _bitDepth;
    size_t _stride;

    size_t _bufferSize;
    uintptr_t _frontBuffer;
    uintptr_t _backBuffer;
};
}  // namespace WamKern::Graphics