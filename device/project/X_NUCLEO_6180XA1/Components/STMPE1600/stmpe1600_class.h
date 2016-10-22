/**
 ******************************************************************************
 * @file    stmpe1600_class.h
 * @author  AST / EST
 * @version V0.0.1
 * @date    14-April-2015
 * @brief   Header file for component stmpe1600
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
 *       without specific prior written permission.
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
#ifndef     __STMPE1600_CLASS
#define     __STMPE1600_CLASS
/* Includes ------------------------------------------------------------------*/
#include    "DevI2C.h"

#define STMPE1600_DEF_DEVICE_ADDRESS  (uint8_t)0x42*2   
#define STMPE1600_DEF_DIGIOUT_LVL      1

/**  STMPE1600 registr map **/
#define ChipID_0_7      (uint8_t)0x00
#define ChipID_8_15     (uint8_t)0x01
#define VersionId       (uint8_t)0x02
#define SYS_CTRL        (uint8_t)0x03
#define IEGPIOR_0_7	    (uint8_t)0x08
#define IEGPIOR_8_15	  (uint8_t)0x09
#define ISGPIOR_0_7	    (uint8_t)0x0A
#define ISGPIOR_8_15	  (uint8_t)0x0B
#define GPMR_0_7	      (uint8_t)0x10
#define GPMR_8_15	      (uint8_t)0x11
#define GPSR_0_7	      (uint8_t)0x12
#define GPSR_8_15	      (uint8_t)0x13
#define GPDR_0_7	      (uint8_t)0x14
#define GPDR_8_15	      (uint8_t)0x15
#define GPIR_0_7	      (uint8_t)0x16
#define GPIR_8_15	      (uint8_t)0x17

#define SOFT_RESET			(uint8_t)0x80

  typedef enum {
    // GPIO Expander pin names
    GPIO_0=0,
    GPIO_1,
    GPIO_2,
    GPIO_3,            
    GPIO_4,
    GPIO_5,
    GPIO_6,
    GPIO_7,            
    GPIO_8,
    GPIO_9,
    GPIO_10,
    GPIO_11,            
    GPIO_12,
    GPIO_13,
    GPIO_14,
    GPIO_15,
	NOT_CON
} ExpGpioPinName;   

typedef enum {
    INPUT = 0,
    OUTPUT,
    NOT_CONNECTED
}ExpGpioPinDirection;

/* Classes -------------------------------------------------------------------*/
/** Class representing a single stmpe1600 GPIO expander output pin
 */
class STMPE1600DigiOut {
	
 public: 
    /** Constructor
     * @param[in] &i2c device I2C to be used for communication
     * @param[in] outpinname the desired out pin name to be created
     * @param[in] DevAddr the stmpe1600 I2C device addres (deft STMPE1600_DEF_DEVICE_ADDRESS)
     * @param[in] lvl the default ot pin level  
     */ 
    STMPE1600DigiOut (DevI2C &i2c, ExpGpioPinName outpinname, uint8_t DevAddr=STMPE1600_DEF_DEVICE_ADDRESS, bool lvl=STMPE1600_DEF_DIGIOUT_LVL): dev_i2c(i2c), expdevaddr(DevAddr), exppinname(outpinname) 
    {
       uint8_t data[2];				
			 if (exppinname == NOT_CON) return;
       /* set the exppinname as output */
       dev_i2c.i2c_read(data, expdevaddr, GPDR_0_7, 1);
       dev_i2c.i2c_read(&data[1], expdevaddr, GPDR_8_15, 1);			
       *(uint16_t*)data = *(uint16_t*)data | (1<<(uint16_t)exppinname);  // set gpio as out 			
       dev_i2c.i2c_write(data, expdevaddr, GPDR_0_7, 1);
       dev_i2c.i2c_write(&data[1], expdevaddr, GPDR_8_15, 1);			
       write(lvl);
    }   

	/**
	 * @brief       Write on the out pin
	 * @param[in]   lvl level to write
	 * @return      0 on Success
	 */			
    void write (int lvl) 
    {
       uint8_t data[2];			
			 if (exppinname == NOT_CON) return;			
       /* set the exppinname state to lvl */
       dev_i2c.i2c_read(data, expdevaddr, GPSR_0_7, 2);
       *(uint16_t*)data = *(uint16_t*)data & (uint16_t)(~(1<<(uint16_t)exppinname));  // set pin mask 			
       if (lvl) *(uint16_t*)data = *(uint16_t*)data | (uint16_t)(1<<(uint16_t)exppinname);
       dev_i2c.i2c_write(data, expdevaddr, GPSR_0_7, 2);
    }

	/**
	 * @brief       Overload assignement operator
	 */					
    STMPE1600DigiOut& operator=(int lvl)
    {
       write (lvl);
       return *this;
    }		
		
 private:
    DevI2C &dev_i2c; 
    uint8_t expdevaddr;
    ExpGpioPinName exppinname; 	
};

/* Classes -------------------------------------------------------------------*/
/** Class representing a single stmpe1600 GPIO expander input pin
 */
class STMPE1600DigiIn 
{	
 public: 
     /** Constructor
     * @param[in] &i2c device I2C to be used for communication
     * @param[in] inpinname the desired input pin name to be created
     * @param[in] DevAddr the stmpe1600 I2C device addres (deft STMPE1600_DEF_DEVICE_ADDRESS)
     */ 
    STMPE1600DigiIn (DevI2C &i2c, ExpGpioPinName inpinname, uint8_t DevAddr=STMPE1600_DEF_DEVICE_ADDRESS): dev_i2c(i2c), expdevaddr(DevAddr), exppinname(inpinname) 
    {
       uint8_t data[2];
			 if (exppinname == NOT_CON) return;			
       /* set the exppinname as input pin direction */
       dev_i2c.i2c_read(data, expdevaddr, GPDR_0_7, 2);
       *(uint16_t*)data = *(uint16_t*)data & (uint16_t)(~(1<<(uint16_t)exppinname));  // set gpio as in			
       dev_i2c.i2c_write(data, expdevaddr, GPDR_0_7, 2);
    }         

	/**
	 * @brief       Read the input pin
	 * @return      The pin logical state 0 or 1
	 */			
    bool read () 
    {
       uint8_t data[2];
			 if (exppinname == NOT_CON) return 0;						
       /* read the exppinname */
       dev_i2c.i2c_read(data, expdevaddr, GPMR_0_7, 2);
       *(uint16_t*)data = *(uint16_t*)data & (uint16_t)(1<<(uint16_t)exppinname);  // mask the in gpio
       if (data[0] || data[1]) return 1;
       return 0;
    }
		
    operator int() 
    {		
       return read();
    }		
		
 private:
    DevI2C &dev_i2c; 
    uint8_t expdevaddr;
    ExpGpioPinName exppinname;      
};

/* Classes -------------------------------------------------------------------*/
/** Class representing a whole stmpe1600 component (16 gpio)
 */
class STMPE1600 {
	
 public: 
    /** Constructor
    * @param[in] &i2c device I2C to be used for communication
    * @param[in] DevAddr the stmpe1600 I2C device addres (deft STMPE1600_DEF_DEVICE_ADDRESS)
    */ 
    STMPE1600 (DevI2C &i2c, uint8_t DevAddr=STMPE1600_DEF_DEVICE_ADDRESS ) : dev_i2c(i2c)
    { 
       dev_i2c = i2c;								
       expdevaddr = DevAddr;
			 writeSYS_CTRL (SOFT_RESET);
			
       GPDR0_15 = (uint16_t)0;	// gpio dir all IN
			 write16bitReg (GPDR_0_7, &GPDR0_15);			
       GPSR0_15 = (uint16_t)0x0ffff;  // gpio status all 1
			 write16bitReg (GPSR_0_7, &GPSR0_15);			
    }

	/**
	 * @brief       Write the SYS_CTRL register 
	 * @param[in]   Data to be written (bit fields)
	 */		
    void writeSYS_CTRL (uint8_t data)     // data = SOFT_RESET reset the device
    {
	     dev_i2c.i2c_write((uint8_t*)SYS_CTRL, expdevaddr, data, 1);
    }
    
	/**
	 * @brief       Set the out pin
	 * @param[in]   The pin name
	 * @return      0 on Success
	 */			
	bool setGPIO (ExpGpioPinName PinName) 
	{
		 if (PinName == NOT_CON) return true;			
		 GPSR0_15 = GPSR0_15 | ((uint16_t)0x0001<<PinName);
		 write16bitReg (GPSR_0_7 , &GPSR0_15);
		 return false;
	}
	
	/**
	 * @brief       Clear the out pin
	 * @param[in]   The pin name
	 * @return      0 on Success
	 */			
	bool clrGPIO (ExpGpioPinName PinName) 
	{
		 if (PinName == NOT_CON) return true;			
		 GPSR0_15 = GPSR0_15 & (~((uint16_t)0x0001<<PinName));
		 write16bitReg (GPSR_0_7 , &GPSR0_15);
		 return false;
	}		
	
	/**
	 * @brief       Read the input pin
	 * @param[in]   The pin name
	 * @return      The logical pin level
	 */					
	bool rdGPIO (ExpGpioPinName PinName) 
	{				
		  uint16_t gpmr0_15;
		  if (PinName == NOT_CON) return true;
		  read16bitReg (GPMR_0_7, &gpmr0_15);
		  gpmr0_15 = gpmr0_15 & ((uint16_t)0x0001<<PinName);
		  if (gpmr0_15) return true; 			
		  return false;			
	}
	
	/**
	 * @brief       Set the pin direction
	 * @param[in]   The pin name
	 * @param[in]   The pin direction	 
	 * @return      0 on success
	 */					
	bool setGPIOdir (ExpGpioPinName PinName, ExpGpioPinDirection PinDir) 
	{
	       if (PinName == NOT_CON || PinDir == NOT_CONNECTED) return true; 
		   GPDR0_15 = GPDR0_15 & (~((uint16_t)0x0001<<PinName));  // clear the Pin
		   GPDR0_15 = GPDR0_15 | ((uint16_t)PinDir<<PinName);
		   write16bitReg (GPDR_0_7 , &GPDR0_15);
		   return false;
	}

	/**
	 * @brief       Read a 16 bits register
	 * @param[in]   The register address
	 * @param[in]   The pointer to the read data
	 */					
    void read16bitReg (uint8_t Reg16Addr, uint16_t *Reg16Data)
    {
       dev_i2c.i2c_read((uint8_t*)Reg16Data, expdevaddr, Reg16Addr, 2);	
    }				

	/**
	 * @brief       Write a 16 bits register
	 * @param[in]   The register address
	 * @param[in]   The pointer to the data to be written
	 */							
    void write16bitReg (uint8_t Reg16Addr, uint16_t *Reg16Data)
    {
       dev_i2c.i2c_write((uint8_t*)Reg16Data, expdevaddr, Reg16Addr, 2);	
    }		

 private:					
    DevI2C &dev_i2c; 	 
    uint16_t GPDR0_15;  // local copy of bit direction reg 
    uint16_t GPSR0_15;  // local copy of bit status reg 
    uint8_t expdevaddr; // expander device i2c addr
};

#endif // __STMPE1600_CLASS
