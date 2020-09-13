#include "kernel/kernel.hpp"

#include "platform/openfirmware.hpp"

using namespace WamKern::Platform;

namespace WamKern {
char Kernel::StackBase[0x8000];

[[noreturn]] void Kernel::InitKernel(void* data) {
    static const char message[15] = "Hello, world!\n";
    OpenFirmwarePlatform platform{data};
    
}
}  // namespace WamKern