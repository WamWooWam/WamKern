TARGET ?= powerpc
SRC_DIRS ?= ./src ./extern

CC=clang
CXX=clang++
LD=ld.lld
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := ./inc ./extern 
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
LDFLAGS := -nostdlib 

powerpc: CPPFLAGS := $(INC_FLAGS) -target powerpc-none-elf -march=powerpc -mtune=g4 -O2 -nostdlib -ffreestanding -DPOWERPC -DBIG_ENDIAN -I/usr/powerpc-linux-gnu/include/
test: CPPFLAGS := $(INC_FLAGS) -DTEST -static -g -DLITTLE_ENDIAN -I/usr/x86_64-linux-gnu/include/

CXXFLAGS ?= -std=c++17 -fno-rtti -fno-exceptions

powerpc: $(OBJS)
	mkdir -p bin
	$(LD) $(LDFLAGS) -e main $(OBJS) -o ./bin/boot.elf

test: $(OBJS) 
	mkdir -p bin 
	$(LD) $(OBJS) -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 /usr/lib/x86_64-linux-gnu/crt1.o /usr/lib/x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/9/crtbegin.o -L/usr/lib/gcc/x86_64-linux-gnu/9 -L/usr/lib/x86_64-linux-gnu -L/usr/lib64 -L/lib/x86_64-linux-gnu -L/lib/../lib64 -L/usr/lib/x86_64-linux-gnu -L/usr/lib64 -L/usr/lib64 -L/usr -L/usr/lib/llvm-10/lib -L/lib -L/usr/lib -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s --no-as-needed /usr/lib/gcc/x86_64-linux-gnu/9/crtend.o /usr/lib/x86_64-linux-gnu/crtn.o -o ./bin/test.elf 

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS) 

-include $(DEPS)
