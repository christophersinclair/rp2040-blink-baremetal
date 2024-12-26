MEMORY
{
    FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 2M
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}

ENTRY(Reset_Handler)

SECTIONS
{
    .text : {
        KEEP(*(.isr_vector))
        *(.text)         
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        *(.eh_frame)
        KEEP(*(.init))
        KEEP(*(.fini))
        _etext = .;
    } > FLASH

    .data : ALIGN(4) {
        __data_load__ = LOADADDR(.data);
        __data_start__ = .;
        *(.data)
        __data_end__ = .;
    } > RAM AT > FLASH

    .bss : ALIGN(4) {
        __bss_start__ = .; 
        *(.bss)            
        *(COMMON)          
        __bss_end__ = .;   
    } > RAM

    .heap : {
        __heap_start = .;
        . = ORIGIN(RAM) + LENGTH(RAM) - 4K;
        __heap_end = .;
    } > RAM

    .stack (NOLOAD) : ALIGN(8) {
        __stack_bottom = __heap_end;
        . = __stack_bottom + 4K;                /* Reserve 4KB for stack */
        __stack_top = .;                     
    } > RAM
}
