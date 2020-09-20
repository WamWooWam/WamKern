#include "platform/platform.hpp"
#include "lib/string.h"

namespace WamKern::Platform {
[[noreturn]] void Platform::Panic(const char* msg) {
    WriteToConsole("\033[34;5mFATAL ERROR: \033[0m");
    WriteToConsole(msg);
    WriteToConsole("\r\nSYSTEM HALTED.");

    Halt();
}

void Platform::WriteToConsole(const char* msg) {
    WriteToConsole(msg, String::Length(msg));
}
}