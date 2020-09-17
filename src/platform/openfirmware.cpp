#include "platform/openfirmware.hpp"

#include "lib/string.h"

namespace WamKern::Platform {
OpenFirmwarePlatform::OpenFirmwarePlatform(void* clientInterfacePtr) {
    _clientInterface = ClientInterface(clientInterfacePtr);

    // aquire the /chosen device
    _chosenPH = _clientInterface.FindDevice("/chosen");

    // get stdout/stdin from it
    _clientInterface.GetProp(_chosenPH, "stdout", (char*)&_stdoutIH, sizeof _stdoutIH);
    _clientInterface.GetProp(_chosenPH, "stdin", (char*)&_stdinIH, sizeof _stdinIH);

    _clientInterface.GetProp(_chosenPH, "memory", (char*)&_memIH, sizeof _memIH);
    if (!ClientInterface::IsValidHandle(_memIH))
        Panic("Unable to aquire memory instance handle!");

    _clientInterface.GetProp(_chosenPH, "mmu", (char*)&_mmuIH, sizeof _mmuIH);
    if (!ClientInterface::IsValidHandle(_mmuIH))
        Panic("Unable to aquire mmu instance handle!");
}

void OpenFirmwarePlatform::WriteToConsole(const char* text) {
    if (ClientInterface::IsValidHandle(_stdoutIH))
        _clientInterface.Write(_stdoutIH, (void*)text, String::Length(text));
}

[[noreturn]] void OpenFirmwarePlatform::Halt() {
    __builtin_trap();
}

[[noreturn]] void OpenFirmwarePlatform::Exit() {
    _clientInterface.Exit();
}
}  // namespace WamKern::Platform
