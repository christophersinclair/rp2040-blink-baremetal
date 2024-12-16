/******************************
* Copyright 2024 Chris Sinclair
* All Rights Reserved.
*
* @file main.c
* @brief RR2040 Onboard LED Blink - Baremetal (No SDK)
* 
* This program directly modifes the registers referenced in the
* RP2040 datasheet to enable GPIO driving, set the correct GPIO pin
* to an output, and drive a high and low signal repeatedly.
*
* @author Chris Sinclair
* @date 12/2024
*
**************************************/
#include <stdint.h>

/* Base address for GPIO control registers */
#define GPIO_BASE 0xD0000000
#define GPIO0_CTRL_OFFSET 0x04 // initial offset for GPIO 0 control
#define GPIO_REGISTER_OFFSET 0x08 // difference between GPIO registers is 8 bytes

#define GPIO_OE (GPIO_BASE + 0x20) // output enable register
#define GPIO_OUT (GPIO_BASE + 0x10) // output data register

#define PIN_NUMBER 25

/* Register macros for GPIO_CTRL - required to drive output */
/* Example: 0xD0000000 + (0x08 * 25) + 0x04 */
#define GPIO_CTRL(pin) (GPIO_BASE + GPIO0_CTRL_OFFSET + (GPIO_REGISTER_OFFSET * (pin)))
#define FUNC_SIO 5 // function select value for software-controlled GPIO

volatile uint32_t *gpio_oe = (uint32_t *)GPIO_OE;
volatile uint32_t *gpio_out = (uint32_t *)GPIO_OUT;

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

void delay(void) {
    for (volatile int i = 0; i < 1000000; i++) { }
}

int main(void) {
    set_pin_mode_output(PIN_NUMBER);
    while (1) {
        digital_write_high(PIN_NUMBER);
        delay();
        digital_write_low(PIN_NUMBER);
        delay();
    }
}