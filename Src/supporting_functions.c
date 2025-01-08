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
 * @file    supporting_functions.c
 * @brief   This file contains the supporting functions required for the program executions.
 *
 *
 * @author  Abhirath Koushik
 * @date    12-11-2024
 *
 */

#include "stm32f0xx.h"
#include "supporting_functions.h"
#include "utilities.h"

// Define the variable to indicate how many iterations required for a 1 millisecond delay
#define LOOP_DELAY_TIME 2500

/*
 * This is used as a delay function during the sensor detect sequence.
 *
 * Parameters:
 *   milliseconds: Delay time in milliseconds
 *
 * Returns:
 *   None
 */
void delay_ms(unsigned int milliseconds)
{
	while(milliseconds > 0)
	{
		for (int i = 0; i < LOOP_DELAY_TIME; i++) // Looping time for a 1 milli second delay
		{}
		milliseconds--;
	}
}

/*
 * This function is used to initialize the LED GPIO Pins.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void led_init(void)
{
	// Configure GPIOA pins for D2 (PA2) and D3 (PA3) as output
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER4, ESF_GPIO_MODER_OUTPUT);
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER5, ESF_GPIO_MODER_OUTPUT);

	// Ensure that LEDs are Off Initially
	GPIOB->BSRR = LED_D4_OFF_MSK;
	GPIOB->BSRR = LED_D5_OFF_MSK;
}
