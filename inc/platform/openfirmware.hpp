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
    Cell _chosenEH = 0;
    Cell _stdoutIH = 0;

    void InitConsole();
};
}  // namespace WamKern::Platform