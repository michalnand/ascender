CXX_SRCS = $(shell find  -name '*.cpp')
CXX_SRCS+= $(shell find  ../kodama -name '*.cpp')
CXX_SRCS+= $(shell find  ../device -name '*.cpp')

C_SRCS	 = $(shell find  ../device -name '*.c')

INC = -I .
INC+= -I ..
INC+= -I ../device
INC+= -I ../device/CMSIS/
INC+= -I ../device/STM32F7xx_HAL_Driver/Inc/
INC+= -I ../kodama
INC+= -I ../kodama/drivers
INC+= -I ../kodama/robotics

INC+= -I ./libs
INC+= -I ./behavior

INCC+= -I ..
INCC+= -I ../device
INCC+= -I ../device/CMSIS/
INCC+= -I ../device/STM32F7xx_HAL_Driver/Inc/

TARGET = -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -fsingle-precision-constant -DSTM32F746xx



GCCPREFIX=arm-none-eabi-
LDSCRIPT = ../device/ldscript.ld

ELF = bin/main.elf

CC = $(GCCPREFIX)gcc
CXX = $(GCCPREFIX)g++
LD = $(GCCPREFIX)g++
OBJCOPY = $(GCCPREFIX)objcopy
OBJDUMP = $(GCCPREFIX)objdump
SIZE = $(GCCPREFIX)size


CCFLAGS = -c -O3 -Os -s -Wall -Wextra -pedantic -std=c99 $(INCC)
CCFLAGS+= -Wshadow -Wpointer-arith -Wcast-qual -Wno-unused-variable -Wno-unused-parameter
CCFLAGS+= $(TARGET) -fdata-sections -ffunction-sections


CXXFLAGS = -c -O2 -Os -s -Wall -Wextra -pedantic -std=c++14  -fno-rtti -fno-exceptions $(INC)
CXXFLAGS+= -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align
CXXFLAGS+= $(TARGET) -fdata-sections -ffunction-sections

LDFLAGS = -T$(LDSCRIPT) $(TARGET) -mthumb -Wl,--gc-sections --specs=nosys.specs


C_OBJS = $(C_SRCS:.c=.o)
CXX_OBJS = $(CXX_SRCS:.cpp=.o)


all: $(ELF)
	$(OBJDUMP) --disassemble -D -z $< > bin/main.asm
	$(OBJCOPY) -O ihex $< bin/main.hex
	$(OBJCOPY) -O binary $< bin/main.bin
	$(SIZE) $(ELF)

$(ELF): $(C_OBJS) $(CXX_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(C_OBJS) $(CXX_OBJS)

%.o: %.c
	$(CC) $(CCFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

CLEAN_FILES = $(C_OBJS)
CLEAN_FILES+= $(CXX_OBJS)
CLEAN_FILES+= bin/main*

clean:
	rm $(CLEAN_FILES) -rf
