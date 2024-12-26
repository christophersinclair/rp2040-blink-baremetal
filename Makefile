#------------------------------------------------------------------------------
# Makefile for compiling against RP2040 ARM Cortex-M0+
#
# Use: make [TARGET] [OVERRIDES]
#
# Build Targets:
#      <FILE>.o - Builds <FILE>.o object file without linking
#      build - Builds and links all source files
#      clean - Removes all generated files
#------------------------------------------------------------------------------
SOURCES = hal.c \
		  blink.c \
		  startup.c

BASENAME = blink
TARGET = $(BASENAME).elf

GEN_FLAGS = -Wall \
            -Werror \
			-Wno-error=main \
			-g \
            -O0 \
			-std=c99

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
LINKER_FILE = linker.ld

CPU = cortex-m0plus
ARCH = thumb

CFLAGS = -mcpu=$(CPU) \
         -mthumb \
         $(GEN_FLAGS) \
         $(EXTRA_CFLAGS)

LDFLAGS = -nostartfiles \
		  -T linker.ld \
		  --specs=nosys.specs \

OBJS = $(SOURCES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: build
build: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET) $(BASENAME).map *.out *.o *.asm *.i *.d *.uf2
