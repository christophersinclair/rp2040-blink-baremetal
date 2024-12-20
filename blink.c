/******************************
* Copyright 2024 Chris Sinclair
* All Rights Reserved.
*
* @file blink.c
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
#include "hal.h"

#define ONBOARD_LED_PIN_NUMBER 25

void main(void) {
    set_pin_mode_output(ONBOARD_LED_PIN_NUMBER);
    while (1) {
        /* Method 1 of toggling*/
        digital_write(ONBOARD_LED_PIN_NUMBER, 1);
        delay(1000000);
        digital_write(ONBOARD_LED_PIN_NUMBER, 0);
        delay(1000000);

        /* Method 2 of toggling */
        digital_toggle(ONBOARD_LED_PIN_NUMBER);
        delay(400000000);
        digital_toggle(ONBOARD_LED_PIN_NUMBER);
        delay(400000000);

        /* Method 3 of toggling */
        digital_write(ONBOARD_LED_PIN_NUMBER, !digital_read(ONBOARD_LED_PIN_NUMBER));
        delay(500000000);
        digital_write(ONBOARD_LED_PIN_NUMBER, !digital_read(ONBOARD_LED_PIN_NUMBER));
        delay(500000000);
    }
}
