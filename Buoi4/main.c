#include "FGAcoursestm8Lib.h" 
#include "FGAcoursestm8_LCD.h"

uint8_t WriteSpi(uint8_t);
void SPIMaster();
void SPISlave();
  


void main( void ) 
{
  SetupLed;
  SetupUserButton; 
  SetupClock;
  SetupTimer1;
  __enable_interrupt();
  LCD_GLASS_Init();
  LCD_GLASS_Clear();
  
  //SPIMaster();
  SPISlave();
  
  uint8_t a = 67;
  
  while(1)
    {       //WriteSpi(a);  
            //a = 'a';
            LCD_GLASS_WriteChar(WriteSpi(a), POINT_ON, COLUMN_OFF,4);
            
            /*
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
            */
    }
}

uint8_t WriteSpi(uint8_t byte){
  //while(SPI->SPI1_SR & 0x80);
  //while(!(SPI->SPI1_SR & 0x02));
  SPI->SPI1_DR = byte;
  //while(!(SPI->SPI1_SR & 0x01));
  return SPI->SPI1_DR;  
}

void SPIMaster()
{
  /*config in/out*/
  PortCb->DDR.DDR5=1;    //SCK
  PortCb->DDR.DDR6=1;    //MOSI
  PortCb->DDR.DDR7=0;    //MISO
  PortEb->DDR.DDR5=1;    //NSS
  
  /*CR1*/
  SPI->SPI1_CR1 |= 0x40;        //set SPE enable SPI
  SPI->SPI1_CR1 |= 0x04;        //set MSTR at master
  
  /*CR2*/
  
  
}

void SPISlave()
{
  /*config in/out*/
  PortCb->DDR.DDR5=0;    //SCK
  PortCb->DDR.DDR6=0;    //MOSI
  PortCb->DDR.DDR7=1;    //MISO
  PortEb->DDR.DDR5=0;    //NSS
  
  /*CR1*/
  SPI->SPI1_CR1 |= 0x40;        //set SPE enable SPI
  SPI->SPI1_CR1 |= 0x00;        //set MSTR at slave
  /*CR2*/
}