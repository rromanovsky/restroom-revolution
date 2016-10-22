/**
 ******************************************************************************
 * @file    x_nucleo_6180xa1.cpp
 * @author  AST / EST
 * @version V0.0.1
 * @date    13-April-2015
 * @brief   Implementation file for the X_NUCLEO_VL6180XA1 singleton class
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "x_nucleo_6180xa1.h"

/* Static variables ----------------------------------------------------------*/
X_NUCLEO_6180XA1* X_NUCLEO_6180XA1::_instance = NULL;

X_NUCLEO_6180XA1* X_NUCLEO_6180XA1::Instance(DevI2C *ext_i2c)
{
   if(_instance==NULL)
      _instance=new X_NUCLEO_6180XA1(ext_i2c);
   else
      VL6180x_ErrLog("Failed to create X_NUCLEO_6180XA1 instance\n\r");
   return _instance;
}

X_NUCLEO_6180XA1* X_NUCLEO_6180XA1::Instance(DevI2C *ext_i2c, 
                                             PinName gpio1_top, PinName gpio1_bottom,
                                             PinName gpio1_left, PinName gpio1_right)
{
   if(_instance==NULL)
      //_instance=new X_NUCLEO_6180XA1(ext_i2c);
      _instance=new X_NUCLEO_6180XA1(ext_i2c, gpio1_top, gpio1_bottom, gpio1_left, gpio1_right);
   else
      VL6180x_ErrLog("Failed to create X_NUCLEO_6180XA1 instance\n\r");
   return _instance;
}


int X_NUCLEO_6180XA1::InitBoard()
{	
   int status, n_dev=0; uint8_t sensor_address;
	
     sensor_top->VL6180x_Off();
     sensor_bottom->VL6180x_Off();
     sensor_left->VL6180x_Off();
     sensor_right->VL6180x_Off();
     sensor_address = NEW_SENSOR_TOP_ADDRESS;     
     status=sensor_top->Init(&sensor_address);
     if(status)
     {
        printf("Sensor top not present\n\r");
     }
     else
     {
        printf("Sensor top present\n\r");
        n_dev++;
     }
     sensor_address = NEW_SENSOR_BOTTOM_ADDRESS;
     status=sensor_bottom->Init(&sensor_address);
     if(status)
     {
        printf("Sensor bottom not present\n\r");
     }
     else
     {
        printf("Sensor bottom present\n\r");
        n_dev++;
     }
     sensor_address = NEW_SENSOR_LEFT_ADDRESS;
     status=sensor_left->Init(&sensor_address);
     if(status)
     {
        printf("Sensor left not present\n\r");
     }
     else
     {
        printf("Sensor left present\n\r");
        n_dev++;
     }
     sensor_address = NEW_SENSOR_RIGHT_ADDRESS;
     status=sensor_right->Init(&sensor_address);
     if(status)
     {
        printf("Sensor right not present\n\r");
     }
     else
     {
        printf("Sensor right present\n\r");
        n_dev++;
     }
   if(n_dev==0)
      return 1;
   else
      return 0;
}


