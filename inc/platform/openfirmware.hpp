#pragma once
#include "firmware/openfirmware/clientinterface.hpp"
#include "platform/baseplatform.hpp"

using namespace WamKern::Firmware::OpenFirmware;

namespace WamKern::Platform {
class OpenFirmwarePlatform : public BasePlatform {
   public:
    OpenFirmwarePlatform(void* clientInterfacePtr);
    OpenFirmwarePlatform(const OpenFirmwarePlatform&) = delete;

    void WriteToConsole(const char* text, long length);
    [[noreturn]] void Exit();

   private:
    ClientInterface _clientInterface;
    Cell _chosenPH = 0;
    Cell _stdoutIH = 0;
    Cell _stdinIH = 0;
};
}  // namespace WamKern::Platform