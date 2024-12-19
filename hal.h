/******************************
* @file hal.h
* @brief Function declarations for the HAL
*
* @author Chris Sinclair
* @date 12/2024
*
**************************************/
#include <stdint.h>

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
* @return void
*/
void digital_write(uint32_t pin_number, uint32_t state);

/**
* Function: digital_read
* @brief Read the digital state of the given pin
* @param pin_number The GPIO pin number
* @return void
*/
uint8_t digital_read(uint32_t pin_number);

/**
* Function: delay
* @brief Delay by running a non-compiler-optimized-away loop
* @param void
* @return void
*/
void delay(uint32_t count);

#endif /* __HAL_H__ */