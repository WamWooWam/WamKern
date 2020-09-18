#ifdef TEST
#include "platform/testplatform.hpp"

#include <stdio.h>
#include <stdlib.h>

namespace WamKern::Platform {
TestPlatform::TestPlatform(void* clientInterfacePtr) {
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