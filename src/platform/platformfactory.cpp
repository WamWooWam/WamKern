#include "platform/platformfactory.hpp"

#include "lib/std.h"
namespace WamKern::Platform {
Platform* PlatformFactory::CreateDefaultPlatform(void* data) {
    CurrentPlatform platform{data};
    platform.InitMemory();
    return new CurrentPlatform(std::move(platform));
}
}  // namespace WamKern::Platform