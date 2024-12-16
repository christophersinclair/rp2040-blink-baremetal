/* Define memory regions */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 2M
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}

/* Define sections and their placement in memory */
SECTIONS
{
    /* Interrupt vector table goes at the start of FLASH */
    .isr_vector : {
        *(.isr_vector)   /* The interrupt vector table */
    } > FLASH

    /* Code and read-only data go into FLASH */
    .text : {
        *(.text)         /* Code */
        *(.rodata*)      /* Read-only data (e.g., const variables) */
        KEEP(*(.init))   /* Initialization code */
        KEEP(*(.fini))   /* Finalization code */
    } > FLASH

    /* Initialized data goes into RAM, but its initial values are stored in FLASH */
    .data : {
        *(.data)         /* Initialized data */
    } > RAM AT > FLASH

    /* Uninitialized data (zeroed at runtime) goes into RAM */
    .bss : {
        *(.bss)          /* Uninitialized variables */
        *(COMMON)        /* Common symbols */
    } > RAM

    /* Stack section */
    .stack : {
        . = ALIGN(8);              /* Align to 8-byte boundary */
        __stack_top = .;           /* Define the top of the stack */
        . = . + 0x1000;            /* Reserve 4KB for the stack */
        __stack_bottom = .;        /* Define the bottom of the stack */
    } > RAM

    /* Heap section (for dynamic memory allocation) */
    . = ALIGN(4);                  /* Align to 4-byte boundary */
    __heap_start = .;              /* Define the start of the heap */
    . = ORIGIN(RAM) + LENGTH(RAM);   /* Move to the end of RAM */
    __heap_end = .;                /* Define the end of the heap */
}