/** Data Transceiver via UART/USART 
 *  
 * Data transciever is one of the most required skill in 
 * digital or analog systems. So, There are the a lot of
 * serial communication protocols like I2C, SPI, UART/USART.
 * In this firmware, I focused the UART interface to aim
 * transmission and reception. I hope it will be useful...  
 */

#include "transceiver.h"

/** System Clock Configuration
 * 
 * Oscillator: HSE - 25MHz
 * Clock     : All Clocks Types
 * PLL State : Active
 * AHB       : 96MHz
 * APB1      : 48MHz
 * APB2      : 48MHz
 */
void SystemClockConfig(void) {

   // Adjust the oscillator settings.
   iosc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
   iosc.HSEState = RCC_HSE_ON;
   iosc.PLL.PLLState = RCC_PLL_ON;
   iosc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
   iosc.PLL.PLLM = 25;
   iosc.PLL.PLLN = 192;
   iosc.PLL.PLLP = 2; 
   HAL_RCC_OscConfig(&iosc);

   // Adjust the clock settings.
   iclk.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                    RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
   iclk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   iclk.AHBCLKDivider = RCC_SYSCLK_DIV1;
   iclk.APB1CLKDivider = RCC_HCLK_DIV2;
   iclk.APB2CLKDivider = RCC_HCLK_DIV2;
   HAL_RCC_ClockConfig(&iclk, FLASH_LATENCY_3);

   HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
   HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}

/** GPIOA Peripheral Initialization 
 * 
 * We must select the GPIO pins to transmit/receive data via UART.
 * That pins can be selected by looking for datasheet of MCU. For 
 * me, I chose the belong pins as alteranate to our purpose:
 * 
 * PA2  --> USART2_TX
 * PA3  --> USART2_RX
 * PA4  --> USART2_CK
 * AF07 --> USART2
 */
void Initialize_GPIOA(void) {

   // Enable the GOIOA peripheral clock.
   __HAL_RCC_GPIOA_CLK_ENABLE();

   // Initialize the GPIOA peripheral.
   igpio.Mode = GPIO_MODE_AF_PP;
   igpio.Pull = GPIO_NOPULL;
   igpio.Speed = GPIO_SPEED_FREQ_LOW;
   igpio.Alternate = GPIO_AF7_USART2;

   igpio.Pin = GPIO_PIN_2;       // USART2_TX
   HAL_GPIO_Init(GPIOA, &igpio);

   igpio.Pin = GPIO_PIN_3;       // USART2_RX
   HAL_GPIO_Init(GPIOA, &igpio);

   // igpio.Pin = GPIO_PIN_4;       // USART2_CK
   // HAL_GPIO_Init(GPIOA, &igpio);
}

/** USART2 Peripheral Initialization 
 * 
 * Initialize the USART peripheral to transmit/receive data.
 * I'll explain the each entity of USART2 handler. Of course
 * You can set the each entity according to your project.
 */
void Initialize_UART2(void) {

   // Enable the clock of peripheral.
   __HAL_RCC_USART2_CLK_ENABLE();

   // Initialize the USART2 peripheral.
   huart.Instance = USART2;
   huart.Init.Mode = UART_MODE_TX_RX;  // transceiver
   huart.Init.BaudRate = 38400;        // bits per seconds
   huart.Init.WordLength = UART_WORDLENGTH_8B; // 8 bits word lenght
   huart.Init.StopBits = UART_STOPBITS_1;  // 1 bit to stop
   huart.Init.OverSampling = UART_OVERSAMPLING_16; // 16 bit sampling
   huart.Init.Parity = UART_PARITY_NONE;   // none parity bit
   huart.Init.HwFlowCtl = UART_HWCONTROL_NONE; // none hardware control
   HAL_UART_Init(&huart);
}
