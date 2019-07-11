#include "FGAcoursestm8Lib.h"

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
uint8_t t_bar[2]={0x0,0X0};

const uint16_t CapLetterMap[26]=
    {
        /* A      B      C      D      E      F      G      H      I  */
        0xFE00,0x6711,0x1d00,0x4711,0x9d00,0x9c00,0x3f00,0xfa00,0x0011,
        /* J      K      L      M      N      O      P      Q      R  */
        0x5300,0x9844,0x1900,0x5a42,0x5a06,0x5f00,0xFC00,0x5F04,0xFC04,
        /* S      T      U      V      W      X      Y      Z  */
        0xAF00,0x0411,0x5b00,0x18c0,0x5a84,0x00c6,0x0052,0x05c0
    };

/* Constant table for number '0' --> '9' */
const uint16_t NumberMap[10]=
    {
        /* 0      1      2      3      4      5      6      7      8      9  */
        0x5F00,0x4200,0xF500,0x6700,0xEa00,0xAF00,0xBF00,0x04600,0xFF00,0xEF00
    };


void LCD_GLASS_Init(void);
void LCD_GLASS_Clear(void);
void display_lcd();

void LCD_GLASS_WriteChar(uint8_t* ch, uint8_t point, uint8_t column, uint8_t position);
void LCD_Conv_Char_Seg(uint8_t* c,uint16_t point,uint8_t column, uint8_t* digit);
void LCD_bar();

void main( void ) 
{
  SetupLed;
  SetupUserButton; 
  SetupClock;
  SetupTimer1;
  __enable_interrupt();
  LCD_GLASS_Init();
  LCD_GLASS_Clear();
  uint8_t a= 51;
  while(1){
    LCD_GLASS_WriteChar(&a, POINT_OFF, COLUMN_OFF,1);
  }
  while(1)
    { 
      //display_lcd();
      /*
      for (a=65;a<=97;a++)
        {
      LCD_GLASS_WriteChar(&a, POINT_OFF, COLUMN_OFF,1);
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
      }*/
            for (a=48;a<=57;a++)
        {
      LCD_GLASS_WriteChar(&a, POINT_OFF, COLUMN_OFF,1);
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
      }
      /*
      GreenOn;
      delay(60000);
      delay(60000);
 
      GreenOff;
      delay(60000);
      delay(60000);*/
    }
}

void LCD_GLASS_Init(void)
{
	/* LCD used clock RTC/2 
     => We have to enable clock RTC first */
  /* Enable LCD/RTC clock */
  //CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
  //CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);
  Clock->CLK_PCKENR2 |= 0x04;
  Clock->CLK_PCKENR2 |= 0x08;
  /*
  #ifdef USE_LSE
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
  #else
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
  #endif
  */
  /* Initialize the LCD */
 /* LCD_Init(LCD_Prescaler_1, LCD_Divider_31, LCD_Duty_1_4, 
                                   LCD_Bias_1_3, LCD_VoltageSource_Internal);*/
  
  LCD->LCD_FRQ &= ~(0xF0);
  LCD->LCD_FRQ |= 0x00;
  LCD->LCD_FRQ &= ~(0x0F);
  LCD->LCD_FRQ |= 0x0F;
  
  LCD->LCD_CR1 &= ~(0x06);
  LCD->LCD_CR1 |= 0x06;
  
  LCD->LCD_CR1 &= ~(0x01);
  LCD->LCD_CR1 |= 0x00;
  
  LCD->LCD_CR2 &= ~(0x01);
  LCD->LCD_CR2 |= 0x00;
  /* Mask register
  For declare the segements used.
  in the Discovery we use 0 to 23 segments. */
  //LCD_PortMaskConfig(LCD_PortMaskRegister_0, 0xFF);
  LCD->LCD_PM0 =  0xFF;

  //LCD_PortMaskConfig(LCD_PortMaskRegister_1, 0xFF);
  LCD->LCD_PM1 =  0xFF;
  
  //LCD_PortMaskConfig(LCD_PortMaskRegister_2, 0xff);
  LCD->LCD_PM2 =  0xFF;
  
  /* To set contrast to mean value */
  //LCD_ContrastConfig(LCD_Contrast_3V0);
  LCD->LCD_CR2 &= (uint8_t)(~(0x0E)); /* Clear the contrast bits  */
  LCD->LCD_CR2 |= 0x08; /* Select the maximum voltage value Vlcd */
  
  //LCD_DeadTimeConfig(LCD_DeadTime_0);
  
  LCD->LCD_CR3 &= (uint8_t)(~(0x07));  /* Clear the dead time bits  */

  LCD->LCD_CR3 |= 0x00;
  
  //LCD_PulseOnDurationConfig(LCD_PulseOnDuration_1);
  
  LCD->LCD_CR2 &= (uint8_t)(~(0xef)); /* Clear the pulses on duration bits */
  LCD->LCD_CR2 |= 0x20;
  
  /* Enable LCD peripheral */ 
  //LCD_Cmd(ENABLE);
  
  LCD->LCD_CR3 |= 0x40;
}

void LCD_GLASS_Clear(void)
{
  LCD->LCD_RAM0 = 0x00;
  LCD->LCD_RAM1 = 0x00;
  LCD->LCD_RAM2 = 0x00;
  LCD->LCD_RAM3 = 0x00;
  LCD->LCD_RAM4 = 0x00;
  LCD->LCD_RAM5 = 0x00;
  LCD->LCD_RAM6 = 0x00;
  LCD->LCD_RAM7 = 0x00;
  LCD->LCD_RAM8 = 0x00;
  LCD->LCD_RAM9 = 0x00;
  LCD->LCD_RAM10 = 0x00;
  LCD->LCD_RAM11 = 0x00;
  LCD->LCD_RAM12 = 0x00;
  LCD->LCD_RAM13 = 0x00;
}

void display_lcd()
{    
        uint8_t count1=0,count2=0,count3=0,count4=0;
        count1= count/1000 + 0x30;
        count2= count%1000/100 + 0x30 ;
        count3= count%100/10 + 0x30 ;
        count4= count%10 + 0x30;
     
        LCD_GLASS_WriteChar(&count1, POINT_ON, COLUMN_ON,1);
        LCD_GLASS_WriteChar(&count2, POINT_OFF, COLUMN_OFF,2);
        LCD_GLASS_WriteChar(&count3, POINT_OFF, COLUMN_OFF,3);
        LCD_GLASS_WriteChar(&count4, POINT_OFF, COLUMN_OFF,4); 
        LCD_GLASS_WriteChar(&count4, POINT_OFF, COLUMN_OFF,5); 
        LCD_GLASS_WriteChar(&count4, POINT_OFF, COLUMN_OFF,6);
        LCD_bar();
} 

void LCD_bar()
{
/* bar0 bar2 */
  LCD->LCD_RAM11 &= 0x5f;
  LCD->LCD_RAM11 |= t_bar[0]&0xa0;
  
/*bar1 bar3 */
  LCD->LCD_RAM8 &= 0xf5;
  LCD->LCD_RAM8 |= t_bar[1]&0x0a;
}


void LCD_GLASS_WriteChar(uint8_t* ch, uint8_t point, uint8_t column, uint8_t position)
{
  uint8_t digit[4];     /* Digit frame buffer */

/* To convert displayed character in segment in array digit */
  LCD_Conv_Char_Seg(ch,point,column,digit);

  switch (position)
  {
    /* Position 1 on LCD (Digit1)*/
    case 1:
      {
      LCD->LCD_RAM0 &= 0x0fc;
      LCD->LCD_RAM0 |= (uint8_t)(digit[0]& 0x03); // 1M 1E	
      
      LCD->LCD_RAM2 &= 0x3f;
      LCD->LCD_RAM2 |= (uint8_t)((digit[0]<<4) & 0xc0); // 1G 1B
    
      LCD->LCD_RAM3 &= 0x0cf;
      LCD->LCD_RAM3 |= (uint8_t)(digit[1]<<4 & 0x30); // 1C 1D
                                                                                                                                      
      LCD->LCD_RAM6 &= 0xf3;
      LCD->LCD_RAM6 |= (uint8_t)(digit[1]&0x0c); // 1F 1A
      
      LCD->LCD_RAM7 &= 0x0fc;
      LCD->LCD_RAM7 |= (uint8_t)(digit[2]&0x03); // 1Col 1P		
      
      LCD->LCD_RAM9 &= 0x3f;
      LCD->LCD_RAM9 |= (uint8_t)((digit[2]<<4) & 0xc0); // 1Q 1K										
      
      LCD->LCD_RAM10 &= 0xcf;
      LCD->LCD_RAM10 |= (uint8_t)((digit[3]<<2)& 0x30); // 1DP 1N	
                                                                                                                                      
      LCD->LCD_RAM13 &= 0xf3;
      LCD->LCD_RAM13 |= (uint8_t)((digit[3]<<2) & 0x0c); // 1H 1J
      break;
    }
    /* Position 2 on LCD (Digit2)*/
    case 2:
      {
      LCD->LCD_RAM0 &= 0x0f3;
      LCD->LCD_RAM0 |= (uint8_t)((digit[0]<<2)&0x0c); // 2M 2E	
      
      LCD->LCD_RAM2 &= 0xcf;
      LCD->LCD_RAM2 |= (uint8_t)((digit[0]<<2)&0x30); // 2G 2B
      
      LCD->LCD_RAM3 &= 0x3f;
      LCD->LCD_RAM3 |= (uint8_t)((digit[1]<<6) & 0xc0); // 2C 2D
      
      LCD->LCD_RAM6 &= 0xfc;
      LCD->LCD_RAM6 |= (uint8_t)((digit[1]>>2)&0x03); // 2F 2A
      
      LCD->LCD_RAM7 &= 0xf3;
      LCD->LCD_RAM7 |= (uint8_t)((digit[2]<<2)& 0x0c); // 2Col 2P		
      
      LCD->LCD_RAM9 &= 0xcf;
      LCD->LCD_RAM9 |= (uint8_t)((digit[2]<<2)&0x30); // 2Q 2K										
      
      LCD->LCD_RAM10 &= 0x3f;
      LCD->LCD_RAM10 |= (uint8_t)((digit[3]<<4)& 0xC0); // 2DP 2N	
      
      LCD->LCD_RAM13 &= 0xfc;
      LCD->LCD_RAM13 |= (uint8_t)((digit[3])& 0x03); // 2H 2J
      break;
    }
    /* Position 3 on LCD (Digit3)*/
    case 3:
      {
      LCD->LCD_RAM0 &= 0xcf;
      LCD->LCD_RAM0 |= (uint8_t)(digit[0]<<4) & 0x30; // 3M 3E	
      
      LCD->LCD_RAM2 &= 0xf3;
      LCD->LCD_RAM2 |= (uint8_t)(digit[0]) & 0x0c; // 3G 3B
      
      LCD->LCD_RAM4 &= 0xfc;
      LCD->LCD_RAM4 |= (uint8_t)(digit[1]) & 0x03; // 3C 3D
      
      LCD->LCD_RAM5 &= 0x3f;
      LCD->LCD_RAM5 |= (uint8_t)(digit[1]<<4) & 0xc0; // 3F 3A
                                                                                                                                      
      LCD->LCD_RAM7 &= 0xcf;
      LCD->LCD_RAM7 |= (uint8_t)(digit[2]<<4)&0x30; // 3Col 3P		
                                                                                                                                      
      LCD->LCD_RAM9 &= 0xf3;
      LCD->LCD_RAM9 |= (uint8_t)(digit[2]) & 0x0C;  // 3Q 3K										
      
      LCD->LCD_RAM11 &= 0xfc;
      LCD->LCD_RAM11 |= (uint8_t)(digit[3]>>2) & 0x03 ; // 3DP 3N	
                                                                                                      
      LCD->LCD_RAM2 &= 0x3f;
      LCD->LCD_RAM12 |= (uint8_t)(digit[3]<<6) & 0xc0; // 3H 3J
      break;
    }
    /* Position 4 on LCD (Digit4)*/
    case 4:
      {
      LCD->LCD_RAM0 &= 0x3f;
      LCD->LCD_RAM0 |= (uint8_t)(digit[0]<<6) & 0xc0; // 4M 4E	
      
      LCD->LCD_RAM2 &= 0xfc;
      LCD->LCD_RAM2 |= (uint8_t)(digit[0]>>2) & 0x03; // 4G 4B
      
      LCD->LCD_RAM4 &= 0xf3;
      LCD->LCD_RAM4 |= (uint8_t)(digit[1]<<2) & 0x0C; // 4C 4D
      
      LCD->LCD_RAM5 &= 0xcf;
      LCD->LCD_RAM5 |= (uint8_t)(digit[1]<<2) & 0x30; // 4F 4A
                                                                                                                                      
      LCD->LCD_RAM7 &= 0x3f;
      LCD->LCD_RAM7 |= (uint8_t)(digit[2]<<6) & 0xC0; // 4Col 4P		
    
      LCD->LCD_RAM9 &= 0xfc;				
      LCD->LCD_RAM9 |= (uint8_t)(digit[2]>>2) & 0x03 ; // 4Q 4K										
    
      LCD->LCD_RAM11 &= 0xf3;				
      LCD->LCD_RAM11 |= (uint8_t)(digit[3]) & 0x0C; // 4DP 4N	
    
      LCD->LCD_RAM12 &= 0xcf;				
      LCD->LCD_RAM12 |= (uint8_t)(digit[3]<<4) & 0x30; // 4H 4J
      break;
      }
    /* Position 5 on LCD (Digit5)*/
    case 5:
      {
      LCD->LCD_RAM1 &= 0xfc;
      LCD->LCD_RAM1 |=  (uint8_t)(digit[0]) & 0x03; // 5M 5E	
      
      LCD->LCD_RAM1 &= 0x3f;
      LCD->LCD_RAM1 |=  (uint8_t)(digit[0]<<4) & 0xc0; // 5G 5B
    
      LCD->LCD_RAM4 &= 0xcf;				
      LCD->LCD_RAM4 |= (uint8_t)(digit[1]<<4) & 0x30; // 5C 5D
    
      LCD->LCD_RAM5 &= 0xf3;				
      LCD->LCD_RAM5 |=  (uint8_t)(digit[1]) & 0x0c; // 5F 5A
    
      // 5 DP 5 COL not used
      
      LCD->LCD_RAM8 &= 0xfe;
      LCD->LCD_RAM8 |=  (uint8_t)(digit[2]) & 0x01; //  5P	
      
      LCD->LCD_RAM8 &= 0x3f;					
      LCD->LCD_RAM8 |=  (uint8_t)(digit[2]<<4) & 0xc0; // 5Q 5K										
    
      LCD->LCD_RAM11 &= 0xef;				
      LCD->LCD_RAM11 |=  (uint8_t)(digit[3]<<2) & 0x10; // 5N	
    
      LCD->LCD_RAM12 &= 0xf3;				
      LCD->LCD_RAM12 |=  (uint8_t)(digit[3]<<2) & 0x0C; // 5H 5J
      break;
      }
    /* Position 6 on LCD (Digit6)*/
    case 6:
      {
      LCD->LCD_RAM1 &= 0xf3;
      LCD->LCD_RAM1 |=  (uint8_t)(digit[0]<<2) & 0x0C; // 6M 6E	
    
      LCD->LCD_RAM1 &= 0xcf;				
      LCD->LCD_RAM1 |=  (uint8_t)(digit[0]<<2) & 0x30; // 6G 6B
    
      LCD->LCD_RAM4 &= 0x3f;				
      LCD->LCD_RAM4 |= (uint8_t)(digit[1]<<6) & 0xc0; // 6C 6D
    
      LCD->LCD_RAM5 &= 0xfc;				
      LCD->LCD_RAM5 |=  (uint8_t)(digit[1]>>2) & 0x03; // 6F 6A
      
      LCD->LCD_RAM8 &= 0xfb;
      LCD->LCD_RAM8 |=  (uint8_t)(digit[2]<<2) & 0x04; //  6P	
      
      // 6 DP 6COL not used
      LCD->LCD_RAM8 &= 0xcf;					
      LCD->LCD_RAM8 |=  (uint8_t)(digit[2]<<2) & 0x30; // 6Q 6K	
    
      LCD->LCD_RAM11 &= 0xbf;				
      LCD->LCD_RAM11 |=  (uint8_t)(digit[3]<<4) & 0x40; // 6N	
    
      LCD->LCD_RAM12 &= 0xfc;				
      LCD->LCD_RAM12 |= (uint8_t)(digit[3]) & 0x03; // 6H	6J
      break;
      }
      default:
        {
              break;
              }
              }
}
 
void LCD_Conv_Char_Seg(uint8_t* c,uint16_t point,uint8_t column, uint8_t* digit)
{
  uint16_t ch = 0;
  uint8_t i,j;
  
  switch (*c)
    {
    case ' ': 
      {
      ch = 0x00;
      break;
      }
    
    case '*':
      {
      ch = star;
      break;
      }
    case 'µ' :
      {
        ch = C_UMAP;
        break;
      }
           
    case 'm' :
      {
        ch = C_mMap;
        break;
      }
    case 'n' :
      {
        ch = C_nMap;
        break;	
      }
                  
    case '-' :
      {
      ch = C_minus;
      break;
      }
                  
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      {
      ch = NumberMap[*c-0x30];		
      break;
      }
          
    default:
      {
      /* The character c is one letter in upper case*/
      if ( (*c < 0x5b) && (*c > 0x40) )
      {
        ch = CapLetterMap[*c-'A'];
      }
      /* The character c is one letter in lower case*/
      if ( (*c <0x7b) && ( *c> 0x60) )
      {
        ch = CapLetterMap[*c-'a'];
      }
      break;
      }
  }
       
  /* Set the digital point can be displayed if the point is on */
  if (point)
  {
    ch |= 0x0008;
  }

  /* Set the "COL" segment in the character that can be displayed if the column is on */
  if (column)
  {
    ch |= 0x0020;
  }		

  for (i = 12,j=0 ;j<4; i-=4,j++)
  {
    digit[j] = (ch >> i) & 0x0f; //To isolate the less signifiant dibit
  }
}
