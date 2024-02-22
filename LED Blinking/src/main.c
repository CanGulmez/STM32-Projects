/* LED Blinking using Basic Timer */

#include "led_blinking.h"

void main(int argc, char *argv[]) {

   // Initialize the low-level settings.
   HAL_Init();

   // Initialize the peripherals.
   Initialize_GPIOA();
   Initialize_TIM7();

   // Start the timer in IT mode.
   HAL_TIM_Base_Start_IT(&htim);

   while (1);
}

void TIM7_IRQHandler(void) {
   // Pass the control to HAL, which processes the IRQ.
   HAL_TIM_IRQHandler(&htim);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
   // This callback is automatically called by the HAL.
   if (htim->Instance == TIM7)
      HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
}
