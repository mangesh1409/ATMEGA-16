#include<avr/io.h>
#include<util/delay.h>

#define ctrl PORTB
#define data PORTD
#define rs 0           //rs=RB0
#define en 1           //en=RB1

void lcd_cmd(unsigned int);
void lcd_data(unsigned int);
void lcd_init(void);
void conversion();

void lcd_init(void)
{
  	lcd_cmd(0x38);
  	lcd_cmd(0x06);
  	lcd_cmd(0x01);
  	lcd_cmd(0x0E);
  	lcd_cmd(0x80);
}

void lcd_cmd(unsigned int x)
{
  	data=x;
  	ctrl&=~(1<<rs);     //clear rs
  	ctrl|=(1<<en);      //set en
  	_delay_ms(100);
  	ctrl&=~(1<<en);     //clear en   
  	_delay_ms(100);
} 

void lcd_data(unsigned int y)
{
   	data=y;
  	ctrl|=(1<<rs);     //set rs
  	ctrl|=(1<<en);     //set en
  	_delay_ms(100);
  	ctrl&=~(1<<en);
  	_delay_ms(100);    //clear en
}

void conversion()
{  
   	signed int a,b,c,d,e,f,m;

	m=ADCW;
	m=m*4.90*10;
	
	a=m/1000;
	b=m%1000;
	c=b/100;
	d=b%100;
	e=d/10;
	f=d%10;
    
	lcd_cmd(0xC5);
	lcd_data(a+0x30);
	lcd_data(c+0x30);
	lcd_data('.');
	lcd_data(e+0x30);
	lcd_data(f+0x30);
	lcd_data('C');
}

void main()
{  
    DDRB=0xFF;
    DDRD=0xFF;
	DDRA=0x00;
	
	ADMUX=0x40;
	ADCSRA=0x80;

    unsigned char a[]={"ADC Reading"};
	unsigned char b[]={"Temp="};
	int i,j;

	lcd_init();
    _delay_ms(100);

    lcd_cmd(0x80);
	  for(i=0;i<=10;i++)
	    {
		   lcd_data(a[i]);
			_delay_ms(10);
        }
    
	lcd_cmd(0xC0);
	  for(j=0;j<=5;j++)
	    {
		  lcd_data(b[j]);
        }
		   
	while(1)
	 {
	    ADCSRA|=(1<<ADSC);                //start conversion
	    while((ADCSRA&(1<<ADIF))==0);     //wait for conversion
		conversion();
	 }
}	
