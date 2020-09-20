#pragma once
#include <stddef.h>

#include "platform/platform.hpp"

#ifdef TEST
#include "platform/testplatform.hpp"
#define PLATFORM TestPlatform
#elif POWERPC
#include "platform/openfirmware.hpp"
#define PLATFORM OpenFirmwarePlatform
#else
#error No supported platform available
#endif

namespace WamKern::Platform {
typedef PLATFORM CurrentPlatform;
struct PlatformFactory {
    static Platform* CreateDefaultPlatform(void* data);
};
}  // namespace WamKern::Platform