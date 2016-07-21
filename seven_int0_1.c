/*
 * sevenseg.c
 *
 * Created: 11/10/2014 8:49:26 PM
 *  Author: Administrator
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 12000000ul
#include<util/delay.h>
#define setbit(a,b)  a |= 1 << b
#define clrbit(a,b)  a &= ~(1 << b)
#define togbit(a,b)  a ^= 1 << b
 
void inits(void);
void seven_seg(unsigned char x);
unsigned char counter = 0;

int main(void)
{
	inits();
	sei();
    while(1)
    {
	    seven_seg(counter);   
		if (counter == 100)
		    counter = 0;
		if (counter == 255)
		    counter = 99;
    }
}

void inits(){
   DDRC = 0xff;
   MCUCR = 0x0f;
   GICR = 0xc0;
   PORTC = 0x00;
}
 
void seven_seg(unsigned char counter){
		unsigned char temp;
		
		temp = counter % 10;
		setbit(temp,4);
		clrbit(temp,5);
		PORTC = temp;
		
		_delay_ms(1);
		
		temp = counter / 10;
		setbit(temp,5);
		clrbit(temp,4);
		PORTC = temp;	
		
		_delay_ms(1);
}

ISR(INT0_vect){
	_delay_ms(40);
	counter++;
}

ISR(INT1_vect){
	_delay_ms(40);
	counter--;
}
