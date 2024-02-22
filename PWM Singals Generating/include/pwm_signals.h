/* PWM Signals Generating */

#ifndef PWM_SIGNALS_H
#define PWM_SIGNALS_H

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

#endif /* PWM_SIGNALS_H */