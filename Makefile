#------------------------------------------------------------------------------
# Makefile that can compile multiple source files and support two platform targets
#
# Use: make [TARGET] [OVERRIDES]
#
# Build Targets:
#      <FILE>.o - Builds <FILE>.o object file without linking
#      build - Builds and links all source files
#      clean - Removes all generated files
#
#
#------------------------------------------------------------------------------
SOURCES = hal.c \
		  blink.c \
		  startup.c

BASENAME = blink
TARGET = $(BASENAME).elf

GEN_FLAGS = -Wall \
            -Werror \
            -g \
            -O0 \
            -std=c99

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
LINKER_FILE = linker.ld

CPU = cortex-m0plus
ARCH = thumb
EXTRA_LDFLAGS = -nostartfiles \
				-T $(LINKER_FILE) \
                --specs=nosys.specs

CFLAGS = -mcpu=$(CPU) \
         -mthumb \
         $(GEN_FLAGS) \
         $(EXTRA_CFLAGS)

LDFLAGS = -Wl,-Map=$(BASENAME).map $(EXTRA_LDFLAGS)

OBJS = $(SOURCES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: build
build: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET) $(BASENAME).map *.out *.o *.asm *.i *.d *.uf2