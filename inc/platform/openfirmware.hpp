#pragma once
#include "firmware/openfirmware/clientinterface.hpp"
#include "platform/baseplatform.hpp"

using namespace WamKern::Firmware::OpenFirmware;

namespace WamKern::Platform {
class OpenFirmwarePlatform : public BasePlatform {
   public:
    OpenFirmwarePlatform(void* clientInterfacePtr);
    OpenFirmwarePlatform(const OpenFirmwarePlatform&) = delete;

    void WriteToConsole(const char* text);
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
};
}  // namespace WamKern::Platform