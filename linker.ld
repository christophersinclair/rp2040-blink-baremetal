MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 2M
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}

SECTIONS
{
    .isr_vector : {
        *(.isr_vector)
    } > FLASH

    .text : {
        *(.text)         
        *(.rodata*)
    } > FLASH

    .data : {
        __data_load__ = .;
        *(.data)
        __data_end__ = .;
    } > FLASH

    .bss : {
        __bss_start__ = .; 
        *(.bss)            
        *(COMMON)          
        __bss_end__ = .;   
    } > RAM

    .data : {
        __data_start__ = .;
        *(.data)
    } > RAM

    /* Heap */
    . = ALIGN(8);
    __heap_start = .;

    .stack (NOLOAD) : {
        __INITIAL_SP = ORIGIN(RAM) + LENGTH(RAM); /* Top of the stack at the end of RAM */
        . = __INITIAL_SP - 0x1000;                /* Reserve 4KB for stack */
        __stack_bottom = .;                     
    } > RAM

    __heap_end = __stack_bottom;                /* End heap at bottom of stack */
}
