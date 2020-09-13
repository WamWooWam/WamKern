#include "platform/openfirmware.hpp"

using namespace WamKern::Firmware::OpenFirmware;

namespace WamKern::Platform {
OpenFirmwarePlatform::OpenFirmwarePlatform(void* clientInterfacePtr) {
    _clientInterface = ClientInterface(clientInterfacePtr);

}
}  // namespace WamKern::Platform