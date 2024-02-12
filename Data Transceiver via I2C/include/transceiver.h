/** Data Transceiver via I2C Interface 
 * 
 * Data transciever is one of the most required skill in 
 * digital or analog systems. So, There are the a lot of
 * serial communication protocols like I2C, SPI, CAN, 
 * UART/USART, etc. In this project, I focused the I2C 
 * interface. I hope it will be useful...
 */

#ifndef TRANSCEIVER_I2C_H
#define TRANSCEIVER_I2C_H

// Standard librries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// STM32Cube libraries
#include <stm32f4xx_hal.h>

// User-defined structures
RCC_OscInitTypeDef iosc;
RCC_ClkInitTypeDef iclk;
GPIO_InitTypeDef igpio;
I2C_HandleTypeDef hi2c;

// Function prototypes
void SystemClockConfig(void);
void Initialize_GPIOA(void);
void Initialize_I2C1(void);

#endif /* TRANSCEIVER_I2C_H */
