/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Deepanshu Tanwar
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

int main(void)
{
	uint32_t *pClkCtrlReg = (uint32_t*)0x40023830;
	uint32_t *pPortDModeReg = (uint32_t*)0x40020C00;
	uint32_t *pPortDOutReg =(uint32_t*)0x40020C14;
	uint32_t *pPortAModeReg = (uint32_t*)0x40020000;
	uint32_t *pPortAInReg = (uint32_t*)0x40020010;


	//1. enable the clock for GPIOD and GPIOA peripheral in the AHB1ENR
	*pClkCtrlReg |= (1<<3); //GPIOD
	*pClkCtrlReg |= (1<<0); //GPIOA

	//2. Configure PD12 as output
	//a. clear the 24th and 25th bit position (CLEAR)
	*pPortDModeReg &= ~(3<<24);

	//b. make 24th as 1 and 25th bit position as 0 (SET)
	*pPortDModeReg |= (1<<24);

	//3. Configure PA0 as input (GPIOA mode register)
	*pPortAModeReg &= ~(3<<0);




	while(1)
	{
		//4. read the ping status of the pin PA0 (GPIOA input data register)
		uint8_t	pinStatus = (uint8_t)(*pPortAInReg & (0x1)); //zero out all other bits except bit 0
		if(pinStatus)
		{
			*pPortDOutReg |= (1<<12);

		}
		else
		{
			*pPortDOutReg &= ~(1<<12);
		}
	}





}
