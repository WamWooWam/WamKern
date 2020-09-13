TARGET ?= ./bin/boot.elf
SRC_DIRS ?= ./src

CC=clang
CXX=clang++
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := ./inc
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -target powerpc-none-elf -march=powerpc -nostdlib -ffreestanding
CXXFLAGS ?= -std=c++17

$(TARGET): $(OBJS)
	mkdir -p bin
	ld.lld $(LDFLAGS) -e main $(OBJS) -o $@

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)
