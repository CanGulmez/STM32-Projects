/* Temperature Measurement with Internal Sensor */

#include "temperature.h"

void main(int argc, char *argv[]) {

   // Configure the lowest settings.
   HAL_Init();

   // Configure the system clock.
   SystemClockConfig();

   // Initialize the peripherals.
   Initialize_ADC1();

   HAL_ADC_Start(&hadc);

   while (1) {

      HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);

      uint16_t rawValue = HAL_ADC_GetValue(&hadc);
      float temp = ((float) rawValue) / 4095 * 3300;
      temp = ((temp - 760.0) / 2.5) + 25;

      printf("Raw value: %d\n\n", rawValue);
      printf("Temperature: %f\r\n", temp);
   }
} 
