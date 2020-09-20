#pragma once
#include "platform/openfirmware/clientinterface.hpp"
#include "platform/platform.hpp"

namespace WamKern::Platform::OpenFirmware {
class OFPlatform : public Platform {
   public:
    OFPlatform(void* clientInterfacePtr);
    OFPlatform(const OFPlatform&) = delete;
    OFPlatform(const OFPlatform&&);

    void InitMemory();
    Graphics::GraphicsDriver* CreateGraphicsDriver();
    
    void WriteToConsole(const char* text, size_t length);
    [[noreturn]] void Halt();
    [[noreturn]] void Exit();

   private:
    ClientInterface _clientInterface;
    Cell _chosenPH = 0;

    // stdout package handle
    Cell _stdoutPH = 0;
    // stdout instance handle
    Cell _stdoutIH = 0;
    // stdin instance handle
    Cell _stdinIH = 0;

    // memory map package handle
    Cell _memmapPH = 0;

    // memory instance handle
    Cell _memIH = 0;
    // mmu instance handle
    Cell _mmuIH = 0;

    const void* _mallocAddress = (void*)0x04000000;
    const ptrdiff_t _mallocSize = 32 * 1024 * 1024;
};
}  // namespace WamKern::Platform