#include "kernel/kernel.hpp"

#include <stdint.h>

#include "lib/alloc.h"
#include "platform/openfirmware.hpp"

using namespace WamKern::Platform;

namespace WamKern {
char Kernel::StackBase[0x8000];
Platform::BasePlatform* Kernel::_platform;

[[noreturn]] void Kernel::Run(void* data) {
    const char testString[16] = "Hello, world!\r\n";

    _platform = new OpenFirmwarePlatform{data};
    _platform->WriteToConsole(testString);
    _platform->Exit();
}

[[noreturn]] void Kernel::Panic(const char* msg) {
    if (_platform != nullptr) {
        _platform->Panic(msg);
    }

    for (;;)
        ;  // halt
}

}  // namespace WamKern