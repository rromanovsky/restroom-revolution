/**
 ******************************************************************************
 * @file    Display.h
 * @author  AST / EST
 * @version V0.0.1
 * @date    14-April-2015
 * @brief   Header file for display
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

#ifndef __DISPLAY_H
#define __DISPLAY_H

/* Includes ------------------------------------------------------------------*/
#include "mbed.h"
#include "stmpe1600_class.h"
#include "DevI2C.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DP  (1<<7)
#define NOT_7_NO_DP( ... ) (uint8_t) ~( __VA_ARGS__ + DP )
#define S0 (1<<0)
#define S1 (1<<1)
#define S2 (1<<2)
#define S3 (1<<3)
#define S4 (1<<4)
#define S5 (1<<5)
#define S6 (1<<6)

#ifndef __cpluplus  
/* refer to http://www.twyman.org.uk/Fonts/ */
static const uint8_t ascii_to_display_lut[256]={
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	[32]=           0,
	0,0,0,0,0,0,0,0,
	0,
	[42]=           NOT_7_NO_DP(),
	0,0,
	[45]=           S6,
	0,0,
	[48]=           NOT_7_NO_DP(S6),
	[49]=           S1+S2,
	[50]=           S0+S1+S6+S4+S3,
	[51]=           NOT_7_NO_DP(S4+S5),
	[52]=           S5+S1+S6+S2,
	[53]=           NOT_7_NO_DP(S1+S4),
	[54]=           NOT_7_NO_DP(S1),
	[55]=           S0+S1+S2,
	[56]=           NOT_7_NO_DP(0),
	[57]=           NOT_7_NO_DP(S4),
	0,0,0,
	[61]=           S3+S6,
	0,
	[63]=           NOT_7_NO_DP(S5+S3+S2),
	[64]=           S0+S3,
	[65]=           NOT_7_NO_DP(S3),
	[66]=           NOT_7_NO_DP(S0+S1), /* as b  */
	[67]=           S0+S3+S4+S5, // same as [
	[68]=           S0+S3+S4+S5, // same as [ DUMMY
	[69]=           NOT_7_NO_DP(S1+S2),
	[70]=           S6+S5+S4+S0,
	[71]=           NOT_7_NO_DP(S4), /* same as 9 */
	[72]=           NOT_7_NO_DP(S0+S3),
	[73]=           S1+S2,
	[74]=           S1+S2+S3+S4,
	[75]=           NOT_7_NO_DP(S0+S3), /* same as H */
	[76]=           S3+S4+S5,
	[77]=           S0+S4+S2, /* same as  m*/
	[78]=           S2+S4+S6, /* same as n*/
	[79]=           NOT_7_NO_DP(S6),
	[80]=           S0+S1+S2+S5+S6, // sames as 'q'
	[81]=           NOT_7_NO_DP(S3+S2),
	[82]=           S4+S6,
	[83]=           NOT_7_NO_DP(S1+S4), /* sasme as 5 */
	[84]=           NOT_7_NO_DP(S0+S1+S2), /* sasme as t */
	[85]=           NOT_7_NO_DP(S6+S0),
	[86]=           S4+S3+S2, // is u but u use U
	[87]=           S1+S3+S5,
	[88]=           NOT_7_NO_DP(S0+S3), // similar to H
	[89]=           NOT_7_NO_DP(S0+S4),
	[90]=           S0+S1+S6+S4+S3, // same as 2
	[91]=           S0+S3+S4+S5,
	0,
	[93]=           S0+S3+S2+S1,
	[94]=           S0, /* use as top bar */
	[95]=           S3,	
	0,
	[97]=           S2+ S3+ S4+ S6 ,
	[98]=           NOT_7_NO_DP(S0+S1),
	[99]=           S6+S4+S3,
	[100]=           NOT_7_NO_DP(S0+S5),
	[101]=           NOT_7_NO_DP(S2),
	[102]=           S6+S5+S4+S0, /* same as F */
	[103]=           NOT_7_NO_DP(S4), /* same as 9 */
	[104]=           S6+S5+S4+S2,
	[105]=           S4,
	[106]=           S1+S2+S3+S4,
	[107]=           S6+S5+S4+S2, /* a h */
	[108]=           S3+S4,
	[109]=           S0+S4+S2, /* same as  */
	[110]=           S2+S4+S6,
	[111]=           S6+S4+S3+S2,
	[112]=           NOT_7_NO_DP(S3+S2), // same as P
	[113]=           S0+S1+S2+S5+S6,
	[114]=           S4+S6,
	[115]=           NOT_7_NO_DP(S1+S4),
	[116]=           NOT_7_NO_DP(S0+S1+S2),
	[117]=           S4+S3+S2+S5+S1, // U
	[118]=           S4+S3+S2, // is u but u use U
	[119]=           S1+S3+S5,
	[120]=           NOT_7_NO_DP(S0+S3), // similar to H
	[121]=           NOT_7_NO_DP(S0+S4),
	[122]=           S0+S1+S6+S4+S3, // same as 2
	0,0,0,
	[126]=           S0+S3+S6 /* 3 h bar */
};
#else 
/* refer to http://www.twyman.org.uk/Fonts/ */
static const uint8_t ascii_to_display_lut[256]={
      [' ']=           0,
      ['-']=           S6,
      ['_']=           S3,
      ['=']=           S3+S6,
      ['~']=           S0+S3+S6, /* 3 h bar */
      ['^']=           S0, /* use as top bar */

      ['?']=           NOT_7_NO_DP(S5+S3+S2),
      ['*']=           NOT_7_NO_DP(),
      ['[']=           S0+S3+S4+S5,
      [']']=           S0+S3+S2+S1,
      ['@']=           S0+S3,

      ['0']=           NOT_7_NO_DP(S6),
      ['1']=           S1+S2,
      ['2']=           S0+S1+S6+S4+S3,
      ['3']=           NOT_7_NO_DP(S4+S5),
      ['4']=           S5+S1+S6+S2,
      ['5']=           NOT_7_NO_DP(S1+S4),
      ['6']=           NOT_7_NO_DP(S1),
      ['7']=           S0+S1+S2,
      ['8']=           NOT_7_NO_DP(0),
      ['9']=           NOT_7_NO_DP(S4),
    
      ['a']=           S2+ S3+ S4+ S6 ,
      ['b']=           NOT_7_NO_DP(S0+S1),
      ['c']=           S6+S4+S3,
      ['d']=           NOT_7_NO_DP(S0+S5),
      ['e']=           NOT_7_NO_DP(S2),
      ['f']=           S6+S5+S4+S0, /* same as F */
      ['g']=           NOT_7_NO_DP(S4), /* same as 9 */
      ['h']=           S6+S5+S4+S2,
      ['i']=           S4,
      ['j']=           S1+S2+S3+S4,
      ['k']=           S6+S5+S4+S2, /* a h */
      ['l']=           S3+S4,
      ['m']=           S0+S4+S2, /* same as  */
      ['n']=           S2+S4+S6,
      ['o']=           S6+S4+S3+S2,
      ['p']=           NOT_7_NO_DP(S3+S2), // same as P
      ['q']=           S0+S1+S2+S5+S6,
      ['r']=           S4+S6,
      ['s']=           NOT_7_NO_DP(S1+S4),
      ['t']=           NOT_7_NO_DP(S0+S1+S2),
      ['u']=           S4+S3+S2+S5+S1, // U
      ['v']=           S4+S3+S2, // is u but u use U
      ['w']=           S1+S3+S5,
      ['x']=           NOT_7_NO_DP(S0+S3), // similar to H
      ['y']=           NOT_7_NO_DP(S0+S4),
      ['z']=           S0+S1+S6+S4+S3, // same as 2
      
      ['A']=           NOT_7_NO_DP(S3),
      ['B']=           NOT_7_NO_DP(S0+S1), /* as b  */
      ['C']=           S0+S3+S4+S5, // same as [
      ['E']=           NOT_7_NO_DP(S1+S2),
      ['F']=           S6+S5+S4+S0,
      ['G']=           NOT_7_NO_DP(S4), /* same as 9 */
      ['H']=           NOT_7_NO_DP(S0+S3),
      ['I']=           S1+S2,
      ['J']=           S1+S2+S3+S4,
      ['K']=           NOT_7_NO_DP(S0+S3), /* same as H */
      ['L']=           S3+S4+S5,
      ['M']=           S0+S4+S2, /* same as  m*/
      ['N']=           S2+S4+S6, /* same as n*/
      ['O']=           NOT_7_NO_DP(S6),
      ['P']=           S0+S1+S2+S5+S6, // sames as 'q'
      ['Q']=           NOT_7_NO_DP(S3+S2),
      ['R']=           S4+S6,
      ['S']=           NOT_7_NO_DP(S1+S4), /* sasme as 5 */
      ['T']=           NOT_7_NO_DP(S0+S1+S2), /* sasme as t */
      ['U']=           NOT_7_NO_DP(S6+S0),
      ['V']=           S4+S3+S2, // is u but u use U
      ['W']=           S1+S3+S5,
      ['X']=           NOT_7_NO_DP(S0+S3), // similar to H
      ['Y']=           NOT_7_NO_DP(S0+S4),
      ['Z']=           S0+S1+S6+S4+S3 // same as 2
};
#endif

#undef S0
#undef S1
#undef S2
#undef S3
#undef S4
#undef S5
#undef S6
#undef DP

#define DISPLAY_DELAY   1  // in mSec 		

/* Classes -------------------------------------------------------------------*/
/** Class representing Display
 */ 

class Display
{
 public:
     /** Constructor
     * @param[in] &stmpe_1600 device handler to be used for display control
     */    
     Display(STMPE1600 &stmpe_1600) : stmpe1600(stmpe_1600) {
	    stmpe1600.setGPIOdir (GPIO_7,  OUTPUT);  // Digit1	 
	    stmpe1600.setGPIOdir (GPIO_8,  OUTPUT);  // Digit2	 
	    stmpe1600.setGPIOdir (GPIO_9,  OUTPUT);  // Digit3	 
	    stmpe1600.setGPIOdir (GPIO_10, OUTPUT);  // Digit4	 	 
	 
	    stmpe1600.setGPIOdir (GPIO_0,  OUTPUT);  // SegmentA	 	 	 
	    stmpe1600.setGPIOdir (GPIO_1,  OUTPUT);  // SegmentB	 	 	 
	    stmpe1600.setGPIOdir (GPIO_2,  OUTPUT);  // SegmentC	 	 
	    stmpe1600.setGPIOdir (GPIO_3,  OUTPUT);  // SegmentD	 	 
	    stmpe1600.setGPIOdir (GPIO_4,  OUTPUT);  // SegmentE	 	 
	    stmpe1600.setGPIOdir (GPIO_5,  OUTPUT);  // SegmentF	 	 
	    stmpe1600.setGPIOdir (GPIO_6,  OUTPUT);  // SegmentG	 	 	  	 
     }
     
	/*** Interface Methods ***/	     
	/**
	 * @brief       Print the string on display
	 * @param[in]   String to be printed
	 * @param[in]   String lenght [min 1, max 4]
	 * @return      void
	 */				
     void DisplayString (char str[4], char strlen)
     {
       int i, dgt;
       const char *pc;
       uint8_t data[2];
       uint16_t *pdata = (uint16_t*)data;				
			
       for(i=0, dgt=4-strlen, pc=str; i<strlen && *pc!=0; i++, pc++, dgt++)
       {
          _V2_Set7Segment( ascii_to_display_lut[(uint8_t)*pc], dgt);
          if( *(pc+1)== '.')
          {
             pc++;
          }
          wait_ms(DISPLAY_DELAY);					
					stmpe1600.read16bitReg(GPSR_0_7, pdata);
          *pdata = *pdata | (uint16_t)0x0780;				// all digits off
					stmpe1600.write16bitReg(GPSR_0_7, pdata);
       }						
			
	 }
	 
	/**
	 * @brief       Print the digit on display
	 * @param[in]   Digit value to be printed
	 * @param[in]   Digit to be used [min 0, max 3]
	 * @return      void
	 */				 
     void DisplayDigit (char *val, char dgt)	
     {
       uint8_t data[2];
       uint16_t *pdata = (uint16_t*)data;		
			
	   stmpe1600.read16bitReg(GPSR_0_7, pdata);
       *pdata = *pdata | (uint16_t)0x0780;				// all digits off
	   stmpe1600.write16bitReg(GPSR_0_7, pdata);
       _V2_Set7Segment( ascii_to_display_lut[(uint8_t)*val], dgt);						
     }		
		
private:		
     void _V2_Set7Segment( int Leds, int digit )
     {
       //Digits_off();
       uint16_t dgt;
       dgt = 1<<digit;
       dgt = ((uint16_t)dgt)<<7;
       dgt = ~dgt;	
       uint8_t data[2];
       uint16_t *pdata = (uint16_t*)data;			 

		 
       /* set the exppinname state to lvl */
	   stmpe1600.read16bitReg(GPSR_0_7, pdata);
       *pdata = *pdata  | (uint16_t)0x007F;      // 7 segments off
	   stmpe1600.write16bitReg(GPSR_0_7, pdata);
		 
       int mask=1;
       for (int i=0; i<7; i++) 
       { 
          if (Leds & mask) *pdata = *pdata & ~(uint16_t)mask;  
          mask = mask<<1;
       }		 
       *pdata = *pdata & dgt;
	   stmpe1600.write16bitReg(GPSR_0_7, pdata);
     }				
	 STMPE1600 &stmpe1600;
};

#ifdef __cplusplus
}
#endif
#endif // __DISPLAY_H