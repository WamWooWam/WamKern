#pragma once
#include <stdint.h>

#include "platform/platform.hpp"

namespace WamKern::Platform::Test {
class TestPlatform : public Platform {
   public:
    TestPlatform(void*);
    TestPlatform(const TestPlatform&) = delete;
    TestPlatform(const TestPlatform&&) {
    }

    void InitMemory();
    Graphics::Driver* CreateGraphicsDriver() {
        return nullptr;
    }

    void WriteToConsole(const char* text);
    void WriteToConsole(const char* text, size_t length);
    [[noreturn]] void Halt();
    [[noreturn]] void Exit();

   private:
    static uint8_t* testHeap;
};
}  // namespace WamKern::Platform