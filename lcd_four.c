#include<avr/io.h>
#include<util/delay.h>

#define ctrl PORTB
#define data PORTD
#define rs 0           //rs=RB0
#define en 1           //en=RB1

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_init(void);


void lcd_init(void)
{
	lcd_cmd(0x02);
  	lcd_cmd(0x28);
  	lcd_cmd(0x06);
  	lcd_cmd(0x01);
  	lcd_cmd(0x0E);
  	lcd_cmd(0x80);
}

void lcd_cmd(unsigned char x)
{ 	
	char a;
	a=x;
  	data=(a>>4)&0x0F;
  	ctrl&=~(1<<rs);     //clear rs
  	ctrl|=(1<<en);      //set en
  	_delay_ms(1);
  	ctrl&=~(1<<en);     //clear en   
  	_delay_ms(50);

	data=a&0x0F;
	ctrl&=~(1<<rs);     //clear rs
  	ctrl|=(1<<en);      //set en
  	_delay_ms(1);
  	ctrl&=~(1<<en);     //clear en   
  	_delay_ms(50);
} 

void lcd_data(unsigned char y)
{
	char b;
	b=y;
   	data=(b>>4)&0x0F;;
  	ctrl|=(1<<rs);     //set rs
  	ctrl|=(1<<en);     //set en
  	_delay_ms(1);
  	ctrl&=~(1<<en);
  	_delay_ms(50);   //clear en

	data=b&0x0F;;
  	ctrl|=(1<<rs);     //set rs
  	ctrl|=(1<<en);     //set en
  	_delay_ms(1);
  	ctrl&=~(1<<en);
  	_delay_ms(50);   //clear en
}



void main()
{  
    unsigned char a[]={"LCD.."};
	int i;

    DDRB=0xFF;
    DDRD=0xFF;

	lcd_init();
    _delay_ms(10);

	
     {   
        lcd_cmd(0x80);
		for(i=0;i<=4;i++)
	    {
		   lcd_data(a[i]);
			_delay_ms(100);
        }
     }
	while(1);


	/*unsigned char a[]={"Ferguson College"};
	unsigned char b[]={"Pune!"};
	unsigned char c[]={"Welcomes You!"};
	unsigned char d[]={"..MJ"};
    int i,j,k,l;

	lcd_init();
    _delay_ms(50);

    while(1)
     {   
        lcd_cmd(0x80);
		for(i=0;i<=15;i++)
	    {
		   lcd_data(a[i]);
			_delay_ms(100);
        }
	    
		lcd_cmd(0xC6);
		for(j=0;j<=4;j++)
	    {
		   lcd_data(b[j]);
			_delay_ms(100);
        }		
		_delay_ms(5000);
		lcd_cmd(0x01); 
		
		lcd_cmd(0x80);
		for(k=0;k<=12;k++)
	    {
		   lcd_data(c[k]);
			_delay_ms(100);
        }
	    
		lcd_cmd(0xCB);
		for(l=0;l<=4;l++)
	    {
		   lcd_data(d[l]);
			_delay_ms(100);
        }		
		_delay_ms(3000);
		lcd_cmd(0x01);

    }*/
}
