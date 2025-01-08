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
 * @file    zx_sensor_functions.h
 * @brief   This file contains the Function Prototypes for the ZX Sensor Functions.
 *
 *
 * @author  Abhirath Koushik
 * @date    12-11-2024
 *
 */

#define ZX_SENSOR_I2C_ADDRESS 0x10  // ZX Sensor I2C address
#define ZX_REG_STATUS         0x00  // Gesture status register
#define ZX_REG_GESTURE        0x04  // Gesture result register
#define ZX_MODEL_REG          0xFF  // Sensor Model register
#define ZX_REG_XPOS           0x08  // X Position register
#define ZX_REG_ZPOS           0x0A  // Z Position register
#define ZX_SENSOR_ID          0x01  // ZX Sensor Model ID
#define ZX_GES_MASK           0b00011100 // Defining the mask value to identify the gestures

// Define the Function Prototypes
void read_gesture_and_positions(void);
