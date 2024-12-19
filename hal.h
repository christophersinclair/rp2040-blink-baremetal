/******************************
* @file hal.h
* @brief Function declarations for the HAL
*
* @author Chris Sinclair
* @date 12/2024
*
**************************************/
#include <stdint.h>
#include <stdbool.h>

#ifndef __HAL_H__
#define __HAL_H__

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
* Function: digital_toggle
* @brief Toggle the given pin
* @param pin_number The GPIO pin number
* @return void
*/
void digital_toggle(uint32_t pin_number);

/**
* Function: digital_write
* @brief Write the digital state to the given pin
* @param pin_number The GPIO pin number
* @param state The state to write to the pin (0 or 1)
* @return void
*/
void digital_write(uint32_t pin_number, uint32_t state);

/**
* Function: digital_read
* @brief Read the digital state of the given pin
* @param pin_number The GPIO pin number
* @return The state of the pin (0 or 1)
*/
bool digital_read(uint32_t pin_number);

/**
* Function: delay
* @brief Delay by running a non-compiler-optimized-away loop
* @param count The number of iterations to delay
* @return void
*/
void delay(uint32_t count);

#endif /* __HAL_H__ */