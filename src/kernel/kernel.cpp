#include "kernel/kernel.hpp"

#include <stdint.h>

#include "lib/endian.h"
#include "lib/memory.h"
#include "lib/std.h"
#include "lib/string.h"
#include "platform/platformfactory.hpp"

using namespace WamKern::Platform;

namespace WamKern {
char Kernel::StackBase[0x8000];
Platform::Platform* Kernel::_platform;

[[noreturn]] void Kernel::Run(void* data) {
    _platform = PlatformFactory::CreateDefaultPlatform(data);

    KernelLogF("WamKern 1.0.0 compiled with clang %son %s at %s", __clang_version__, __DATE__, __TIME__);
    KernelLogF("Memory allocation at 0x%x-0x%x (0x%x bytes), stack at 0x%x",
               Memory::BaseAddress(),
               Memory::TopAddress(),
               (uintptr_t)Memory::TopAddress() - (uintptr_t)Memory::BaseAddress(),
               &StackBase);

    uint8_t* allocTest = Memory::Allocate<uint8_t>(1 * 1024 * 1024);
    if (allocTest == nullptr)
        Panic("Failed to allocate memory!!");

    KernelLogF("Allocated 1M at 0x%x", Endian::Swap((uintptr_t)allocTest));
    KernelLogF("0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x", allocTest[0], allocTest[1], allocTest[2], allocTest[3], allocTest[4], allocTest[5], allocTest[6], allocTest[7]);
    Memory::Free(allocTest);
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