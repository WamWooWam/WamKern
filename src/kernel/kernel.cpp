#include "kernel/kernel.hpp"

#include <stdint.h>

#include "lib/memory.h"
#include "lib/std.h"
#include "lib/string.h"
#include "platform/openfirmware.hpp"
#include "platform/testplatform.hpp"

using namespace WamKern::Platform;

namespace WamKern {
char Kernel::StackBase[0x8000];
Platform::BasePlatform* Kernel::_platform;

[[noreturn]] void Kernel::Run(void* data) {
#ifdef TEST
    TestPlatform platform{data};
    _platform = new TestPlatform(std::move(platform));
#else
    OpenFirmwarePlatform platform{data};
    _platform = new OpenFirmwarePlatform(std::move(platform));
#endif
    KernelLogF("WamKern 1.0.0 compiled with clang %son %s at %s", __clang_version__, __DATE__, __TIME__);
    KernelLogF("Memory allocation starting at 0x%x, stack at 0x%x", Memory::GetBaseAddress(), &StackBase);

    uint8_t* allocTest = Memory::Allocate<uint8_t>(1024 * 1024, true);
    if (allocTest == nullptr)
        Panic("Failed to allocate memory!!");

    KernelLogF("Allocated 1M at 0x%x", allocTest);
    KernelLogF("0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x", allocTest[0], allocTest[1], allocTest[2], allocTest[3], allocTest[4], allocTest[5], allocTest[6], allocTest[7]);
    
    delete[] allocTest;
    KernelLog("Exiting to host.");

    _platform->Exit();
}

[[noreturn]] void Kernel::Panic(const char* msg) {
    if (_platform != nullptr) {
        _platform->Panic(msg);
    }

    for (;;)
        ;  // halt
}

void Kernel::Log(const char* file, const char* func, int lineNum, const char* messageFormat, ...) {
    if (_platform == nullptr)
        return;

    char message[1024];
    char logString[1280];
    size_t messageLength, logStringLength = 0;
    va_list arg;

    va_start(arg, messageFormat);
    messageLength = vsnprintf(message, 1024, messageFormat, arg);
    va_end(arg);

    logStringLength = snprintf(logString, 1280, "\033[31m[%s:%i]::%s:\033[0m %s\r\n", file, lineNum, func, message);
    _platform->WriteToConsole((const char*)logString, logStringLength);
}

}  // namespace WamKern