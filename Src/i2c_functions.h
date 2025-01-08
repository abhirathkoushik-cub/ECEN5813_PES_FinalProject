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
 * @file    i2c_functions.h
 * @brief   This is the Header file with the I2C Function Prototypes.
 *
 *
 * @author  Abhirath Koushik
 * @date    12-11-2024
 *
 */

#include <stdint.h>
#include "stm32f0xx.h"

// Define the Function Prototypes
void I2C_Init(void);
void I2C_WriteReg(uint8_t dev_adx, uint8_t reg_adx, uint8_t *bufp, uint16_t data_len);
void I2C_ReadReg(uint8_t dev_adx, uint8_t reg_adx, uint8_t *bufp, uint16_t data_len);
