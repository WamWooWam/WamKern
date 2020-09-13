#include "platform/openfirmware.hpp"

namespace WamKern::Platform {
OpenFirmwarePlatform::OpenFirmwarePlatform(void* clientInterfacePtr) {
    _clientInterface = ClientInterface(clientInterfacePtr);
    _chosenEH = _clientInterface.FindDevice("/chosen");
}

void OpenFirmwarePlatform::WriteToConsole(const char* text, long length) {
    InitConsole();

    _clientInterface.Write(_stdoutIH, (void*)text, length);
}

void OpenFirmwarePlatform::InitConsole() {
    if (_stdoutIH == 0) {
        _clientInterface.GetProp(_chosenEH, "stdout", (char*)&_stdoutIH, sizeof _stdoutIH);
    }
}

[[noreturn]] void OpenFirmwarePlatform::Exit() {
    _clientInterface.Exit();
}
}  // namespace WamKern::Platform
