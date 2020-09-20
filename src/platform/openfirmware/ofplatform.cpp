#ifdef POWERPC
#include "lib/memory.h"
#include "lib/string.h"
#include "platform/openfirmware/ofgraphics.hpp"
#include "platform/openfirmware/ofplatform.hpp"

using namespace WamKern::Graphics;

namespace WamKern::Platform::OpenFirmware {
OFPlatform::OFPlatform(void* clientInterfacePtr) {
    _clientInterface = ClientInterface(clientInterfacePtr);

    // aquire the /chosen device
    _chosenPH = _clientInterface.FindDevice("/chosen");

    // get stdout/stdin from it
    _clientInterface.GetProp(_chosenPH, "stdout", (char*)&_stdoutIH, sizeof _stdoutIH);
    _stdoutPH = _clientInterface.InstanceToPackage(_stdoutIH);

    _clientInterface.GetProp(_chosenPH, "stdin", (char*)&_stdinIH, sizeof _stdinIH);

    _clientInterface.GetProp(_chosenPH, "memory", (char*)&_memIH, sizeof _memIH);
    if (!ClientInterface::IsValidHandle(_memIH))
        Panic("Unable to aquire memory instance handle!");

    _clientInterface.GetProp(_chosenPH, "mmu", (char*)&_mmuIH, sizeof _mmuIH);
    if (!ClientInterface::IsValidHandle(_mmuIH))
        Panic("Unable to aquire mmu instance handle!");
}

OFPlatform::OFPlatform(const OFPlatform&& p) {
    _clientInterface = p._clientInterface;
    _chosenPH = p._chosenPH;
    _stdoutIH = p._stdoutIH;
    _stdoutPH = p._stdoutPH;
    _stdinIH = p._stdinIH;
    _memIH = p._memIH;
    _mmuIH = p._mmuIH;
}

void OFPlatform::InitMemory() {
    _clientInterface.Claim((Cell)_mallocAddress, _mallocSize, 0);
    Memory::Init(_mallocAddress, _mallocSize);
}

GraphicsDriver* OFPlatform::CreateGraphicsDriver() {
    return new OFGraphicsDriver(_clientInterface, _stdoutIH, _stdoutPH);
}

void OFPlatform::WriteToConsole(const char* text, size_t length) {
    if (ClientInterface::IsValidHandle(_stdoutIH))
        _clientInterface.Write(_stdoutIH, (void*)text, length);
}

[[noreturn]] void OFPlatform::Halt() {
    __builtin_trap();
}

[[noreturn]] void OFPlatform::Exit() {
    _clientInterface.Exit();
}
}  // namespace WamKern::Platform::OpenFirmware
#endif