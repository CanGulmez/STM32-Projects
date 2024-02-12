/** Data Transceiver via I2C Interface 
 * 
 * Data transciever is one of the most required skill in 
 * digital or analog systems. So, There are the a lot of
 * serial communication protocols like I2C, SPI, CAN, 
 * UART/USART, etc. In this project, I focused the I2C 
 * interface. I hope it will be useful...
 */

#define AUTHOR    "Ahmet Can Gulmez"
#define EMAIL     "ahmetcangulmez02@gmail.com"
#define VERSION   1.0
#define LICENSE   "GNU GPLv3"

#include "transceiver.h"

int main(int argc, char *argv[]) {

   // Initialize the low-level settings.
   HAL_Init();

   // Set the clock and oscillator.
   SystemClockConfig();

   // Initialize the other peripherals.
   Initialize_GPIOA();
   Initialize_I2C1();

   // Specify the contents.
   uint8_t sendData[] = {0x01, 0x02, 0x03};
   uint16_t dataSize = sizeof(sendData);
   uint8_t deviceAddress = 0x50; 

   HAL_I2C_Master_Transmit(&hi2c,          // I2C handler
                           deviceAddress,  // target address
                           sendData,       // data to send
                           dataSize,       // size of data
                           HAL_MAX_DELAY); // max delay

   while (1);

   return 1;
}