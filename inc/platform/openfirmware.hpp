#pragma once
#include "platform/baseplatform.hpp"
#include "firmware/openfirmware/clientinterface.hpp"

namespace WamKern::Platform {
class OpenFirmwarePlatform : public BasePlatform {
   public:
    OpenFirmwarePlatform(void* clientInterfacePtr);
    OpenFirmwarePlatform(const OpenFirmwarePlatform&) = delete;

   private:
    Firmware::OpenFirmware::ClientInterface _clientInterface;
};
}  // namespace WamKern::Platform