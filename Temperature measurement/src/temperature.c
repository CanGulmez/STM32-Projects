/* Temperature Measurement with Internal Sensor */

#include "temperature.h"

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

/** Initialization of ADC1 Peripheral 
 * 
 * Initialize the ADC1 peripheral to measure the temperature. 
 * Note that any external sensor is not required. STM32 has itsef
 * internal temperature sensor. So, just I use that sensor. 
 */
void Initialize_ADC1(void) {

   // Enable the ADC1 peripheral.
   __HAL_RCC_ADC1_CLK_ENABLE();

   // Configure the global features of the ADC1.
   hadc.Instance = ADC1;
   hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2; // 24MHz
   hadc.Init.Resolution = ADC_RESOLUTION_12B;
   hadc.Init.ContinuousConvMode = ENABLE;
   hadc.Init.ScanConvMode = DISABLE;
   hadc.Init.DiscontinuousConvMode = DISABLE;
   hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
   hadc.Init.NbrOfConversion = 1;
   hadc.Init.DMAContinuousRequests = DISABLE;
   hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
   HAL_ADC_Init(&hadc);

   // Configure for the selected ADC regular channel.
   cadc.Channel = ADC_CHANNEL_TEMPSENSOR;
   cadc.Rank = 1;
   cadc.SamplingTime = ADC_SAMPLETIME_480CYCLES;
   HAL_ADC_ConfigChannel(&hadc, &cadc);
}
