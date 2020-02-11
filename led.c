#include<avr/io.h>
#include<util/delay.h>

#define out PORTB
#define led 3

void main()
{
	DDRB|=(1<<led);
	DDRC=0xFF;
	
	while(1)
	 {
	   out|=(1<<led);
	   _delay_ms(1000);
	   out&=~(1<<led);
	   _delay_ms(1000);
     }
}

