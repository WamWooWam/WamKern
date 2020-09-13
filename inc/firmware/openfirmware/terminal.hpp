#pragma once
#include "clientinterface.hpp"

namespace WamKern::Firmware::OpenFirmware {
class Terminal {
   public:
    static void Init();
   private:
    static Cell StdOutIH;
    static Cell StdInIH;
};
}  // namespace WamKern::Firmware::OpenFirmware