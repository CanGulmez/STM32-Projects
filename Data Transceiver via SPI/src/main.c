/** Data Transceiver via SPI Interface 
 * 
 * Data transciever is one of the most required skill in 
 * digital or analog systems. So, There are the a lot of
 * serial communication protocols like I2C, SPI, CAN, etc.
 * In this project, I focused the SPI interface with 
 * master and slave modes. I hope it will be useful...  
 */

#define AUTHOR    "Ahmet Can Gulmez"
#define EMAIL     "ahmetcangulmez02@gmail.com"
#define VERSION   1.0
#define LICENSE   "MIT"

#include "transceiver.h"

int main(int argc, char **argv) {

   // Initialize the low-level settings.
   HAL_Init();

   #if (MASTER == 1)
      // Set the clock and oscillator.
      SystemClockConfig();
   #endif

   // Initialize the other peripherals.
   Initialize_GPIOA();
   Initialize_SPI1();

   // Declare the message that will be sent.
   char *message = "STM32 is amazing!";
   // Declare the buffer to store recieved data.
   char buffer[512];

   // Set the fourth pin of GPIOA as low for NSS. 
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

   #if (MASTER == 1)
      HAL_SPI_Transmit(&hspi,               // SPI hander
                     (uint8_t*) message,  // message that will be sent
                     strlen(message) + 1, // lenght of the message
                     HAL_MAX_DELAY);      // max delay time
   #else
      HAL_SPI_Receive(&hspi,              // SPI hander
                     (uint8_t*) buffer,  // buffer that will be received
                     strlen(buffer) + 1, // lenght of the buffer
                     HAL_MAX_DELAY);     // max delay time
   #endif

   // Set the fourth pin of GPIOA as high.
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

   while (1);

   return 1;
}
