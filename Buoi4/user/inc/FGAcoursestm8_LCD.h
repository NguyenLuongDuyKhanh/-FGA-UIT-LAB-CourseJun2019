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


#ifndef __FGAcoursestm8_LCD_h__
#define __FGAcoursestm8_LCD_h__

#include "FGAcoursestm8Lib.h" 
//#include "FGAcoursestm8_LCD.h"
 

#define BAR0_ON  t_bar[0] |= 0x80
#define BAR0_OFF t_bar[0] &= ~0x80
#define BAR1_ON  t_bar[1] |= 0x08
#define BAR1_OFF t_bar[1] &= ~0x08
#define BAR2_ON  t_bar[0] |= 0x20
#define BAR2_OFF t_bar[0] &= ~0x20
#define BAR3_ON t_bar[1] |= 0x02
#define BAR3_OFF t_bar[1] &= ~0x02

#define  POINT_OFF 0
#define  POINT_ON 1

/* Define for caracter ":" */
#define  COLUMN_OFF 0
#define  COLUMN_ON 1

/* code for 'µ' character */
#define C_UMAP 0x6081

/* code for 'm' character */
#define C_mMap 0xb210

/* code for 'n' character */
#define C_nMap 0x2210

/* constant code for '*' character */
#define star 0xA0D7

/* constant code for '-' character */
#define C_minus 0xA000

/* LCD BAR status: We don't write directly in LCD RAM for save the bar setting */
static uint8_t t_bar[2]={0x0,0X0};

static const uint16_t CapLetterMap[26]=
    {
        /* A      B      C      D      E      F      G      H      I  */
        0xFE00,0x6711,0x1d00,0x4711,0x9d00,0x9c00,0x3f00,0xfa00,0x0011,
        /* J      K      L      M      N      O      P      Q      R  */
        0x5300,0x9844,0x1900,0x5a42,0x5a06,0x5f00,0xFC00,0x5F04,0xFC04,
        /* S      T      U      V      W      X      Y      Z  */
        0xAF00,0x0411,0x5b00,0x18c0,0x5a84,0x00c6,0x0052,0x05c0
    };

/* Constant table for number '0' --> '9' */
static const uint16_t NumberMap[10]=
    {
        /* 0      1      2      3      4      5      6      7      8      9  */
        0x5F00,0x4200,0xF500,0x6700,0xEa00,0xAF00,0xBF00,0x04600,0xFF00,0xEF00
    };


void LCD_GLASS_Init(void);
void LCD_GLASS_Clear(void);
void display_lcd();

void LCD_GLASS_WriteChar(uint8_t ch, uint8_t point, uint8_t column, uint8_t position);
void LCD_Conv_Char_Seg(uint8_t c,uint16_t point,uint8_t column, uint8_t* digit);
void LCD_bar();
#endif 