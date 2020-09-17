// error handler for if pure virtual functions somehow get called directiy
#include "kernel/kernel.hpp"

extern "C" {
void __cxa_pure_virtual() {
    WamKern::Kernel::Panic("Attempt to call pure virtual function!!");
}
}