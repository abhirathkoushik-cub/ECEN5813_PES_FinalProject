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
 * @file    test_zx_sensor.c
 * @brief   This file contains the Functions of the Test Functions for the ZX Sensor.
 *
 *
 * @author  Abhirath Koushik
 * @date    12-12-2024
 *
 */
#include <stdio.h>
#include <stdint.h>
#include "zx_sensor_functions.h"
#include "test_zx_sensor.h"
#include "i2c_functions.h"

#define TEST_1_COUNT 2
#define TEST_ZX_LOOP_COUNT 10
#define TEST_PASS_VALUE 3
#define XZ_AXIS_MAX_VALUE 255

int execute_all_tests(void)
{
	int flag = 0;
	flag += test_zx_sensor_init();
	flag += test_zx_sensor_z_values();
	flag += test_zx_sensor_x_values();

	if (flag == TEST_PASS_VALUE){
		return 1;
	} else {
		printf("\n\rTests have Failed!\n\r");
		return 0;
	}
}
/*
 * This function is used to test the Sensor Initialization by reading the Model ID through I2C Read.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   1: Success
 *   0: Failure
 */
int test_zx_sensor_init(void)
{
	uint8_t reg_value;
	int test_count = 0;
	I2C_ReadReg(ZX_SENSOR_I2C_ADDRESS, ZX_MODEL_REG, &reg_value, 1);
	printf("\n\rSensor Model ID: 0x%02X\n\r", reg_value);

	if (reg_value != ZX_SENSOR_ID) {
		printf("\n\rInvalid Sensor Model. Initialization Test Failed!\n\r");
	} else {
		printf("\n\rInitialization Test-1 Passed!\n\r");
		test_count++;
	}

	// Choosing invalid register (gesture register 0x04) for Sensor Model ID (register 0xff)
	I2C_ReadReg(ZX_SENSOR_I2C_ADDRESS, ZX_REG_GESTURE, &reg_value, 1);
	printf("\n\rSensor Model ID: 0x%02X\n\r", reg_value);
	if (reg_value != ZX_SENSOR_ID) {
		printf("\n\rInvalid Sensor Model. Invalid Initialization Test-2 Passed!\n\r");
		test_count++;
	} else {
		printf("\n\rInvalid Initialization Test-2 Failed!\n\r");
	}

	if (test_count == TEST_1_COUNT){
		printf("\n\rTest-1 Passed!\n\r");
		return 1;
	} else{
		printf("\n\rTest-1 Failed. Please Check!\n\r");
		return 0;
	}
}

/*
 * This function is used to test if the Sensor Z Values lies in the 8-bit range (0-255)
 * as mentioned by the ZX Sensor Datasheet.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   1: Success
 *   0: Failure
 */
int test_zx_sensor_z_values(void)
{
	uint8_t zpos;
	int test_flag = 0;
	for (int i=0; i < TEST_ZX_LOOP_COUNT; i++){
		I2C_ReadReg(ZX_SENSOR_I2C_ADDRESS, ZX_REG_ZPOS, &zpos, 1);
		printf("\n\rZ Value is %d\n\r", zpos);
		if (zpos < 0 || zpos > XZ_AXIS_MAX_VALUE){
			test_flag = 1;
			break;
		}
	}

	if (test_flag == 0)
	{
		printf("\n\rZ Value Test Passed!\n\r");
		return 1;
	}else {
		printf("\n\rInvalid Z Position Value. Z Value Test Failed!\n\r");
		return 0;
	}
}

/*
 * This function is used to test if the Sensor X Values lies in the 8-bit range (0-255)
 * as mentioned by the ZX Sensor Datasheet.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   1: Success
 *   0: Failure
 */
int test_zx_sensor_x_values(void)
{
	uint8_t xpos;
	int test_flag = 0;
	for (int i=0; i < TEST_ZX_LOOP_COUNT; i++){
		I2C_ReadReg(ZX_SENSOR_I2C_ADDRESS, ZX_REG_XPOS, &xpos, 1);
		printf("\n\rX Value is %d\n\r", xpos);
		if (xpos < 0 || xpos > XZ_AXIS_MAX_VALUE){
			test_flag = 1;
			break;
		}
	}

	if (test_flag == 0)
	{
		printf("\n\rX Value Test Passed!\n\r");
		return 1;
	}else {
		printf("\n\rInvalid X Position Value. X Value Test Failed!\n\r");
		return 0;
	}
}
