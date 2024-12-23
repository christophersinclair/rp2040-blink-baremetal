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
extern uint32_t __INITIAL_SP;   // Top of the stack
extern uint32_t __data_start__; // Start of .data in RAM
extern uint32_t __data_end__;   // End of .data in RAM
extern uint32_t __bss_start__;  // Start of .bss in RAM
extern uint32_t __bss_end__;    // End of .bss in RAM
extern uint32_t __data_load__;  // Start of .data in FLASH

void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);

__attribute__((section(".isr_vector"))) const uint32_t VectorTable[] = {
    (uint32_t)&__INITIAL_SP,     // Initial stack pointer
    (uint32_t)Reset_Handler,     // Reset handler
    (uint32_t)NMI_Handler,       // NMI handler
    (uint32_t)HardFault_Handler, // HardFault handler
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

void NMI_Handler(void) {
    while (1) {}
}

void HardFault_Handler(void) {
    while (1) {}
}

void Default_Handler(void) {
    while (1) {}
}
