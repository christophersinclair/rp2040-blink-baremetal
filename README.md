# RP2040 Blink Baremetal (No SDK)

This project showcases baremetal programming against the Raspberry Pi Pico (RP2040) through direct register access.

`blink.c` - Program code
`linker.ld` - Linker file to use to map code to physical memory regions
`startup.c` - Startup code that runs on board boot

To compile, use:
`arm-none-eabi-gcc -T linker.ld -o blink.elf blink.c startup.c -nostartfiles -Wl,--gc-sections`

To convert to the resulting binary from the previous command into one bootable by the Pico:
`arm-none-eabi-objcopy -O binary blink.elf blink.uf2`

To copy the binary to the Pico, hold down the BOOTSEL button on the board while plugging it into the computer, then run:
`cp blink.uf2 /media/pi/PICO`

Huge shoutout to the RP2040 datasheet, which contains all the registers addresses, offsets, and GPIO function selection tables: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf

