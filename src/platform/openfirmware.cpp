#include "platform/openfirmware.hpp"

namespace WamKern::Platform {
OpenFirmwarePlatform::OpenFirmwarePlatform(void* clientInterfacePtr) {
    _clientInterface = ClientInterface(clientInterfacePtr);

    // aquire the /chosen device
    _chosenPH = _clientInterface.FindDevice("/chosen");

    // get stdout/stdin from it
    _clientInterface.GetProp(_chosenPH, "stdout", (char*)&_stdoutIH, sizeof _stdoutIH);
    _clientInterface.GetProp(_chosenPH, "stdin", (char*)&_stdinIH, sizeof _stdinIH);
}

void OpenFirmwarePlatform::WriteToConsole(const char* text, long length) {
    _clientInterface.Write(_stdoutIH, (void*)text, length);
}

[[noreturn]] void OpenFirmwarePlatform::Exit() {
    _clientInterface.Exit();
}
}  // namespace WamKern::Platform
