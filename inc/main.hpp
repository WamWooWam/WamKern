#pragma once
#include "kernel/kernel.hpp"
#include "lib/alloc.h"

extern "C" {
#ifdef TEST
int main();
#else
int main(void* unused1, void* unused2, void* ofInterface);
#endif
}
