#ifdef TEST
#include "platform/testplatform.hpp"
#include "lib/memory.h"

#include <stdio.h>
#include <stdlib.h>

namespace WamKern::Platform {
uint8_t* TestPlatform::testHeap = nullptr;

TestPlatform::TestPlatform(void* clientInterfacePtr) {
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