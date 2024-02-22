/* Temperature Measurement with Internal Sensor */

#ifndef TEMPERATURE_MEASUREMENT_H
#define TEMPERATURE_MEASUREMENT_H

// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

// STM32Cube firmware
#include <stm32f4xx_hal.h>

// User-defined structures
RCC_OscInitTypeDef iosc;
RCC_ClkInitTypeDef iclk;
ADC_HandleTypeDef hadc;
ADC_ChannelConfTypeDef cadc;

// Function prototypes
void SystemClockConfig(void);
void Initialize_ADC1(void);

#endif /* TEMPERATURE_MEASUREMENT_H */