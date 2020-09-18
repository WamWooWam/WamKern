#pragma once
#include <stddef.h>

namespace WamKern::Platform {
class BasePlatform {
   public:
    BasePlatform() = default;
    BasePlatform(const BasePlatform&) = delete;

    virtual void WriteToConsole(const char* text) = 0;
    virtual void WriteToConsole(const char* text, size_t length) = 0;

    [[noreturn]] virtual void Panic(const char* msg);
    [[noreturn]] virtual void Halt() = 0;
    [[noreturn]] virtual void Exit() = 0;
};
}  // namespace WamKern::Platform