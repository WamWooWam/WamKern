#include "main.hpp"

using namespace WamKern;

extern "C" {
int main(void *, void *, void *ofInterface) {
    long stackPtr = (long)Kernel::StackBase + sizeof(Kernel::StackBase) - 0x100;
    __asm__ volatile("mr 1, %0"
                     :
                     : "r"(stackPtr));  // fix the stack pointer to something reasonable

    InitAlloc();
    Kernel::Run(ofInterface);
}
}