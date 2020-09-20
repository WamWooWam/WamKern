#pragma once
#include "firmware/openfirmware/clientinterface.hpp"
#include "platform/platform.hpp"

using namespace WamKern::Firmware::OpenFirmware;

namespace WamKern::Platform {
class OpenFirmwarePlatform : public Platform {
   public:
    OpenFirmwarePlatform(void* clientInterfacePtr);
    OpenFirmwarePlatform(const OpenFirmwarePlatform&) = delete;
    OpenFirmwarePlatform(const OpenFirmwarePlatform&&);

    void InitMemory();
    Graphics::Driver* CreateGraphicsDriver();

    void WriteToConsole(const char* text);
    void WriteToConsole(const char* text, size_t length);
    [[noreturn]] void Halt();
    [[noreturn]] void Exit();

   private:
    ClientInterface _clientInterface;
    Cell _chosenPH = 0;

    // stdout instance handle
    Cell _stdoutIH = 0;
    // stdin instance handle
    Cell _stdinIH = 0;

    // memory map package handle
    Cell _memmapPH = 0;

    // memory instance handle
    Cell _memIH = 0;
    // mmu instance handle
    Cell _mmuIH = 0;

    const void* _mallocAddress = (void*)0x04000000;
    const ptrdiff_t _mallocSize = 32 * 1024 * 1024;
};
}  // namespace WamKern::Platform