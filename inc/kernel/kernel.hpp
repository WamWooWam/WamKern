#pragma once

namespace WamKern {
class Kernel {
   public:
    static char StackBase[0x8000];
    [[noreturn]] static void InitKernel(void* ofInterface);
};
}  // namespace WamKern