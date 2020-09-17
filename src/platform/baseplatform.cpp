#include "platform/baseplatform.hpp"

namespace WamKern::Platform {
[[noreturn]] void BasePlatform::Panic(const char* msg) {
    WriteToConsole("\033[34;5mFATAL ERROR: \033[0m");
    WriteToConsole(msg);
    WriteToConsole("\r\nSYSTEM HALTED.");

    Halt();
}
}