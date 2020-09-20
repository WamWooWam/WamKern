#include "platform/platform.hpp"

namespace WamKern::Platform {
[[noreturn]] void Platform::Panic(const char* msg) {
    WriteToConsole("\033[34;5mFATAL ERROR: \033[0m");
    WriteToConsole(msg);
    WriteToConsole("\r\nSYSTEM HALTED.");

    Halt();
}
}