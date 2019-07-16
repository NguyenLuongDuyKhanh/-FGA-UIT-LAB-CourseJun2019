/**
  ******************************************************************************
  * @author  NguyenLuongDuyKhanh
  * @date    June-2019
  * @course  FGA-UIT training course
  ******************************************************************************
  * @attention
  * I wrote this libary to use in course only.
  * Any problem, please contact me at:
  *        https://github.com/NguyenLuongDuyKhanh
  ******************************************************************************
  */ 
#ifndef __FGAcoursestm8lLib_h__
#define __FGAcoursestm8lLib_h__

#include <stdint.h>
#include "intrinsics.h"

/******************************************************************************/
/*                                GPIO                                        */
/******************************************************************************/
#define PortAb   ((GPIObit*)0x5000)    
#define PortBb   ((GPIObit*)0x5005)   
#define PortCb   ((GPIObit*)0x500a)   
#define PortDb   ((GPIObit*)0x500f)   
#define PortEb   ((GPIObit*)0x5014)  
#define PortFb   ((GPIObit*)0x5019) 

typedef struct ODR
{
  uint8_t       ODR0 :1;
  uint8_t       ODR1 :1;
  uint8_t       ODR2 :1;
  uint8_t       ODR3 :1;
  uint8_t       ODR4 :1;
  uint8_t       ODR5 :1;
  uint8_t       ODR6 :1;
  uint8_t       ODR7 :1;
}ODRreg;
 
typedef struct IDR
{
  uint8_t       IDR0 :1;
  uint8_t       IDR1 :1;
  uint8_t       IDR2 :1;
  uint8_t       IDR3 :1;
  uint8_t       IDR4 :1;
  uint8_t       IDR5 :1;
  uint8_t       IDR6 :1;
  uint8_t       IDR7 :1;
}IDRreg;

typedef struct DDR
{
  uint8_t       DDR0 :1;
  uint8_t       DDR1 :1;
  uint8_t       DDR2 :1;
  uint8_t       DDR3 :1;
  uint8_t       DDR4 :1;
  uint8_t       DDR5 :1;
  uint8_t       DDR6 :1;
  uint8_t       DDR7 :1;
}DDRreg;

typedef struct CR1
{
  uint8_t       CR10 :1;
  uint8_t       CR11 :1;
  uint8_t       CR12 :1;
  uint8_t       CR13 :1;
  uint8_t       CR14 :1;
  uint8_t       CR15 :1;
  uint8_t       CR16 :1;
  uint8_t       CR17 :1;
}CR1reg;

typedef struct CR2
{
  uint8_t       CR20 :1;
  uint8_t       CR21 :1;
  uint8_t       CR22 :1;
  uint8_t       CR23 :1;
  uint8_t       CR24 :1;
  uint8_t       CR25 :1;
  uint8_t       CR26 :1;
  uint8_t       CR27 :1;
}CR2reg;

//Define with bitfeild stype    
typedef struct GPIORegbit
{
  ODRreg       ODR;
  IDRreg       IDR;
  DDRreg       DDR;
  CR1reg       CR1;
  CR2reg       CR2;
} GPIObit;

/******************************************************************************/
/*                                      Interrupt                             */
/******************************************************************************/
#define IRQ   ((IRQreg*)0x50A0) 

typedef struct Interrupt
{
  uint8_t       EXTI_CR1;
  uint8_t       EXTI_CR2;
  uint8_t       EXTI_CR3;
  uint8_t       EXTI_SR1;
  uint8_t       EXTI_SR2;
  uint8_t       EXTI_CONF1;
}IRQreg;

/******************************************************************************/
/*                                      Clock                                 */
/******************************************************************************/

typedef struct Clock
{
  uint8_t       CLK_DIVR;
  uint8_t       CLK_CRTCR;
  uint8_t       CLK_ICKR;
  uint8_t       CLK_PCKENR1;
  uint8_t       CLK_PCKENR2;   
  uint8_t       CLK_CCOR;
  uint8_t       CLK_ECKR;
  uint8_t       CLK_SCSR;
  uint8_t       CLK_SWR;
  uint8_t       CLK_SWCR;   
  uint8_t       CLK_CSSR;
  uint8_t       CLK_CBEEPR;
  uint8_t       CLK_HSICALR;
  uint8_t       CLK_HSITRIMR;
  uint8_t       CLK_HSIUNLCKR;
  uint8_t       CLK_REGCSR; 
}ClodkReg;

#define Clock   ((ClodkReg*)0x50C0) 

//CLK_SCSR clear by hardware
//0x01 check stable status HSI (16Mhz)
//0x02 check stable status LSI (1-16Mhz)
//0x04 check stable status HSE (32.768Mhz)
//0x08 check stable status LSE (38Khz)

//CLK_SWR
//0x01 using HSI
//0x02 using LSI
//0x04 using HSE
//0x08 using LSE

//CLK_CKDIVR
//0-7 ~ 1,2,4,8,16,32,64,128 prescaling

#define SetupClock {\
  Clock->CLK_SWCR       |=0x02;\
  Clock->CLK_SWR        =1;\
  Clock->CLK_DIVR       =1;\
  Clock->CLK_PCKENR2 |=0x02;\
  while ((Clock->CLK_SCSR)!= 1); \
}

/******************************************************************************/
/*                                      Timer                                 */
/******************************************************************************/
#define TIM1   ((TIM1Reg*)0x52B0) 
#define SetupTimer1 {\
  TIM1->TIM1_PSCRH = 0x00;\
  TIM1->TIM1_PSCRL = 0xF3;\
  TIM1->TIM1_IER =0x01;\
  TIM1->TIM1_CR1 =0x01;\
}
//#define TIM2   ((ClodkReg*)0x50C0) 
//#define TIM3   ((ClodkReg*)0x50C0) 

typedef struct Timer1
{
  uint8_t       TIM1_CR1;       //52B0
  uint8_t       TIM1_CR2;
  uint8_t       TIM1_SMCR;
  uint8_t       TIM1_ETR;
  uint8_t       TIM1_DER;
  uint8_t       TIM1_IER;
  uint8_t       TIM1_SR1;
  uint8_t       TIM1_SR2;       //52B7
  
  uint8_t       TIM1_EGR;       //52B8 
  uint8_t       TIM1_CCMR1;
  uint8_t       TIM1_CCMR2;
  uint8_t       TIM1_CCMR3;
  uint8_t       TIM1_CCMR4;
  uint8_t       TIM1_CCER1;
  uint8_t       TIM1_CCER2;
  uint8_t       TIM1_CNTRH;     //52BF
  
  uint8_t       TIM1_CNTRL;     //52C0
  uint8_t       TIM1_PSCRH;
  uint8_t       TIM1_PSCRL;
  uint8_t       TIM1_ARRH;
  uint8_t       TIM1_ARRL;
  uint8_t       TIM1_RCR;
  uint8_t       TIM1_CCR1H;
  uint8_t       TIM1_CCR1L;     //52C7
  
  uint8_t       TIM1_CCR2H;     //52C8
  uint8_t       TIM1_CCR2L;
  uint8_t       TIM1_CCR3H;
  uint8_t       TIM1_CCR3L;
  uint8_t       TIM1_CCR4H;
  uint8_t       TIM1_CCR4L;
  uint8_t       TIM1_BKR;
  uint8_t       TIM1_DTR;       //52CF
  
  uint8_t       TIM1_OISR;      //52D0
  uint8_t       TIM1_DCR1;
  uint8_t       TIM1_DCR2;
  uint8_t       TIM1_DMA1R;     //52D3
}TIM1Reg;

/******************************************************************************/
/*                                      LCD                                   */
/******************************************************************************/

#define LCD     ((LCDreg*)0x5400) 

typedef struct LCDreg
{
  uint8_t       LCD_CR1;        //0x5400
  uint8_t       LCD_CR2;
  uint8_t       LCD_CR3;
  uint8_t       LCD_FRQ;
  uint8_t       LCD_PM0;
  uint8_t       LCD_PM1;
  uint8_t       LCD_PM2;
  uint8_t       LCD_PM3;        //0x5407
  uint8_t       freespace[4];   //0x5408
  uint8_t       LCD_RAM0;       //0x540c
  uint8_t       LCD_RAM1;
  uint8_t       LCD_RAM2;
  uint8_t       LCD_RAM3;
  uint8_t       LCD_RAM4;
  uint8_t       LCD_RAM5;
  uint8_t       LCD_RAM6;
  uint8_t       LCD_RAM7;
  uint8_t       LCD_RAM8;
  uint8_t       LCD_RAM9;
  uint8_t       LCD_RAM10;
  uint8_t       LCD_RAM11;
  uint8_t       LCD_RAM12;
  uint8_t       LCD_RAM13;
}LCDreg;
/******************************************************************************/
/*                              SPI                                           */
/******************************************************************************/
#define SPI     ((SPIreg*)0x5200)

typedef struct SPIreg
{
  uint8_t       SPI1_CR1;
  uint8_t       SPI1_CR2;
  uint8_t       SPI1_ICR;
  uint8_t       SPI1_SR;
  uint8_t       SPI1_DR;
  uint8_t       SPI1_CRCPR;
  uint8_t       SPI1_RXCRCR;
  uint8_t       SPI1_TXCRCR;
}SPIreg;

/******************************************************************************/
/*                 Only usefull with Stm8L152 Discovery Board                 */
/******************************************************************************/

////////////////////////////GPIO//////////////////////////////////////////////// 
   
//Control led Green Macro
#define GreenOn         PortEb->ODR.ODR7=1
#define GreenOff        PortEb->ODR.ODR7=0

//Control led Blue Macro
#define BlueOn          PortCb->ODR.ODR7=1
#define BlueOff         PortCb->ODR.ODR7=0

//configure pín PC7 OUTPUT FOR LED BLUE
//configure pín PE7 OUTPUT FOR LED GREEN
#define SetupLed {\
  PortCb->DDR.DDR7=1;\
  PortCb->CR1.CR17=1;\
  PortEb->DDR.DDR7=1;\
  PortEb->CR1.CR17=1;\
}

//configure pín PC1 INPUT FOR BUTTON USER
#define SetupUserButton {\
  PortCb->IDR.IDR1=1;\
  PortCb->CR1.CR11=1;\
  PortCb->CR2.CR21=1;\
}  

/******************************************************************************/
/*                              Interrupt Vector                              */
/******************************************************************************/



/******************************************************************************/
/*                         Function Prototype                                 */
/******************************************************************************/

void delay(unsigned int n);

/******************************************************************************/
/*                         End                                                */
/******************************************************************************/
#endif