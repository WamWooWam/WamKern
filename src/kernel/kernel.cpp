#include "kernel/kernel.hpp"

#include <stdint.h>

#include "graphics/display.hpp"
#include "graphics/driver.hpp"
#include "lib/endian.h"
#include "lib/memory.h"
#include "lib/string.h"
#include "platform/platformfactory.hpp"

using namespace WamKern::Platform;

namespace WamKern {
char Kernel::StackBase[0x8000];
Platform::Platform* Kernel::_platform = nullptr;

[[noreturn]] void Kernel::Run(void* data) {
    _platform = PlatformFactory::CreateDefaultPlatform(data);

    KernelLogF("WamKern 1.0.0 compiled with clang %son %s at %s", __clang_version__, __DATE__, __TIME__);
    KernelLogF("Memory allocation at 0x%x-0x%x (0x%x bytes), stack at 0x%x",
               Memory::BaseAddress(),
               Memory::TopAddress(),
               (uintptr_t)Memory::TopAddress() - (uintptr_t)Memory::BaseAddress(),
               &StackBase);

    auto graphicsDriver = _platform->CreateGraphicsDriver();
    if (graphicsDriver->Initialise()) {
        //auto displays = Memory::Allocate<Graphics::Display>(Graphics::GraphicsDriver::MaxDisplays);
        auto displayCount = graphicsDriver->DisplayCount();

        KernelLogF("Got %d displays", displayCount);
    }

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