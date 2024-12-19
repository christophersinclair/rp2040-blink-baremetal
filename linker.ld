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

    .text : ALIGN(0x4) {
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

    .stack : {
        . = ALIGN(8);              /* Align to 8-byte boundary */
        __stack_top = .;           /* Define the top of the stack */
        . = . + 0x1000;            /* Reserve 4KB for the stack */
        __stack_bottom = .;        /* Define the bottom of the stack */
    } > RAM

    /* Heap section (for dynamic memory allocation) */
    . = ALIGN(4);                  /* Align to 4-byte boundary */
    __heap_start = .;              /* Define the start of the heap */
    . = ORIGIN(RAM) + LENGTH(RAM); /* Move to the end of RAM */
    __heap_end = .;                /* Define the end of the heap */
}