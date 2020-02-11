#include<avr/io.h>
#include<util/delay.h>
#define sw 0

void main()
{
  unsigned char f[5]={0x05,0x06,0x0A,0x09};
  unsigned char r[5]={0x05,0x09,0x0A,0x06};
  int i,j;
  

  DDRD=0xFF;
  DDRC=0x00;
  

  while(1)
   { 
     if(PINC&(1<<sw))                          
       {
            for(i=0;i<=3;i++)
              {
                PORTD=f[i];    
               _delay_ms(100);
              }
       }

     else 
	    {
            for(j=0;j<=3;j++)
              {
                PORTD=r[j];    
                _delay_ms(00);
              }
          }

     }
}
