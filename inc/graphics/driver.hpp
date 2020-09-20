#pragma once
#include <utility>

#include "graphics/display.hpp"
#include "lib/memory.h"

namespace WamKern::Graphics {
class GraphicsDriver {
   public:
    static constexpr size_t MaxDisplays = 8;

    virtual bool Initialise() = 0;
    virtual size_t GetDisplays(Display** displays, size_t size) = 0;
    virtual Display* GetDisplay(size_t index) = 0;

    virtual size_t DisplayCount() = 0;
};
}  // namespace WamKern::Graphics