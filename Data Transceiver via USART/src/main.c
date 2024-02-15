/** Data Transceiver via UART/USART 
 *  
 * Data transciever is one of the most required skill in 
 * digital or analog systems. So, There are the a lot of
 * serial communication protocols like I2C, SPI, UART/USART.
 * In this firmware, I focused the UART interface to aim
 * transmission and reception. I hope it will be useful...  
 */

#define AUTHOR    "Ahmet Can Gulmez"
#define EMAIL     "ahmetcangulmez02@gmail.com"
#define VERSION   1.0
#define LICENSE   "GNU GPLv3"

#include "transceiver.h"

void main(int argc, char *argv[]) {

   // Initialize low-level settings.
   HAL_Init();

   // Adjust the oscillator and clock.
   SystemClockConfig();

   // Initialize the peripherals.
   Initialize_GPIOA();
   Initialize_UART2();

   // Buffers to send and receive.
   char tbuffer[] = "STM32 is amazing!";
   char rbuffer[32];

   // Transmit and receive buffers in polling mode.
   HAL_UART_Transmit(&huart, 
                     (uint8_t*) tbuffer, 
                     strlen(tbuffer)+1, 
                     HAL_MAX_DELAY);

   HAL_Delay(100); // give the 0.1 seconds.

   HAL_UART_Receive(&huart, 
                    (uint8_t*) rbuffer, 
                    strlen(rbuffer)+1, 
                    HAL_MAX_DELAY);

   // If transmitted and received buffers are same,
   // and then blink the LED of microcontroller.
   if (!strcmp(tbuffer, rbuffer))
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

   while (1);
}
