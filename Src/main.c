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
 * @file    main.c
 * @brief   This is the Main file with the initial program executions.
 *
 *
 * @author  Abhirath Koushik
 * @date    12-11-2024
 *
 */

#include <stdio.h>
#include "utilities.h"
#include "i2c_functions.h"
#include "zx_sensor_functions.h"
#include "supporting_functions.h"
#include "test_zx_sensor.h"

/*
 * This function initializes the components and starts the program executions.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
int main(void) {
    printf("\n\rStarting Gesture Detection Program...\n\r");

    I2C_Init();  // Initialize I2C peripheral
    led_init(); // Initialize the LED Pins

    // Execute Defined Automated Testcases
    if (execute_all_tests() == 1){
		printf("\n\rAll Automated Tests have Passed!\n\r");
    } else{
    	printf("\n\rTest Failures observed in Automated Tests. Please Check!\n\r");
    }

    printf("\n\n\rNow Waiting for Gestures from User.....\n\r");
    while (1) {
    	read_gesture_and_positions(); // Continuously Read Gestures
        delay_ms(500);
    }
}
