/* Square Wave Producing using Timer */

#ifndef SQUARE_WAVE_PRODUCING_H
#define SQUARE_WAVE_PRODUCING_H

// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// STM32Cube firmware
#include <stm32f4xx_hal.h>

// User-defined structures
RCC_OscInitTypeDef iosc;
RCC_ClkInitTypeDef iclk;
GPIO_InitTypeDef igpio;
TIM_HandleTypeDef htim;
TIM_OC_InitTypeDef ioc;

// Function prototypes
void SystemClockConfig(void);
void Initialize_GPIOA(void);
void Initialize_TIM2(void);
void TIM2_IRQHandler(void);
void HAL_TIM_OC_DelayElapsedCallback(
   TIM_HandleTypeDef *htim
);

#endif /* SQUARE_WAVE_PRODUCING_H */
