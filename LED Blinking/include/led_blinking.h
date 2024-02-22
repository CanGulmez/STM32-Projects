/* LED Blinking using Basic Timer */

#ifndef LED_BLINKING_H
#define LED_BLINKING_H

// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// stm32cube libraries
#include <stm32f4xx_hal.h>

// User-defined structures
RCC_OscInitTypeDef iosc;
RCC_ClkInitTypeDef iclk;
GPIO_InitTypeDef igpio;
TIM_HandleTypeDef htim;

// Function prototypes
void SystemClockConfig(void);
void Initialize_GPIOA(void);
void Initialize_TIM7(void);
void TIM7_IRQHandler(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* LED_BLINKING_H */
