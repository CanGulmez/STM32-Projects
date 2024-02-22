/* Square Wave Producing using Timer */

#include "square_wave.h"

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
 * Initialize TIM2 as output compare mode. This step
 * aims to configure the output channel frewuency as
 * 1KHz or 0.001s. To configure the frequency, that
 * fourmula is used:
 * 
 * ChannelFreq = TimFreq / Pulse
 * 
 * Just select the 'Pulse' attribute as your requests.
 */
void Initialize_TIM2(void) {

   // Enable the TIM2 peripheral.
   __HAL_RCC_TIM2_CLK_ENABLE();

   htim.Instance = TIM2;
   htim.Init.CounterMode = TIM_COUNTERMODE_UP;
   htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
   htim.Init.Period = 0xFFFFFFFF;
   htim.Init.Prescaler = 1;  // 24MHz
   HAL_TIM_OC_Init(&htim);
   
   ioc.OCMode = TIM_OCMODE_TOGGLE;
   ioc.OCPolarity = TIM_OCPOLARITY_HIGH;
   ioc.Pulse = 24000; // 1KHz = 0.001s 
   HAL_TIM_OC_ConfigChannel(&htim, &ioc, TIM_CHANNEL_1);

   // Can be selected another channels of course.
   // HAL_TIM_OC_ConfigChannel(&htim, &ioc, TIM_CHANNEL_2);

   // Enable the interrupt (non-blocking) mode.
   HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
   HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

/** IRQ Handler
 * 
 * This firmware is run in interrupt mode. So, 
 * I'm developing the IRQ Handler function. 
 */
void TIM2_IRQHandler(void) {
   HAL_TIM_IRQHandler(&htim);
}

/** Timer Callback 
 * 
 * As above mentioned. To run in interrupt mode, 
 * another implementation is callback function.
*/
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {
   // TIM2_CH1 toggling with frequency 1KHz.
   uint16_t content; 
   if (htim->Channel == TIM_CHANNEL_1) {
      content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
      __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, (content + 24000));
   }
}
