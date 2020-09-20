#ifdef TEST
#include "platform/testplatform.hpp"

#include <stdio.h>
#include <stdlib.h>

#include "lib/memory.h"

namespace WamKern::Platform {
uint8_t* TestPlatform::testHeap = nullptr;

TestPlatform::TestPlatform(void* data) {
}

void TestPlatform::InitMemory() {
    testHeap = (uint8_t*)malloc(32 * 1024 * 1024);
    Memory::Init(testHeap, 32 * 1024 * 1024);
}

void TestPlatform::WriteToConsole(const char* text) {
    printf("%s", text);
}

void TestPlatform::WriteToConsole(const char* text, size_t length) {
    printf("%s", text);
}

[[noreturn]] void TestPlatform::Halt() {
    abort();
}

[[noreturn]] void TestPlatform::Exit() {
    exit(0);
}
}  // namespace WamKern::Platform

#endif