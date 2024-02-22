/* LED Blinking using Basic Timer */

#include "led_blinking.h"

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
 * Just initialize the GPIO pins to toggle LED. That LED
 * can be anywhere on microcontroller. I selected the pin 
 * randomly. So, change the pin due to your project.
 */
void Initialize_GPIOA(void) {

   // Enable the GOIOA peripheral clock.
   __HAL_RCC_GPIOA_CLK_ENABLE();

   // Initialize the GPIOA peripheral.
   igpio.Mode = GPIO_MODE_AF_PP;
   igpio.Pull = GPIO_NOPULL;
   igpio.Speed = GPIO_SPEED_FREQ_LOW;
   igpio.Pin = GPIO_PIN_1;
   HAL_GPIO_Init(GPIOA, &igpio);
}

/** TIM7 Peripheral Initialization 
 * 
 * Intialize the TIM7 peripheral to update each event in 1 
 * seconds. So, parameters of peripheral was selected due to 
 * it. General formula to determine update event is 
 * 
 * UpdateEvent = TimerClk / (Prescaler + 1) * (Period + 1)
 * 
 * This formula gives us the frequency which is updated.
 * So (1 / UpdateEvent) gives us the elapsed time.
 */
void Initialize_TIM7(void) {

   // Enable the TIM6 clock.
   __HAL_RCC_TIM7_CLK_ENABLE();

   htim.Instance = TIM7;
   htim.Init.CounterMode = TIM_COUNTERMODE_UP;
   htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
   htim.Init.Prescaler = 48000 - 1; // 48MHz/48000 = 1KHz
   htim.Init.Period = 1000 - 1;     // 1KHz/1000 = 1s
   HAL_TIM_Base_Init(&htim);

   // Enable the interrupt mode.
   HAL_NVIC_SetPriority(TIM7_IRQn, 0, 0);
   HAL_NVIC_EnableIRQ(TIM7_IRQn);
}

