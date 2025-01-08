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
 * @file    i2c_functions.c
 * @brief   This file contains the functions for I2C Initialization, Read and Write operations.
 *
 *
 * @author  Abhirath Koushik and Alexander G. Dean
 * @date    12-11-2024
 *
 */

#include "i2c_functions.h"
#include "utilities.h"

#define I2C_TIMING 0x00B01A4B // Defining the Timing as 71 kbaud

/*
 * This function initializes the I2C1 Configuration on Pins 8 and 9 of the board.
 * This code is originally written by Alexander G. Dean.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void I2C_Init(void) {
    // Clock gating for I2C1 and GPIO B
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // GPIO B pin 8 and 9 in alternate function
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER8, ESF_GPIO_MODER_ALT_FUNC);
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER9, ESF_GPIO_MODER_ALT_FUNC);
	// Select I2C1 (AF = 1) as alternate function
	MODIFY_FIELD(GPIOB->AFR[1], GPIO_AFRH_AFSEL8, 1);
	MODIFY_FIELD(GPIOB->AFR[1], GPIO_AFRH_AFSEL9, 1);

	// I2C1 Configuration
	I2C1->CR1 = 0; // Default configuration, peripheral disabled
	I2C1->CR2 = 0; // Default configuration, 7 bit addressing
	I2C1->TIMINGR = I2C_TIMING;

	MODIFY_FIELD(I2C1->CR1, I2C_CR1_PE, 1); // Enable peripheral
}


/*
 * This function is used to write to a register through the I2C Sequence.
 * This code is originally written by Alexander G. Dean.
 *
 * Parameters:
 *   dev_adx:   I2C Address of your device
 *   reg_adx:   Register Address to write into
 *   bufp:      Pointer to the buffer that stores the data to write
 *   data_len:  Length of the Data to write
 *
 * Returns:
 *   None
 */
void I2C_WriteReg(uint8_t dev_adx, uint8_t reg_adx, uint8_t *bufp, uint16_t data_len) {
	uint32_t tmp;
	// -- Send START, Device Address, Write Command --
	tmp = 0;
	MODIFY_FIELD(tmp, I2C_CR2_SADD, dev_adx << 1);
	MODIFY_FIELD(tmp, I2C_CR2_RD_WRN, 0); // Write
	MODIFY_FIELD(tmp, I2C_CR2_NBYTES, data_len+1); //data bytes + reg. adx.
	// Set START to start transfer
	MODIFY_FIELD(tmp, I2C_CR2_START, 1);
	I2C1->CR2 = tmp;
	// Wait until START is cleared by hardware
	while (I2C1->CR2 & I2C_CR2_START)
		;
	// -- Send Register Address --
	I2C1->TXDR = reg_adx;
	// Wait until transmitter empty
	while (!(I2C1->ISR & I2C_ISR_TXE))
		;
	// -- Send Data --
	while (data_len--) {
		I2C1->TXDR = *bufp;
		bufp++;
		while (!(I2C1->ISR & I2C_ISR_TXE))
			;
	}
	// -- Send Stop --
	MODIFY_FIELD(I2C1->CR2, I2C_CR2_STOP, 1);
}


/*
 * This function is used to read from a register through the I2C Sequence.
 * This code is originally written by Alexander G. Dean.
 *
 * Parameters:
 *   dev_adx:   I2C Address of your device
 *   reg_adx:   Register Address to read from
 *   bufp:      Pointer to the buffer that will store the data read
 *   data_len:  Length of the Data to read
 *
 * Returns:
 *   None
 */
void I2C_ReadReg(uint8_t dev_adx, uint8_t reg_adx, uint8_t *bufp, uint16_t data_len) {
	uint32_t tmp;
	// -- Send START, Device Address, Write Command --
	tmp = 0;
	MODIFY_FIELD(tmp, I2C_CR2_SADD, dev_adx << 1);
	MODIFY_FIELD(tmp, I2C_CR2_RD_WRN, 0); // First write addresses
	MODIFY_FIELD(tmp, I2C_CR2_NBYTES, 1); // 1 byte: register address
	MODIFY_FIELD(tmp, I2C_CR2_START, 1); 	// Start transfer
	I2C1->CR2 = tmp;
	while (I2C1->CR2 & I2C_CR2_START) // Wait until START ends
	 ;
	// -- Write Register Address --
	I2C1->TXDR = reg_adx;
	while (!(I2C1->ISR & I2C_ISR_TXE)) // Wait until sent
		;
	// -- Send Repeated START, Device Address, Read Command--
	tmp = I2C1->CR2;
	MODIFY_FIELD(tmp, I2C_CR2_SADD, dev_adx << 1);
	MODIFY_FIELD(tmp, I2C_CR2_RD_WRN, 1);	// Then read data
	MODIFY_FIELD(tmp, I2C_CR2_NBYTES, data_len); // Data byte count
	MODIFY_FIELD(tmp, I2C_CR2_START, 1); // Start transfer
	I2C1->CR2 = tmp;
	// -- Read Data --
	while (data_len--) {
		while (!(I2C1->ISR & I2C_ISR_RXNE)) // Await data rx
			;
		*bufp++ = I2C1->RXDR; // Read RXDR, advance pointer
	}
	// -- Write Stop --
	MODIFY_FIELD(I2C1->CR2, I2C_CR2_STOP, 1);
}
