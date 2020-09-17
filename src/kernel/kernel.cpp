#include "kernel/kernel.hpp"

#include "platform/openfirmware.hpp"

using namespace WamKern::Platform;

namespace WamKern {
char Kernel::StackBase[0x8000];
Platform::BasePlatform* Kernel::_platform;

[[noreturn]] void Kernel::Run(void* data) {
    _platform = new OpenFirmwarePlatform(data);
    _platform->WriteToConsole("Hello, world!\r\n");
    _platform->Exit();
}

[[noreturn]] void Kernel::Panic(const char* msg) {
    if (_platform != nullptr) {
        _platform->Panic(msg);
    }

    for (;;)
        ; // halt
}

}  // namespace WamKern