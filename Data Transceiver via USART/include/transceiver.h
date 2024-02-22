/** Data Transceiver via UART/USART Interface
 *  
 * Data transciever is one of the most required skill in 
 * digital or analog systems. So, There are the a lot of
 * serial communication protocols like I2C, SPI, UART/USART.
 * In this firmware, I focused the UART interface to aim
 * transmission and reception. I hope it will be useful...  
 */

#ifndef UART_USART_TRANSCEIVER_H
#define UART_USART_TRANSCEIVER_H

// Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Include STM32Cube libraries
#include <stm32f4xx_hal.h>

// User-defined structs
RCC_OscInitTypeDef iosc;
RCC_ClkInitTypeDef iclk;
GPIO_InitTypeDef igpio;
UART_HandleTypeDef huart;

// Function prototypes
void SystemClockConfig(void);
void Initialize_GPIOA(void);
void Initialize_UART2(void);

#endif /* UART_USART_TRANSCEIVER_H */
