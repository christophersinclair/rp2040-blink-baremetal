/******************************
* @file main.h
* @brief Function declarations for the Baremetal blink program
*
* @author Chris Sinclair
* @date 12/2024
*
**************************************/
#include <stdint.h>

#ifndef __MAIN_H__
#define __MAIN_H__

/**
* Function: set_pin_mode_output
* @brief Set the pin mode to output
* @param pin_number The GPIO pin number
* @return void
*/
void set_pin_mode_output(uint32_t pin_number);

/**
* Function: digital_write_high
* @brief Drive the given pin to digital HIGH
* @param pin_number The GPIO pin number
* @return void
*/
void digital_write_high(uint32_t pin_number);

/**
* Function: digital_write_low
* @brief Drive the given pin to digital LOW
* @param pin_number The GPIO pin number
* @return void
*/
void digital_write_low(uint32_t pin_number);

/**
* Function: delay
* @brief Delay by running a non-compiler-optimized-away loop
* @param void
* @return void
*/
void delay(void);

#endif /* __MAIN_H__ */