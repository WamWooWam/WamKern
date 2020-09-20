#pragma once
#include <stdarg.h>

#include "platform/platform.hpp"

#define KernelLog(format) WamKern::Kernel::Log(__BASE_FILE__, __func__, __LINE__, format)
#define KernelLogF(format, ...) WamKern::Kernel::Log(__BASE_FILE__, __func__, __LINE__, format, __VA_ARGS__)

namespace WamKern {
class Kernel {
   public:
    static char StackBase[0x8000];
    
    [[noreturn]] static void Run(void* ofInterface);
    [[noreturn]] static void Panic(const char* msg);
    static void Log(const char* file, const char* func, int lineNum, const char* messageFormat, ...);

   private:
    static Platform::Platform* _platform;
};


}  // namespace WamKern