/******************************
* Copyright 2024 Chris Sinclair
* All Rights Reserved.
*
* @file hal.c
* @brief RR2040 Hardware Abstraction Layer (HAL) functions
* 
* This file contains the hardware abstraction layer functions
* for the RP2040. These functions are used to set the pin mode
* to output, drive the pin high and low, read pin state,
* and delay execution.
*
* @author Chris Sinclair
* @date 12/2024
*
**************************************/
#include <stdint.h>
#include <stdbool.h>

/* Base address for GPIO control registers */
#define GPIO_BASE 0xD0000000
#define GPIO0_CTRL_OFFSET 0x04 // initial offset for GPIO 0 control
#define GPIO_REGISTER_OFFSET 0x08 // difference between GPIO registers is 8 bytes

#define GPIO_OE (GPIO_BASE + 0x20) // output enable register
#define GPIO_OUT (GPIO_BASE + 0x10) // output data register
#define GPIO_IN (GPIO_BASE + 0x00) // input data register

#define DELAY 1000000

/* Register macros for GPIO_CTRL - required to drive output */
/* Example: 0xD0000000 + (0x08 * 25) + 0x04 */
#define GPIO_CTRL(pin) (GPIO_BASE + GPIO0_CTRL_OFFSET + (GPIO_REGISTER_OFFSET * (pin)))
#define FUNC_SIO 5 // function select value for software-controlled GPIO

volatile uint32_t *gpio_oe = (uint32_t *)GPIO_OE;
volatile uint32_t *gpio_out = (uint32_t *)GPIO_OUT;
volatile uint32_t *gpio_in = (uint32_t *)GPIO_IN;

void set_pin_mode_output(uint32_t pin_number) {
    /* Set the pin function to FUNC_SIO (software-controlled GPIO) */
    volatile uint32_t *gpio_ctrl = (uint32_t *)GPIO_CTRL(pin_number);
    *gpio_ctrl = 0b00101; // FUNC_SIO in datasheet (decimal 5)

    /* Enable output driver for the pin */
    *gpio_oe |= (1UL << pin_number);
}

void digital_write_high(uint32_t pin_number) {
    /**
     * Place a 1 at the register bit controlling pin_number
     *  0 | 1 = 1
     *  1 | 1 = 1 
    */
    *gpio_out |= (1UL << pin_number);
}

void digital_write_low(uint32_t pin_number) {
    /**
     * Place a 0 at the register bit controlling pin_number
     * 0 & 0 = 0
     * 1 & 0 = 0
     */
    *gpio_out &= ~(1UL << pin_number);
}

void digital_toggle(uint32_t pin_number) {
    /**
     * Toggle the pin state by XORing the pin_number bit
     * 0 ^ 1 = 1
     * 1 ^ 1 = 0
     */
    *gpio_out ^= (1UL << pin_number);
}

void digital_write(uint32_t pin_number, uint32_t value) {
    if (value) {
        digital_write_high(pin_number);
    } else {
        digital_write_low(pin_number);
    }
}

bool digital_read(uint32_t pin_number) {
    return (*gpio_in >> pin_number) & 1;
}

void delay(uint32_t count) {
    for (volatile int i = 0; i < count; i++) { }
}