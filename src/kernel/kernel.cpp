#include "kernel/kernel.hpp"
#include "firmware/openfirmware/clientinterface.hpp"

using namespace WamKern::Firmware::OpenFirmware;

namespace WamKern {
char Kernel::StackBase[0x8000];

[[noreturn]] void Kernel::InitKernel(void* ofInterface) {
    static const char message[15] = "Hello, world!\n";

    ClientInterface::Init(ofInterface);
    
    Cell chosenCell = ClientInterface::FindDevice("/chosen");
    Cell stdoutCell;

    ClientInterface::GetProp(chosenCell, "stdout", (char*)&stdoutCell, sizeof stdoutCell);
    ClientInterface::Write(stdoutCell, (void*)message, sizeof message);

    ClientInterface::Exit();

    for (;;) {
    }
}
}  // namespace WamKern