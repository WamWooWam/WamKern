#include "kernel/kernel.hpp"

#include <stdint.h>

#include "lib/alloc.h"
#include "lib/string.h"
#include "platform/openfirmware.hpp"
#include "platform/testplatform.hpp"

using namespace WamKern::Platform;

namespace WamKern {
char Kernel::StackBase[0x8000];
Platform::BasePlatform* Kernel::_platform;

[[noreturn]] void Kernel::Run(void* data) {
#ifdef TEST
    _platform = new TestPlatform{data};
#else
    _platform = new OpenFirmwarePlatform{data};
#endif
    KernelLog("WamKern 1.0.0 compiled with clang %s on %s at %s",  __clang_version__, __DATE__, __TIME__);

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

    char *message, *logString = nullptr;
    size_t messageLength, logStringLength = 0;
    va_list arg;

    va_start(arg, messageFormat);
    messageLength = vasprintf(&message, messageFormat, arg);
    va_end(arg);

    logStringLength = asprintf(&logString, "[%s:%i] %s: ", file, lineNum, func);
    _platform->WriteToConsole((const char*)logString, logStringLength);
    _platform->WriteToConsole((const char*)message, messageLength);
    _platform->WriteToConsole("\r\n");

    free(message);
    free(logString);
}

}  // namespace WamKern