/** Data Transceiver via SPI Interface 
 * 
 * Data transciever is one of the most required skill in 
 * digital or analog systems. So, There are the a lot of
 * serial communication protocols like I2C, SPI, CAN, etc.
 * In this project, I focused the SPI interface with 
 * master and slave modes. I hope it will be useful...  
 */

#ifndef TRANSCEIVER_SPI_H
#define TRANSCEIVER_SPI_H

// Standard librries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// STM32Cube libraries
#include <stm32f4xx_hal.h>

// Master or Slave?
#define MASTER  1
#define SLAVE   0

// User-defined structures
RCC_OscInitTypeDef iosc;
RCC_ClkInitTypeDef iclk;
GPIO_InitTypeDef igpio;
SPI_HandleTypeDef hspi;

// Function prototypes
void SystemClockConfig(void);
void Initialize_GPIOA(void);
void Initialize_SPI1(void);

#endif /* TRANSCEIVER_SPI_H */
