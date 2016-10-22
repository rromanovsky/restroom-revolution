#include "mbed.h"
#include "x_nucleo_6180xa1.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* This VL6180X Expansion board test application performs a range measurement and als measurement in polling mode
   on the onboard embedded top sensor. 
   The result of both the measures are printed on the serial over.  
   GetDistance and GetLux are synchronous!. So they blocks the caller until the result will be ready 
*/

#define VL6180X_I2C_SDA   D14 
#define VL6180X_I2C_SCL   D15 

static X_NUCLEO_6180XA1 *board=NULL;

/*=================================== Main ==================================
  Prints on the serial over USB the measured distance and lux.
  The measures are run in single shot polling mode.
=============================================================================*/
int main()
{ 
   int status;
   uint32_t lux, dist; 	 
   DevI2C *device_i2c =new DevI2C(VL6180X_I2C_SDA, VL6180X_I2C_SCL);     		
   /* creates the 6180XA1 expansion board singleton obj */
   board=X_NUCLEO_6180XA1::Instance(device_i2c, A3, A2, D13, D2);
   /* init the 6180XA1 expansion board with default values */
   status=board->InitBoard();
   if(status) { printf("Failed to init board!\n\r"); return 0; }
   while(1)
   {
      board->sensor_top->GetDistance(&dist);	
      board->sensor_top->GetLux(&lux);
      printf ("%d\n", lux>20);    
      wait_ms(1000);	
   }  
}
