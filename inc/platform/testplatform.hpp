#ifdef TEST
#pragma once
#include "platform/baseplatform.hpp"

namespace WamKern::Platform {
class TestPlatform : public BasePlatform {
   public:
    TestPlatform(void*);
    TestPlatform(const TestPlatform&) = delete;

    void WriteToConsole(const char* text);
    void WriteToConsole(const char* text, size_t length);
    [[noreturn]] void Halt();
    [[noreturn]] void Exit();
};
}  // namespace WamKern::Platform
#endif