/** Data Transceiver via SPI Interface 
 * 
 * Data transciever is one of the most required skill in 
 * digital or analog systems. So, There are the a lot of
 * serial communication protocols like I2C, SPI, CAN, etc.
 * In this project, I focused the SPI interface with 
 * master and slave modes. I hope it will be useful...  
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
 * We must select the GPIO pins to transmit/receive data via SPI.
 * That pins can be selected by looking for datasheet of MCU. For 
 * me, I chose the belong pins as alteranate to our purpose:
 * 
 * PA7  --> SPI1_MOSI
 * PA6  --> SPI1_MISO
 * PA4  --> SPI1_NSS
 * PA5  --> SPI1_CLK
 * AF05 --> SPI1
 */
void Initialize_GPIOA(void) {

   // Enable the GOIOA peripheral clock.
   __HAL_RCC_GPIOA_CLK_ENABLE();

   // Initialize the GPIOA peripheral.
   igpio.Mode = GPIO_MODE_AF_PP;
   igpio.Pull = GPIO_NOPULL;
   igpio.Speed = GPIO_SPEED_FREQ_LOW;
   igpio.Alternate = GPIO_AF5_SPI1;

   igpio.Pin = GPIO_PIN_4;       // SPI1_NSS
   HAL_GPIO_Init(GPIOA, &igpio);

   igpio.Pin = GPIO_PIN_5;       // SPI1_CLK
   HAL_GPIO_Init(GPIOA, &igpio);

   igpio.Pin = GPIO_PIN_6;       // SPI1_MISO
   HAL_GPIO_Init(GPIOA, &igpio);

   igpio.Pin = GPIO_PIN_7;       // SPI1_MOSI
   HAL_GPIO_Init(GPIOA, &igpio);
}

/** SPI1 Peripheral Initialization 
 * 
 * Initialize the SP1 peripheral to transmit/receive data.
 * I'll explain the each entity of SPI1 handler. Of course
 * You can set the each entity according to your project.
 */
void Initialize_SPI1(void) {

   // Enable the SPI1 peripheral.
   __HAL_RCC_SPI1_CLK_ENABLE();

   // Initialize the SPI1 peripheral.
   hspi.Instance = SPI1;

   #if (MASTER == 1)
      hspi.Init.Mode = SPI_MODE_MASTER;  // master mode
   #else
      hspi.Init.Mode = SPI_MODE_SLAVE;  // slave mode
   #endif

   hspi.Init.Direction = SPI_DIRECTION_2LINES;  // full-duplex 
   hspi.Init.DataSize = SPI_DATASIZE_8BIT;  // 8 bits for each bytes
   hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;  // 6MHz for APB2
   hspi.Init.CLKPhase = SPI_PHASE_1EDGE;  // first edge triggering
   hspi.Init.CLKPolarity = SPI_POLARITY_LOW;  // rising edge triggering
   hspi.Init.NSS = SPI_NSS_SOFT;  // soft slave selection
   hspi.Init.TIMode = SPI_TIMODE_DISABLE;
   hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;  // most significant bit
   hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;  // disable CRC
   HAL_SPI_Init(&hspi);
}

