#pragma once
#include <stddef.h>

#include "platform/platform.hpp"

#ifdef TEST
#include "platform/test/testplatform.hpp"
#define PLATFORM Test::TestPlatform
#elif POWERPC
#include "platform/openfirmware/ofplatform.hpp"
#define PLATFORM OpenFirmware::OFPlatform
#else
#error No supported platform available
#endif

namespace WamKern::Platform {
typedef PLATFORM CurrentPlatform;
struct PlatformFactory {
    static Platform* CreateDefaultPlatform(void* data);
};
}  // namespace WamKern::Platform