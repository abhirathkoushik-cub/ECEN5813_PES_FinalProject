/*******************************************************************************
 * Copyright (C) 2024 by Abhirath Koushik
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Abhirath Koushik and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    zx_sensor_functions.c
 * @brief   This file contains the functions for the ZX Sensor.
 *
 *
 * @author  Abhirath Koushik
 * @date    12-11-2024
 *
 */

#include <stdio.h>
#include "zx_sensor_functions.h"
#include "supporting_functions.h"
#include "i2c_functions.h"


// Defining Enum for states of the state machine used for gesture detection
typedef enum {
    STATE_IDLE,
    STATE_LEFT_SWIPE,
    STATE_RIGHT_SWIPE,
    STATE_NO_GESTURE
} GestureState;

GestureState current_state = STATE_IDLE;

/*
 * This function is used to identify the Gestures and ZX Positions at those instances.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void read_gesture_and_positions(void) {
    uint8_t status, gesture, xpos, zpos;

    // Check the gesture status register (0x00)
    I2C_ReadReg(ZX_SENSOR_I2C_ADDRESS, ZX_REG_STATUS, &status, 1);

    if (status & (uint8_t)ZX_GES_MASK) { // Gesture detected
        // Read gesture register (0x04)
        I2C_ReadReg(ZX_SENSOR_I2C_ADDRESS, ZX_REG_GESTURE, &gesture, 1);

        // Read X and Z positions
        I2C_ReadReg(ZX_SENSOR_I2C_ADDRESS, ZX_REG_XPOS, &xpos, 1);
        I2C_ReadReg(ZX_SENSOR_I2C_ADDRESS, ZX_REG_ZPOS, &zpos, 1);

        switch (current_state) {
			case STATE_IDLE:
				if (gesture == 0x01) {
					current_state = STATE_RIGHT_SWIPE;
				} else if (gesture == 0x02) {
					current_state = STATE_LEFT_SWIPE;
				} else {
					current_state = STATE_NO_GESTURE;
				}
				break;

			case STATE_LEFT_SWIPE:
				printf("\n\rLeft Swipe Detected!\n\r");
				printf("\n\rZ Value is %d\n\r", zpos);
				printf("\n\rX Value is %d\n\r", xpos);
				GPIOB->BSRR = LED_D4_OFF_MSK;
				GPIOB->BSRR = LED_D5_ON_MSK;
				current_state = STATE_IDLE;
				break;

			case STATE_RIGHT_SWIPE:
				printf("\n\rRight Swipe Detected!\n\r");
				printf("\n\rZ Value is %d\n\r", zpos);
				printf("\n\rX Value is %d\n\r", xpos);
				GPIOB->BSRR = LED_D4_ON_MSK;
				GPIOB->BSRR = LED_D5_OFF_MSK;
				current_state = STATE_IDLE;
				break;

			case STATE_NO_GESTURE:
				GPIOB->BSRR = LED_D4_OFF_MSK;
				GPIOB->BSRR = LED_D5_OFF_MSK;
				current_state = STATE_IDLE;
				break;

			default:
				current_state = STATE_IDLE;
				break;
		}
    }
}
