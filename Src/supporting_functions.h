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
 * @file    supporting_functions.h
 * @brief   This is the Header file with the Macros and Function Prototypes for the Supporting Functions.
 *
 *
 * @author  Abhirath Koushik
 * @date    12-11-2024
 *
 */

#include <stdint.h>

// Define the LED Masks
#define LED_D4_OFF_MSK (GPIO_BSRR_BR_4)
#define LED_D4_ON_MSK (GPIO_BSRR_BS_4)
#define LED_D5_OFF_MSK (GPIO_BSRR_BR_5)
#define LED_D5_ON_MSK (GPIO_BSRR_BS_5)

//Define the Function Prototypes
void delay_ms(unsigned int milliseconds);
void led_init(void);
