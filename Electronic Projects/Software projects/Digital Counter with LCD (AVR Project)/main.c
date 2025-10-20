#define F_CPU 8000000UL
#define Button PB0



/*
 * digital counter with lcd
 * Author: Fatemeh Jamalzahi
 */


#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#include <stdio.h>


int Counter = 0;
char Counter_String[10];
void Timer_Config(void);


int main(void)
{	
	
	DDRB &= ~(1<<Button);
	PORTB |= (1<<Button);
	lcd_init(LCD_DISP_ON);
    
    while (1) 
	
    {	
		
		
		
		if((PINB &(1<<Button))==0) //æä Ï˜ãå æÑæÏ? åÓÊ Èå ÕæÑÊ ?ä ÊÚÑ?Ý ã?Ôå¡ äå æÑÊ
		//˜Ï ÈÇáÇ ÇÈÊÏÇ ÎÑæÌ? äã?ÏÇÏ æä ÊÞÏã ÚãáÑ åÇ ÑÚÇ?Ê äã?ÔÏ
		{
			Counter++;
			sprintf(Counter_String , "%d" , Counter);
			lcd_puts(Counter_String);
			_delay_ms(400);
			lcd_clrscr();
			while((PINB &(1<<Button))==0);
		}
	}
}

void Timer_Config(void)
{
	TCCR0 = (1<<CS02)|(1<<CS01)|(1<<CS00);//counter mode
}





