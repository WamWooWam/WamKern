#pragma once
#include "platform/baseplatform.hpp"

namespace WamKern {
class Kernel {
   public:
    static char StackBase[0x8000];
    [[noreturn]] static void Run(void* ofInterface);
    [[noreturn]] static void Panic(const char* msg);

   private:
    static Platform::BasePlatform* _platform;
};
}  // namespace WamKern