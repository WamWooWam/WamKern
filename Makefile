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
SHARED_FLAGS := $(INC_FLAGS) -nostdlib -ffreestanding -Os
LDFLAGS := -nostdlib 

powerpc: CPPFLAGS := $(SHARED_FLAGS) -target powerpc-none-elf -march=powerpc
powerpc64: CPPFLAGS := $(SHARED_FLAGS) -target powerpc64-none-elf -march=powerpc64
CXXFLAGS ?= -std=c++17 -fno-rtti -fno-exceptions

powerpc: $(OBJS)
	mkdir -p bin
	$(LD) $(LDFLAGS) -e main $(OBJS) --lto-O2 -o ./bin/boot.elf

powerpc64: $(OBJS)
	mkdir -p bin
	$(LD) $(LDFLAGS) -e main $(OBJS) --lto-O2 -o ./bin/boot64.elf

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS) 

-include $(DEPS)
