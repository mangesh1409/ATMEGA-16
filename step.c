#include <avr/io.h>
#include <util/delay.h>

uint16_t t=50535;                   // time delay value for delay loop

void keydly()                             // key debounce delay
{
   uint8_t i;
   for(i=0; i<7;i++)

      _delay_loop_2(10000);             // delay loop library function with fixed delay

}

void incspeed()                 // increase speed of motor by

{

                PORTB = 0x00;

                if(t>20535) t=t-2000;                                       // decreasing time delay value if its min limit is

                if(t==20535) PORTB = 0x01;                         // not reached. For min limit give indication on LED3

}

void decspeed()                                                                               // decrease speed of motor by

{

                PORTB = 0x00;

                if(t<60535) t=t+2000;                                      // increasing time delay value if its max limit is not

                if(t==60535) PORTB = 0x02;                         // reached. For max limit give indication on LED4              

}

void clockwise()                                                                                // rotate motor clockwise

  {

                  while(PINA==0xFF)                                       // apply pulse sequence till no button is pressed

                                  {

                                                  PORTC=0x01;                   // apply pulse to 1st coil

                                                  _delay_loop_2(t);         // generate delay as per time delay value

                                                   PORTC=0x02;                  // apply pulse to next coil and like wise

                                                  _delay_loop_2(t);

                                                   PORTC=0x04;

                                                  _delay_loop_2(t);

                                                   PORTC=0x08;

                                                  _delay_loop_2(t);

                                  }           

  }

void anticlockwise()                                                        // rotate motor anti clockwise

  {

                  while(PINA==0x0F)                                       // apply pulse sequence till no button is pressed

                                 { 

                                                  PORTC=0x08;                   // apply pulse to last coil

                                                  _delay_loop_2(t);         // give delay as per time delay value

                                                   PORTC=0x04;                  // apply next pulses as per required sequence

                                                  _delay_loop_2(t);

                                                   PORTC=0x02;

                                                  _delay_loop_2(t);

                                                   PORTC=0x01;

                                                  _delay_loop_2(t);

                                  }                           

  }

int main(void)

{

    uint8_t r=0,d;                                                                                // run and direction flag

    DDRC=0xFF;                                                                   // initialize ports as input and output

                DDRB=0x03;

                DDRD=0x03;

                DDRA=0x00;

                PORTC=0x00;

                PORTB=0x00;

                PORTD=0x00;

    while(PINA==0xFF);                                                   // wait till no key is pressed

loop:switch(PINA)

                  {

                                  case 0xFE:                                         // for 1st key

                                                                keydly();              // give key debounce delay

                                                                r=1;                        // set run flag

                                                                d=0;                       // clear direction flag for CLK direction

                                                                clockwise();        // start rotating motor clock wise

                                                                break;

                                  case 0xFD:                                         // for 2nd key

                                                                keydly();              // key debounce delay

                                                                r=1;                        // set run flag

                                                                d=1;                       // set direction flag for ACLK direction

                                                                anticlockwise(); // start rotating motor anticlockwise

                                                                break;

                                  case 0xFB:                                         // for 3rd key

                                                                PORTC = 0x00;   // stop motor

                                                                r=0;                        // clear run flag

                                                                PORTB = 0x00;   // all indication off

                                                                break;

                                  case 0xF7:                                         // for 4th key

                                                                PORTD=0x01;     // give indication on  LED1

                                                                keydly();

                                                                PORTD=0x00;

                                                                incspeed();         // increase speed           

                                                                if(r==1)                 // if motor was running

                                                                  {

                                                                                if(d==0) clockwise();                       // check direction and

                                                                                else anticlockwise();                       // keep it running

                                                                  }

                                                                 break;

                                  case 0xEF:                                         // for 5th key

                                                                PORTD=0x02;     // indication on LED2

                                                                keydly();

                                                                PORTD=0x00;

                                                                decspeed();       // decrease speed

                                                                if(r==1)                 // if motor was running

                                                                  {

                                                                                if(d==0) clockwise();                       // check direction and

                                                                                else anticlockwise();                       // keep it running

                                                                  }

                                                                 break;                                 

                  }                                                              

      goto loop;                                                                     // continuous loop

}                         


