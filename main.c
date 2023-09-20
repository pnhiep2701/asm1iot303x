/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
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
#include "system_stm32f4xx.h"
#include "timer.h"
#include "misc.h"
#include "stm32f401re_rcc.h"
#include "stm32f401re_gpio.h"
#include "stm32f401re_exti.h"
#include "stm32f401re_syscfg.h"

/*------------------Private typedef ------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
/*------------------Private define ------------------------*/

/*------------------Private macro ------------------------*/
/* Define Logic GPIO PIN */
#define GPIO_PIN_SET			1
#define GPIO_PIN_RESET			0

/* Define LED Board*/
#define LED_BOARD_GPIO_PORT				GPIOA
#define LED_BOARD_GPIO_PIN				GPIO_Pin_5
#define LED_BOARD_GPIO_PIN5				5
#define LED_BOARD_GPIO_SetClock			RCC_AHB1Periph_GPIOA

/* Define LED Green Pin*/
#define LED_Green_1_GPIO_PORT			GPIOA
#define LED_Green_1_GPIO_PIN			GPIO_Pin_0
#define LED_Green_1_PIN0				0
#define LED_Green_1_SetClock			RCC_AHB1Periph_GPIOA

#define LED_Green_2_GPIO_PORT			GPIOA
#define LED_Green_2_GPIO_PIN			GPIO_Pin_11
#define LED_Green_2_PIN11				11
#define LED_Green_2_SetClock			RCC_AHB1Periph_GPIOA

/* Define LED_1 Blue */
#define LED_BLUE_1_GPIO_PORT			GPIOA
#define LED_BLUE_1_GPIO_PIN				GPIO_Pin_10
#define LED_BLUE_1_GPIO_PIN10			10
#define LED_BLUE_1_SetClock				RCC_AHB1Periph_GPIOA

#define LED_BLUE_2_GPIO_PORT			GPIOA
#define LED_BLUE_2_GPIO_PIN				GPIO_Pin_3
#define LED_BLUE_2_GPIO_PIN3			3
#define LED_BLUE_2_SetClock				RCC_AHB1Periph_GPIOA

/* Define LED Red*/
#define LED_RED_1_GPIO_PORT				GPIOB
#define LED_RED_1_GPIO_PIN				GPIO_Pin_13
#define LED_RED_1_GPIO_PIN13			13
#define LED_RED_1_SetClock				RCC_AHB1Periph_GPIOB

#define LED_RED_2_GPIO_PORT				GPIOA
#define LED_RED_2_GPIO_PIN				GPIO_Pin_1
#define LED_RED_2_GPIO_PIN1				1
#define LED_RED_2_SetClock				RCC_AHB1Periph_GPIOA

/* Define Buzzer */
#define BUZZER_GPIO_PORT				GPIOC
#define BUZZER_GPIO_PIN					GPIO_Pin_9
#define BUZZER_SetClock					RCC_AHB1Periph_GPIOC

/* Define Button Interrupt*/
//Button B2:PB3
#define BUTTONB2_IT_GPIO_PORT			GPIOB
#define BUTTONB2_IT_GPIO_PIN			GPIO_Pin_3
#define BUTTONB2_IT_SetClock			RCC_AHB1Periph_GPIOB

//Button B4:PB0
#define BUTTONB4_IT_GPIO_PORT			GPIOB
#define BUTTONB4_IT_GPIO_PIN			GPIO_Pin_0
#define BUTTONB4_IT_SetClock			RCC_AHB1Periph_GPIOB

//Button B3:PA4
#define BUTTONB3_IT_GPIO_PORT			GPIOA
#define BUTTONB3_IT_GPIO_PIN			GPIO_Pin_4
#define BUTTONB3_IT_SetClock			RCC_AHB1Periph_GPIOA

#define SYSCFG_Clock					RCC_APB2Periph_SYSCFG

/*------------------Private variable-------------------------*/
uint32_t releaseTimeB3 = 0;
uint32_t pressTimeB3 = 0;
uint32_t releaseTimeB2 = 0;
uint32_t pressTimeB2 = 0;
uint32_t releaseTimeB4 = 0;
uint32_t pressTimeB4 = 0;
uint8_t countB3 = 0;
uint8_t countB2 = 0;
uint8_t countB4 = 0;

/*------------------Private function prototypes-------------------------*/

/*
 * @func	LedBuzz_Init
 * @brief	Configure the control pins of the led and buzzer module
 * @param	None
 * retval	None
 * */
static void LedBuzz_Init(void) {
	/*LED_BOARD*/
	//Enable Clock GPIO
	RCC_AHB1PeriphClockCmd(LED_BOARD_GPIO_SetClock, ENABLE);
	//Choose Pin LED
	GPIO_InitStructure.GPIO_Pin = LED_BOARD_GPIO_PIN;
	//Choose Pin mode LED as OUT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//Choose Speed Pin
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//Select Output type
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//Select status
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	//The function initializes all of the above values
	GPIO_Init(LED_BOARD_GPIO_PORT, &GPIO_InitStructure);

	/*LED Green*/
	//Enable Clock GPIO
	RCC_AHB1PeriphClockCmd(LED_Green_1_SetClock, ENABLE);
	//Choose Pin LED
	GPIO_InitStructure.GPIO_Pin = LED_Green_1_GPIO_PIN;
	//Choose Pin LED as Out
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//Choose Speed Pin
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//Select type
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//Select status
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	//The function initializes all of the above values
	GPIO_Init(LED_Green_1_GPIO_PORT, &GPIO_InitStructure);

	//Enable Clock GPIO
	RCC_AHB1PeriphClockCmd(LED_Green_2_SetClock, ENABLE);
	//Choose Pin LED
	GPIO_InitStructure.GPIO_Pin = LED_Green_2_GPIO_PIN;
	//Choose Pin LED as Out
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//Choose Speed Pin
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//Select type
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//Select status
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	//The function initializes all of the above values
	GPIO_Init(LED_Green_2_GPIO_PORT, &GPIO_InitStructure);

	/*LED BLUE*/
	//Enable Clock GPIO
	RCC_AHB1PeriphClockCmd(LED_BLUE_1_SetClock, ENABLE);
	//Choose Pin LED_1
	GPIO_InitStructure.GPIO_Pin = LED_BLUE_1_GPIO_PIN;
	//Choose Pin LED_1 as Out
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//Choose Speed Pin
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//Select type
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//Select status
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	//The function initializes all of the above values
	GPIO_Init(LED_BLUE_1_GPIO_PORT, &GPIO_InitStructure);

	//Enable Clock GPIO
	RCC_AHB1PeriphClockCmd(LED_BLUE_2_SetClock, ENABLE);
	//Choose Pin LED_1
	GPIO_InitStructure.GPIO_Pin = LED_BLUE_2_GPIO_PIN;
	//Choose Pin LED_1 as Out
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//Choose Speed Pin
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//Select type
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//Select status
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	//The function initializes all of the above values
	GPIO_Init(LED_BLUE_2_GPIO_PORT, &GPIO_InitStructure);

	/*LED RED*/
	//Enable Clock GPIO
	RCC_AHB1PeriphClockCmd(LED_RED_1_SetClock, ENABLE);
	//Choose Pin LED_2
	GPIO_InitStructure.GPIO_Pin = LED_RED_1_GPIO_PIN;
	//Choose Pin LED_2 as Out
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//Choose Speed Pin
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//Select type
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//Select status
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	//The function initializes all of the above values
	GPIO_Init(LED_RED_1_GPIO_PORT, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(LED_RED_2_SetClock, ENABLE);
	//Choose Pin LED_2
	GPIO_InitStructure.GPIO_Pin = LED_RED_2_GPIO_PIN;
	//Choose Pin LED_2 as Out
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//Choose Speed Pin
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//Select type
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//Select status
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	//The function initializes all of the above values
	GPIO_Init(LED_RED_2_GPIO_PORT, &GPIO_InitStructure);

	/*BUZZER*/
	//Enable Clock GPIOC
	RCC_AHB1PeriphClockCmd(BUZZER_SetClock, ENABLE);
	//Choose Pin Buzzer
	GPIO_InitStructure.GPIO_Pin = BUZZER_GPIO_PIN;
	//Choose Pin Buzzer as Out
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//Choose Speed Pin
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//Select type
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//Select status
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	//The function initializes all of the above values
	GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStructure);
}

/*
 * @func	Button_Init
 * @brief	Configure push buttons B2, B3, B4 with interrupt function
 * @param	None
 * retval	None
 * */
static void Button_Init(void) {
	/*B2*/
	//Enable Clock GPIO
	RCC_AHB1PeriphClockCmd(BUTTONB2_IT_SetClock, ENABLE);
	//Choose Pin Button b2
	GPIO_InitStructure.GPIO_Pin = BUTTONB2_IT_GPIO_PIN;
	//Choose Pin Button b2 as Input
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	//Choose Speed Pin
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//Select status
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	//The function initializes all of the above values
	GPIO_Init(BUTTONB2_IT_GPIO_PORT, &GPIO_InitStructure);

	/*B3*/
	//Initialize GPIO PB0 pin
	RCC_AHB1PeriphClockCmd(BUTTONB3_IT_SetClock, ENABLE);
	//Choose Pin Button B3
	GPIO_InitStructure.GPIO_Pin = BUTTONB3_IT_GPIO_PIN;
	//Choose Pin Button B3 as mode input
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	//Choose Speed Pin
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//Select status
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	//The function initializes all of the above values
	GPIO_Init(BUTTONB3_IT_GPIO_PORT, &GPIO_InitStructure);

	/*B4*/
	//Enable Clock GPIO
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//Choose Pin Button B4
	GPIO_InitStructure.GPIO_Pin = BUTTONB4_IT_GPIO_PIN;
	//Choose Pin Button B4 as mode Input
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	//Choose Speed Pin
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//Select status
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	//The function initializes all of the above values
	GPIO_Init(BUTTONB4_IT_GPIO_PORT, &GPIO_InitStructure);
}

/*
 * @func	LedControl_SetState
 * @brief	Led on/off control
 * @param	led_id: id of led want to control
 * 			led_state: LED on/off control status.
 * retval	None
 * */
static void LedControl_SetState(uint8_t led_id, uint8_t led_state) {
	//Set bit in BSRR Resgister
	if (led_state == GPIO_PIN_SET) {
		if (led_id == LED_BOARD_GPIO_PIN5) {
			(LED_BOARD_GPIO_PORT->BSRRL) |= 1 << LED_BOARD_GPIO_PIN5;
		} else if (led_id == LED_Green_1_PIN0) {
			(LED_Green_1_GPIO_PORT->BSRRL) |= 1 << LED_Green_1_PIN0;
		} else if (led_id == LED_Green_2_PIN11) {
			(LED_Green_2_GPIO_PORT->BSRRL) |= 1 << LED_Green_2_PIN11;
		} else if (led_id == LED_RED_1_GPIO_PIN13) {
			(LED_RED_1_GPIO_PORT->BSRRL) |= 1 << LED_RED_1_GPIO_PIN13;
		} else if (led_id == LED_RED_2_GPIO_PIN1) {
			(LED_RED_2_GPIO_PORT->BSRRL) |= 1 << LED_RED_2_GPIO_PIN1;
		} else if (led_id == LED_BLUE_1_GPIO_PIN10) {
			(LED_BLUE_1_GPIO_PORT->BSRRL) |= 1 << LED_BLUE_1_GPIO_PIN10;
		} else if (led_id == LED_BLUE_2_GPIO_PIN3) {
			(LED_BLUE_2_GPIO_PORT->BSRRL) |= 1 << LED_BLUE_2_GPIO_PIN3;
		}
	}
//Reset bit in BSRR Registers
	else if (led_state == GPIO_PIN_RESET) {
		if (led_id == LED_BOARD_GPIO_PIN5) {
			(LED_BOARD_GPIO_PORT->BSRRH) |= 1 << LED_BOARD_GPIO_PIN5;
		} else if (led_id == LED_Green_1_PIN0) {
			(LED_Green_1_GPIO_PORT->BSRRH) |= 1 << LED_Green_1_PIN0;
		} else if (led_id == LED_Green_2_PIN11) {
			(LED_Green_2_GPIO_PORT->BSRRH) |= 1 << LED_Green_2_PIN11;
		} else if (led_id == LED_RED_1_GPIO_PIN13) {
			(LED_RED_1_GPIO_PORT->BSRRH) |= 1 << LED_RED_1_GPIO_PIN13;
		} else if (led_id == LED_RED_2_GPIO_PIN1) {
			(LED_RED_2_GPIO_PORT->BSRRH) |= 1 << LED_RED_2_GPIO_PIN1;
		} else if (led_id == LED_BLUE_1_GPIO_PIN10) {
			(LED_BLUE_1_GPIO_PORT->BSRRH) |= 1 << LED_BLUE_1_GPIO_PIN10;
		} else if (led_id == LED_BLUE_2_GPIO_PIN3) {
			(LED_BLUE_2_GPIO_PORT->BSRRH) |= 1 << LED_BLUE_2_GPIO_PIN3;
		}
	}

}

/*
 * @func 	delay
 * @brief	Delay
 * @param	delay time
 * @retval  None
 * */
static
void delay(uint32_t ms) {
	uint32_t i, j;
	for (i = 0; i < ms; i++) {
		for (j = 0; j < 5000; j++) {
			;
		}
	}
}

/*
 * @func	BuzzerControl_SetBeep
 * @brief	Control buzzer
 * @param	None
 * retval	None
 * */
static void BuzzerControl_SetBeep(void) {
	uint8_t i;
	for (i = 0; i < 2; i++) {
		GPIO_SetBits(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN);
		delay(100);
		GPIO_ResetBits(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN);
		delay(100);
	}
}

/*
 * @func 	Blinkled_StatusPower
 * @brief	Blinked Led 4 times anouce MCU have power
 * @param	None
 * @retval	None
 * */
static void Blinkled_StatusPower(void) {
	uint8_t i;
	for (i = 0; i < 4; i++) {
		LedControl_SetState( LED_BOARD_GPIO_PIN5, GPIO_PIN_SET);
		delay(500);
		LedControl_SetState( LED_BOARD_GPIO_PIN5, GPIO_PIN_RESET);
		delay(500);
	}
}

/*
 * @func	CalculatorTime
 * @brief	Calculator Time press button
 * @param	dwTimeInit: Time start press button
 * 			dwTimeCurrent: Time current
 * retval	dwTimeTotal: Total time
 * */
uint32_t CalculatorTime(uint32_t dwTimeInit, uint32_t dwTimeCurrent) {
	uint32_t dwTimeTotal;

	if (dwTimeCurrent >= dwTimeInit) {
		dwTimeTotal = dwTimeCurrent - dwTimeInit;
	} else {
		dwTimeTotal = 0xFFFFFFFU + dwTimeCurrent - dwTimeInit;
	}
	return dwTimeTotal;
}

/*
 * @func	B3Interruppt_Init
 * @brief	Configure Interrupt for b3
 * @param	None
 * @retval	None
 * */
static void B3Interruppt_Init(void) {

	//Enable Clock Syscfg, Connect EXTI Line4 to PB4 pin
	RCC_APB2PeriphClockCmd(SYSCFG_Clock, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4);

	//Configure EXTI Line4
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	//Enable and set EXTI Line4 Interrupt to the lowest priority
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

/*
 * @func	B2Interruppt_Init
 * @brief	Configure Interrupt for b2
 * @param	None
 * @retval	None
 * */
void B2Interruppt_Init(void) {

	//Enable Clock Syscfg, Connect EXTI Line3 to PB3 pin
	RCC_APB2PeriphClockCmd(SYSCFG_Clock, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource3);
	//Configure EXTI Line3
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	//Enable and set EXTI Line3 Interrupt to the lowest priority
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

/*
 * @func	B4Interruppt_Init
 * @brief	Configure Interrupt for b4
 * @param	None
 * @retval	None
 * */
void B4Interruppt_Init(void) {

	//Enable Clock Syscfg, Connect EXTI Line0 to PB0 pin
	RCC_APB2PeriphClockCmd(SYSCFG_Clock, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0);

	//Configure EXTI Line0
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	//Enable and set EXTI Line0 Interrupt to the lowest priority
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*
 * @func	Interruppt_Init
 * @brief	Initialization Interrupt
 * @param	None
 * @retval	None
 * */
static void Interruppt_Init(void) {
	B2Interruppt_Init();
	B3Interruppt_Init();
	B4Interruppt_Init();
}

/*
 * @func	EXTI4_IRQHandler
 * @brief	Interrupt handler function for GPIO Pin 4(Button 3)
 * @param	None
 * @retval	None
 * */
void EXTI4_IRQHandler() {
	//If button b3 press
	if (GPIO_ReadInputDataBit(BUTTONB3_IT_GPIO_PORT, BUTTONB3_IT_GPIO_PIN)
			== 0) {
		//Nhấn nút
		pressTimeB3 = GetMilSecTick();	//Save press time
		releaseTimeB3 = 0;				//Delete release time
	}
	//If button b3 release
	else {
		releaseTimeB3 = GetMilSecTick();	//Save release time
		countB3++;							//Add press count
		pressTimeB3 = 0;					//Delete press time
	}

	//Clear bit PR Exit Interrupt
	EXTI_ClearITPendingBit(EXTI_Line4);
}

/*
 * @func	EXTI3_IRQHandler
 * @brief	Interrupt handler function for GPIO Pin 3(Button 2)
 * @param	None
 * @retval	None
 * */
void EXTI3_IRQHandler() {
	//If button b2 press
	if (GPIO_ReadInputDataBit(BUTTONB2_IT_GPIO_PORT, BUTTONB2_IT_GPIO_PIN)
			== 0) {
		pressTimeB2 = GetMilSecTick();		//Save press time
		releaseTimeB2 = 0;					//Delete release time
	}
	//If button b3 release
	else {
		releaseTimeB2 = GetMilSecTick();	//Save release time
		countB2++;							//Add press count
		pressTimeB2 = 0;					//Delete press time
	}
	//Clear bit PR Exit Interrupt
	EXTI_ClearITPendingBit(EXTI_Line3);
}

/*
 * @func	EXTI0_IRQHandler
 * @brief	Interrupt handler function for GPIO Pin 0(Button 4)
 * @param	None
 * @retval	None
 * */
void EXTI0_IRQHandler() {
	//If button b4 press
	if (GPIO_ReadInputDataBit(BUTTONB4_IT_GPIO_PORT, BUTTONB4_IT_GPIO_PIN)
			== 0) {
		pressTimeB4 = GetMilSecTick();		//Save press time
		releaseTimeB4 = 0;					//Delete release time
	} else {
		releaseTimeB4 = GetMilSecTick();	//Save release time
		countB4++;							//Add press count
		pressTimeB4 = 0;					//Delete press time
	}
	//Clear bit PR Exit Interrupt
	EXTI_ClearITPendingBit(EXTI_Line0);
}

/*
 * @func	Button3_Scan
 * @brief	Event handler function when interrupt occurs on Button 3
 * @param	None
 * @retval	None
 * */
void Button3_Scan() {
	//If release time b3 >500ms
	if (releaseTimeB3 != 0
			&& CalculatorTime(releaseTimeB3, GetMilSecTick()) > 500) {
		// If button press 5 times
		if (countB3 == 5) {
			BuzzerControl_SetBeep();
			uint8_t i = 0;
			for (; i < 5; i++) {
				LedControl_SetState( LED_Green_1_PIN0,
				GPIO_PIN_SET);
				LedControl_SetState( LED_Green_2_PIN11,
				GPIO_PIN_SET);
				delay(500);
				LedControl_SetState( LED_Green_1_PIN0,
				GPIO_PIN_RESET);
				LedControl_SetState( LED_Green_2_PIN11,
				GPIO_PIN_RESET);
				delay(500);
			}
		}
		countB3 = 0;			//Reset press count b3
		releaseTimeB3 = 0;		//Reset release time b3
	}
}

/*
 * @func	Button2_Scan
 * @brief	Event handler function when interrupt occurs on Button 2
 * @param	None
 * @retval	None
 * */
void Button2_Scan(void) {
	// If button b2 press
	if (pressTimeB2 != 0) {
		uint32_t durationTime = CalculatorTime(pressTimeB2, GetMilSecTick());
		// Hold button > 500 ms turn on Led Blue
		if (durationTime > 500) {
			LedControl_SetState( LED_BLUE_1_GPIO_PIN10, GPIO_PIN_SET);
			LedControl_SetState( LED_BLUE_2_GPIO_PIN3, GPIO_PIN_SET);
		}
	}
	// Release button B2 turn off Led Blue
	else if (releaseTimeB2 != 0
			&& CalculatorTime(releaseTimeB2, GetMilSecTick()) > 400) {
		// If button B2 press count = 1 turn off Led Blue
		if (countB2 == 1) {
			LedControl_SetState( LED_BLUE_1_GPIO_PIN10, GPIO_PIN_RESET);
			LedControl_SetState( LED_BLUE_2_GPIO_PIN3, GPIO_PIN_RESET);
		}
		//  If button B2 press 2 time turn on Led Blue
		else if (countB2 == 2) {
			LedControl_SetState( LED_BLUE_1_GPIO_PIN10, GPIO_PIN_SET);
			LedControl_SetState( LED_BLUE_2_GPIO_PIN3, GPIO_PIN_SET);
		}
		countB2 = 0;		//Reset press count b2
		releaseTimeB2 = 0;	//Reset release time b2
	}
}

/*
 * @func	Button4_Scan
 * @brief	Event handler function when interrupt occurs on Button 4
 * @param	None
 * @retval	None
 * */
void Button4_Scan(void) {
	// If button b4 press
	if (pressTimeB4 != 0) {
		uint32_t durationTime = CalculatorTime(pressTimeB4, GetMilSecTick());
		//Hold button > 500 ms turn on Led Red
		if (durationTime > 500) {
			LedControl_SetState( LED_RED_1_GPIO_PIN13, GPIO_PIN_SET);
			LedControl_SetState( LED_RED_2_GPIO_PIN1, GPIO_PIN_SET);
		}
	}
	// Release button B2 turn off Led RED
	if (releaseTimeB4 != 0
			&& CalculatorTime(releaseTimeB4, GetMilSecTick()) > 500) {
		// If button B4 press count = 1 turn off Led Red
		if (countB4 == 1
				&& CalculatorTime(releaseTimeB4, GetMilSecTick()) > 500) {
			LedControl_SetState( LED_RED_1_GPIO_PIN13, GPIO_PIN_RESET);
			LedControl_SetState( LED_RED_2_GPIO_PIN1, GPIO_PIN_RESET);
		}
		// If button B4 press count = 2 turn on Led Red
		else if (countB4 == 2) {
			LedControl_SetState( LED_RED_1_GPIO_PIN13, GPIO_PIN_SET);
			LedControl_SetState( LED_RED_2_GPIO_PIN1, GPIO_PIN_SET);
		}
		countB4 = 0;			//Reset press count b4
		releaseTimeB4 = 0;		//Reset release time b4
	}
}

/*
 * @func	AppInit
 * @brief	Initialization function
 * @param	None
 * @retval	None
 * */
void AppInit(void) {
	SystemCoreClockUpdate();
	TimerInit();
	LedBuzz_Init();
	Button_Init();
	Interruppt_Init();
}
/*
 * @func 	main
 * @brief
 * */
int main(void) {

	AppInit();
	Blinkled_StatusPower();

	/* Loop forever */
	while (1) {
		Button3_Scan();
		Button2_Scan();
		Button4_Scan();
	}
}

