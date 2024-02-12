/** Data Transceiver via I2C Interface 
 * 
 * Data transciever is one of the most required skill in 
 * digital or analog systems. So, There are the a lot of
 * serial communication protocols like I2C, SPI, CAN, 
 * UART/USART, etc. In this project, I focused the I2C 
 * interface. I hope it will be useful...
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
 * We must select the GPIO pins to transmit/receive data via I2C.
 * That pins can be selected by looking for datasheet of MCU. For 
 * me, I chose the belong pins as alteranate to our purpose:
 * 
 * PB6  --> I2C1_SCL
 * PB7  --> I2C1_SDL
 * AF04 --> I2C1
 */
void Initialize_GPIOA(void) {

   // Enable the GOIOA peripheral clock.
   __HAL_RCC_GPIOB_CLK_ENABLE();

   // Initialize the GPIOA peripheral.
   igpio.Mode = GPIO_MODE_AF_OD;
   igpio.Pin = GPIO_PIN_6 | GPIO_PIN_7; 
   igpio.Pull = GPIO_PULLUP;  // required external resistor/s
   igpio.Speed = GPIO_SPEED_FREQ_LOW;
   igpio.Alternate = GPIO_AF4_I2C1;
   HAL_GPIO_Init(GPIOB, &igpio);
}

/* I2C1 Peripheral Initialization */
void Initialize_I2C1(void) {

   // Enable the I2C1 peripheral.
   __HAL_RCC_I2C1_CLK_ENABLE();

   // Initialize the I2C1 peripheral
   hi2c.Instance = I2C1;
   hi2c.Init.ClockSpeed = 100000; // 100KHz
   hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT; // 7 bit address
   hi2c.Init.OwnAddress1 = 0x0; // primary device address in slave mode
   hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2; // not required
   hi2c.Init.OwnAddress2 = 0; // not required
   hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
   hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
   hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
   HAL_I2C_Init(&hi2c);
}
