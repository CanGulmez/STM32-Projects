/* PWM Signals Generating */

#include "pwm_signals.h"

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

/** Initialization GPIOA Peripheral 
 * 
 * Set the PA5 pin as alternate. Because of channel 
 * selection of timer which is in output compare mode, 
 * I'm configuring PA5 pin acting like TIM2_CH1.
 */
void Initialize_GPIOA(void) {

   // Enable the GPIOA peripheral.
   __HAL_RCC_GPIOA_CLK_ENABLE();

   igpio.Mode = GPIO_MODE_AF_PP;
   igpio.Pin = GPIO_PIN_5;
   igpio.Pull = GPIO_NOPULL;
   igpio.Speed = GPIO_SPEED_FREQ_LOW;
   igpio.Alternate = GPIO_AF1_TIM2;
   HAL_GPIO_Init(GPIOA, &igpio);
}

/** Initialize TIM2 Peripheral
 * 
 * Initialize TIM2 as output compare mode to control LED
 * brightness using PWM. I 've decided 1s period of the
 * signals. The most important thing is to detername duty
 * cycle rate. For this project, I selected 40% rate. 
 */
void Initialize_TIM2(void) {

   // Enable the TIM2 peripheral.
   __HAL_RCC_TIM2_CLK_ENABLE();

   htim.Instance = TIM2;
   htim.Init.CounterMode = TIM_COUNTERMODE_UP;
   htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
   htim.Init.Period = 10000 - 1;
   htim.Init.Prescaler = 4800 - 1; 
   HAL_TIM_PWM_Init(&htim); 
   
   ioc.OCMode = TIM_OCMODE_PWM1;
   ioc.OCPolarity = TIM_OCPOLARITY_HIGH;
   ioc.Pulse = (htim.Init.Period * 40) / 100; // 40% duty
   HAL_TIM_PWM_ConfigChannel(&htim, &ioc, TIM_CHANNEL_1);
}
