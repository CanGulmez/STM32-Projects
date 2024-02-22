/* Square Wave Producing using Timer  */

#include "square_wave.h"

void main(int argc, char *argv[]) {

   // Initialize the low-level settings.
   HAL_Init();

   // Initialize the peripherals.
   Initialize_GPIOA();
   Initialize_TIM2();

   // Start the timer in output compare mode.
   HAL_TIM_OC_Start_IT(&htim, TIM_CHANNEL_1);

   while (1);
}
