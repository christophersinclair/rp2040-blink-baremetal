/******************************
* @file startup.c
* @brief Startup file for RP2040
* 
* Contains reset handler executed after CPU reset,
* the initial stack pointer (defined in linker 
* script), as well as the exception and interrupt 
* vector table.
*
* @author Chris Sinclair
* @date 12/2024
*
**************************************/
#include <stdint.h>

/* Linker script symbols */
extern uint32_t __stack_top;   // Top of the stack
extern uint32_t __data_start__; // Start of .data in RAM
extern uint32_t __data_end__;   // End of .data in RAM
extern uint32_t __bss_start__;  // Start of .bss in RAM
extern uint32_t __bss_end__;    // End of .bss in RAM
extern uint32_t __data_load__;  // Start of .data in FLASH

void Reset_Handler(void);
void Default_Handler(void);

__attribute__((section(".isr_vector"))) const void *vector_table[] = {
    (void *)&__stack_top, // Initial stack pointer
    Reset_Handler,         // Reset handler
    Default_Handler,       // NMI handler
    Default_Handler,       // HardFault handler
    Default_Handler,       // Reserved
    Default_Handler,       // Reserved
    Default_Handler,       // Reserved
    Default_Handler,       // Reserved
    Default_Handler,       // Reserved
    Default_Handler,       // Reserved
    Default_Handler,       // Reserved
    Default_Handler,       // SVC handler
    Default_Handler,       // Reserved
    Default_Handler,       // Reserved
    Default_Handler,       // PendSV handler
    Default_Handler,       // SysTick handler
};

void Reset_Handler(void) {
    /* Copy .data section from FLASH to RAM */
    uint32_t *src = &__data_load__;
    uint32_t *dest = &__data_start__;
    while (src < &__data_end__) {
        *dest++ = *src++;
    }

    /* Zero out the .bss section in RAM */
    dest = &__bss_start__;
    while (dest < &__bss_end__) {
        *dest++ = 0;
    }

    /* Call the main function */
    extern void main(void);
    main();
}

void Default_Handler(void) {
    while (1) {}
}
