#include<avr/io.h>
#include<util/delay.h>

void main()
{ 
  ;DDRD=0xFF;
  
   unsigned int a[10]={0x3F,0x06,0x5B,0x4F,0x66,
   						0x6D,0x7D,0x07,0x7F,0x6F},i;//FOR CC DISPLAY  
  
  while(1)
  {
    for(i=0;i<=9;i++)
     {
	     PORTD=a[i];
		 _delay_ms(2000);
	 }
  }
}
