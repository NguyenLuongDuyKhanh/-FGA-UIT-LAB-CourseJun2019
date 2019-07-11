#include "FGAcoursestm8Lib.h" 
#include "FGAcoursestm8_LCD.h"

void main( void ) 
{
  SetupLed;
  SetupUserButton; 
  SetupClock;
  SetupTimer1;
  __enable_interrupt();
  LCD_GLASS_Init();
  LCD_GLASS_Clear();
        BAR0_ON;
      BAR1_ON;
      BAR2_ON;
      BAR3_ON;
  uint8_t a;
  while(1)
    { 

            for (a=48;a<=57;a++)
        {
      LCD_GLASS_WriteChar(a, POINT_ON, COLUMN_OFF,5);
      LCD_GLASS_WriteChar(a, POINT_ON, COLUMN_OFF,2);
      LCD_GLASS_WriteChar(a, POINT_ON, COLUMN_OFF,3);
      LCD_GLASS_WriteChar(a, POINT_ON, COLUMN_OFF,4);
      LCD_GLASS_WriteChar(a, POINT_OFF, COLUMN_ON,1);
      LCD_GLASS_WriteChar(a, POINT_OFF, COLUMN_ON,6);

      LCD_bar();
      
            delay(60000);
            delay(60000);
            delay(60000);
            delay(60000);
            delay(60000);
            delay(60000);
            delay(60000);
            delay(60000);
            delay(60000);
            delay(60000);
            delay(60000);
            delay(60000);
            LCD_GLASS_Clear();
      }
    }
}
