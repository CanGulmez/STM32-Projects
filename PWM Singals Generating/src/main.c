/* PWM Signals Generating */

#include "pwm_signals.h"

void main(int argc, char *argv[]) {

   // Initialize the low-level settings.
   HAL_Init();

   // Initialize the peripherals.
   Initialize_GPIOA();
   Initialize_TIM2();

   // Start the timer in output compare mode.
   HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1);

   while (1);
}
