#pragma once
#include <stddef.h>

#include "graphics/driver.hpp"

namespace WamKern::Platform {
class Platform {
   public:
    Platform() = default;
    Platform(const Platform&) = delete;

    virtual void InitMemory() = 0;
    virtual Graphics::GraphicsDriver* CreateGraphicsDriver() = 0;

    virtual void WriteToConsole(const char* text);
    virtual void WriteToConsole(const char* text, size_t length) = 0;

    [[noreturn]] virtual void Panic(const char* msg);
    [[noreturn]] virtual void Halt() = 0;
    [[noreturn]] virtual void Exit() = 0;
};
}  // namespace WamKern::Platform