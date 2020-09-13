#pragma once

namespace WamKern::Platform {
class BasePlatform {
   public:
    BasePlatform() = default;
    BasePlatform(const BasePlatform&) = delete;

    virtual void WriteToConsole(const char* text, long length) = 0;

    [[noreturn]] virtual void Exit() = 0;
};
}  // namespace WamKern::Platform