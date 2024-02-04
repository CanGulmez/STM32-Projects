/** INSULATION MONITORING DEVICE - FIRMWARE DEVELOPMENT
 *   
 * Insulation monitoring device is a device which monitor the 
 * insulation resistance level in the high-voltage required systems. 
 * If measured resistance level is the low (according to desired 
 * referance resistance), and the this monitoring system triggers 
 * the alarm (buzzer).
 */

#ifndef INSULTION_MONITORING_H
#define INSULTION_MONITORING_H

// Include libraries:
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#include <stm32f4xx_hal.h>

// Declare the user-defined structs.
RCC_OscInitTypeDef init_osc;
RCC_ClkInitTypeDef init_clk;
ADC_HandleTypeDef handle_adc;
ADC_ChannelConfTypeDef conf_channel_adc;
GPIO_InitTypeDef init_gpio;

// Declare the function prototypes:
void SystemClock_Config(void);
void Initialize_ADC1(void);
void Initialize_GPIOA(void);
int Calculate_R_Value(int value);

#endif /* INSULATION_MONITORING_H */
