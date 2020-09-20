#include "graphics/display.hpp"

#include "kernel/kernel.hpp"
#include "lib/memory.h"

namespace WamKern::Graphics {
void Display::Clear(uint8_t col) {
    //KernelLog("Clear");
    memset((void*)this->_backBuffer, col, this->_bufferSize);
}

void Display::FillRect(size_t x, size_t y, size_t width, size_t height, uint8_t col) {
    uint8_t* buff = (uint8_t*)this->BackBuffer();
    // long xMax = width + x;
    // long yMax = height + y;
    // if (xMax > this->Width())
    //     width = width + (xMax - (long)this->Width());
    // if (yMax > this->Height())
    //     height = height + (yMax - (long)this->Height());

    // KernelLogF("x:%d y:%d w:%d h:%d", width, height, x, y);

    for (size_t i = 0; i < height; i++) {
        uint8_t* buff2 = buff + ((y + i) * this->Stride());
        for (size_t j = 0; j < width; j++) {
            buff2[x + j] = col;
        }
    }
}

void Display::Present() {
    //KernelLogF("Present src: 0x%x dest: 0x%x", this->_backBuffer, this->_frontBuffer);
    memcpy((void*)this->_frontBuffer, (void*)this->_backBuffer, this->_bufferSize);
}
}  // namespace WamKern::Graphics