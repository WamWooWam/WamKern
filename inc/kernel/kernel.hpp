#pragma once
#include "platform/baseplatform.hpp"

namespace WamKern {
class Kernel {
   public:
    static char StackBase[0x8000];
    [[noreturn]] static void InitKernel(void* ofInterface);

   private:
    Platform::BasePlatform* _platform;
};
}  // namespace WamKern