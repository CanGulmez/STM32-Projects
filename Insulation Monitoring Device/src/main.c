/** INSULATION MONITORING DEVICE - FIRMWARE DEVELOPMENT
 *   
 * Insulation monitoring device is a device which monitor the 
 * insulation resistance level in the high-voltage required systems. 
 * If measured resistance level is the low (according to desired 
 * referance resistance), and the this monitoring system triggers 
 * the alarm (buzzer).
 */

#define AUTHOR    "Ahmet Can GULMEZ"
#define EMAIL     "ahmetcangulmez02@gmail.com"
#define LICENSE   "MIT License"
#define VERSION   1.0

#include "insulation_monitoring.h"

int main(int argc, char **argv) {

   #ifdef INSULTION_MONITORING_H
   
      // Initialize and configurate the necassary settings.
      HAL_Init();
      SystemClock_Config();
      Initialize_ADC1();
      Initialize_GPIOA();

      // Start the ADC1 periheral.
      HAL_ADC_Start(&handle_adc);
      
      // Continuously, get the ADC1 readings.
      while (1) {

         // Let the ADC1 peripheral set the convention.
         HAL_ADC_PollForConversion(&handle_adc, HAL_MAX_DELAY);

         // Get the raw value from the ADC1 peripheral.
         int rawValue = HAL_ADC_GetValue(&handle_adc);
         // Convert the 'rawValue' to R resistance.
         int resistance = Calculate_R_Value(rawValue);

         // Referance value to compare the 'R'. This is a 
         // specific value that can be set by hardware design.
         int RefR = 1;

         if (resistance > RefR && resistance < RefR) {
            // Enable the buzzer and break up the loop.
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, SET);
            break;
         }
         // Give the 200 microseconds in each iteration.
         HAL_Delay(200);
      }

   #endif /* INSULATION_MONITORING_H */
}
