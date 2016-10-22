/**
 ******************************************************************************
 * @file    x_nucleo_6180xa1.h
 * @author  AST / EST
 * @version V0.0.1
 * @date    13-April-2015
 * @brief   Header file for class X_NUCLEO_6180XA1 representing a X-NUCLEO-6180XA1
 *          expansion board
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

/* Define to prevent from recursive inclusion --------------------------------*/
#ifndef __X_NUCLEO_6180XA1_H
#define __X_NUCLEO_6180XA1_H

/* Includes ------------------------------------------------------------------*/
#include "mbed.h"
#include "vl6180x_class.h"
#include "Display_class.h"
#include "stmpe1600_class.h"
#include "DevI2C.h"
#include "Switch_class.h"

/** New device addresses */
#define NEW_SENSOR_TOP_ADDRESS			0x10
#define NEW_SENSOR_BOTTOM_ADDRESS		0x11
#define NEW_SENSOR_LEFT_ADDRESS			0x12
#define NEW_SENSOR_RIGHT_ADDRESS		0x13

/* Classes--------------------------------------------------------------------*/

/* Classes -------------------------------------------------------------------*/
/** Class representing the X-NUCLEO-VL6180XA1 expansion board singleton obj
 */
class X_NUCLEO_6180XA1
{
protected:
     /** Constructor 1
     * @param[in] &i2c device I2C to be used for communication
     */
    X_NUCLEO_6180XA1(DevI2C *ext_i2c) : dev_i2c(ext_i2c)
    {
       stmpe1600 = new STMPE1600(*ext_i2c);		
       stmpe1600->writeSYS_CTRL (SOFT_RESET);		
       Switch = new SWITCH (*stmpe1600, GPIO_11);	
       display = new Display(*stmpe1600);			
			
       gpio0_top=new STMPE1600DigiOut(*dev_i2c, GPIO_12);
       sensor_top=new VL6180X(*dev_i2c, *gpio0_top, A3);
       
       gpio0_bottom=new STMPE1600DigiOut(*dev_i2c, GPIO_13);
       sensor_bottom=new VL6180X(*dev_i2c, *gpio0_bottom, A2);
       
       gpio0_left=new STMPE1600DigiOut(*dev_i2c, GPIO_14);
       sensor_left=new VL6180X(*dev_i2c, *gpio0_left, D13);
       
       gpio0_right=new STMPE1600DigiOut(*dev_i2c, GPIO_15);
       sensor_right=new VL6180X(*dev_i2c, *gpio0_right, D2);
    }
    
    /** Constructor 2
     * @param[in] &i2c device I2C to be used for communication
     * @param[in] PinName gpio1_top Mbed DigitalOut pin name to be used as a top sensor GPIO_1 INT
     * @param[in] PinName gpio1_bottom Mbed DigitalOut pin name to be used as a bottom sensor GPIO_1 INT
     * @param[in] PinName gpio1_left Mbed DigitalOut pin name to be used as a left sensor GPIO_1 INT
     * @param[in] PinName gpio1_right Mbed DigitalOut pin name to be used as a right sensor GPIO_1 INT               
     */    
    X_NUCLEO_6180XA1(DevI2C *ext_i2c, PinName gpio1_top, PinName gpio1_bottom,
    		 						  PinName gpio1_left, PinName gpio1_right) : dev_i2c(ext_i2c) {
       stmpe1600 = new STMPE1600(*ext_i2c);		    		 						  	
       stmpe1600->writeSYS_CTRL (SOFT_RESET);	
       Switch = new SWITCH (*stmpe1600, GPIO_11);	
       display = new Display(*stmpe1600);			

       gpio0_top=new STMPE1600DigiOut(*dev_i2c, GPIO_12);			
       sensor_top=new VL6180X(*dev_i2c, *gpio0_top, gpio1_top);
       
       gpio0_bottom=new STMPE1600DigiOut(*dev_i2c, GPIO_13);   
       sensor_bottom=new VL6180X(*dev_i2c, *gpio0_bottom, gpio1_bottom);
 
       gpio0_left=new STMPE1600DigiOut(*dev_i2c, GPIO_14);      
       sensor_left=new VL6180X(*dev_i2c, *gpio0_left, gpio1_left);
       
       gpio0_right=new STMPE1600DigiOut(*dev_i2c, GPIO_15);
       sensor_right=new VL6180X(*dev_i2c, *gpio0_right, gpio1_right);   	
    }  

     /**
     * @brief       Override default copy constructor as empty
     * @param[in]   &X_NUCLEO_6180XA1 singleton object reference
     * @return     
     */		    
    X_NUCLEO_6180XA1() {};
    
     /**
     * @brief       Override default assignement operator to avoid multiple singletons
     * @param[in]   &X_NUCLEO_6180XA1 singleton object reference
     * @return     
     */		    
    void operator = (const X_NUCLEO_6180XA1&);
    
public:
     /**
     * @brief       Creates a singleton object instance
     * @param[in]   &i2c device I2C to be used for communication
     * @return      Pointer to the object instance
     */					     
    static X_NUCLEO_6180XA1 *Instance(DevI2C *ext_i2c);
    
     /**
     * @brief       Creates a singleton object instance
     * @param[in]   &i2c device I2C to be used for communication
     * @param[in]   PinName gpio1_top the pin connected to top sensor INT     
     * @param[in]   PinName gpio1_bottem the pin connected to bottom sensor INT          
     * @param[in]   PinName gpio1_left the pin connected to left sensor INT          
     * @param[in]   PinName gpio1_right the pin connected to right sensor INT          
	 * @return      Pointer to the object instance
	 */					         
    static X_NUCLEO_6180XA1 *Instance(DevI2C *ext_i2c, PinName gpio1_top, PinName gpio1_bottom,
                                             PinName gpio1_left, PinName gpio1_right);

    
	/**
	 * @brief       Initialize the board and sensors with deft values
	 * @return      0 on success
	 */		
    int InitBoard();

	/**
	 * @brief       Read the on board red slider switch
	 * @return      0 or 1 according to switch position
	 */				
    bool RdSwitch () {
	     return Switch->RdSwitch();	
    }

    DevI2C *dev_i2c;
    VL6180X *sensor_top;
    VL6180X *sensor_bottom;
    VL6180X *sensor_left;
    VL6180X *sensor_right;
    STMPE1600 * stmpe1600;
    SWITCH * Switch;	    
    Display *display;
    
private:
    STMPE1600DigiOut *gpio0_top;
    STMPE1600DigiOut *gpio0_bottom;
    STMPE1600DigiOut *gpio0_left;
    STMPE1600DigiOut *gpio0_right;    
    static X_NUCLEO_6180XA1 *_instance;
};

#endif /* __X_NUCLEO_6180XA1_H */
