#include "FGAcoursestm8Lib.h" 

//Read chapter 6 page 57 datasheet stm8l152c6 to find out interupt vector number
_Pragma( "vector = 11" ) __interrupt void       //External interrupt 1 No9+2
ButtonInterupt( void )
{
  BlueOff;
  IRQ->EXTI_SR1 |= 0x02;;
}

_Pragma( "vector = 25" ) __interrupt void       //Timer 1 interupt No23+2
Timer1Interupt( void )
{
  PortCb->ODR.ODR7^=1;
  
  TIM1->TIM1_SR1 = ~0x01;
}