/** INSULATION MONITORING DEVICE - FIRMWARE DEVELOPMENT
 *   
 * Insulation monitoring device is a device which monitor the 
 * insulation resistance level in the high-voltage required systems. 
 * If measured resistance level is the low (according to desired 
 * referance resistance), and the this monitoring system triggers 
 * the alarm (buzzer).
 */

#include "insulation_monitoring.h"

/** System Clock Configuration
 * 
 * Oscillator: HSE - 25MHz
 * Clock     : All Clocks Types
 * PLL State : Active
 * AHB       : 96MHz
 * APB1      : 48MHz
 * APB2      : 48MHz
 */
void SystemClock_Config(void) {

   // Adjust the oscillator settings.
   init_osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
   init_osc.HSEState = RCC_HSE_ON;
   init_osc.PLL.PLLState = RCC_PLL_ON;
   init_osc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
   init_osc.PLL.PLLM = 25;
   init_osc.PLL.PLLN = 192;
   init_osc.PLL.PLLP = 2; 
   HAL_RCC_OscConfig(&init_osc);

   // Adjust the clock settings.
   init_clk.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                        RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
   init_clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   init_clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
   init_clk.APB1CLKDivider = RCC_HCLK_DIV2;
   init_clk.APB2CLKDivider = RCC_HCLK_DIV2;
   HAL_RCC_ClockConfig(&init_clk, FLASH_LATENCY_3);

   HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
   HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}

/** ADC1 Peripheral Initialization
 * 
 * This peripheral is used to convert analog inputs into
 * digital digits. I want to plan that the frequency of this
 * peripheral will be 48MHz. The mode of this peripheral will 
 * be single-channel continuous which means continuously 
 * and indefinitely sampling.
 */
void Initialize_ADC1(void) {

   // Enable the ADC1 peripheral.
   __HAL_RCC_ADC1_CLK_ENABLE();

   // Adjust the ADC1 perpheral settings.
   handle_adc.Instance = ADC1;
   handle_adc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
   handle_adc.Init.Resolution = ADC_RESOLUTION_12B;
   handle_adc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
   handle_adc.Init.ContinuousConvMode = ENABLE;    
   handle_adc.Init.ScanConvMode = DISABLE;        
   handle_adc.Init.NbrOfConversion = 1;
   handle_adc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
   HAL_ADC_Init(&handle_adc);

   // Configure the selected ADC1 channel and ranks.
   conf_channel_adc.Channel = ADC_CHANNEL_0;
   conf_channel_adc.Rank = 1;
   conf_channel_adc.Offset = 0;
   conf_channel_adc.SamplingTime = ADC_SAMPLETIME_480CYCLES;
   HAL_ADC_ConfigChannel(&handle_adc, &conf_channel_adc);
}

/** GPIOA Port Initialization for Buzzer 
 *  
 * Initialize the GPIOA port. When the system gets wrong, 
 * this function will be useful to toggle buzzer to inform
 * the users.
 */
void Initialize_GPIOA(void) {

   // Enable the GPIOA port.
   __HAL_RCC_GPIOA_CLK_ENABLE();

   // Initiliaze the GPIOA port.
   init_gpio.Mode = GPIO_MODE_OUTPUT_PP;
   init_gpio.Pin = GPIO_PIN_1;
   init_gpio.Pull = GPIO_NOPULL;
   init_gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
   HAL_GPIO_Init(GPIOA, &init_gpio);
}

/** Calculate the R Value
 * 
 * Calculate the R value from ADC inputs. This function
 * give us the necessary value that will be mesuared 
 * insulation resistance.
 */
int Calculate_R_Value(int value) {

   // This implementation is hardware-specified.So I 
   // don't implement and convension algorithm now. 
   return value;
}
