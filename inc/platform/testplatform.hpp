#ifdef TEST
#pragma once
#include <stdint.h>

#include "platform/baseplatform.hpp"

namespace WamKern::Platform {
class TestPlatform : public BasePlatform {
   public:
    TestPlatform(void*);
    TestPlatform(const TestPlatform&) = delete;
    TestPlatform(const TestPlatform&&) {
    }

    void WriteToConsole(const char* text);
    void WriteToConsole(const char* text, size_t length);
    [[noreturn]] void Halt();
    [[noreturn]] void Exit();

   private:
    static uint8_t* testHeap;
};
}  // namespace WamKern::Platform
#endif