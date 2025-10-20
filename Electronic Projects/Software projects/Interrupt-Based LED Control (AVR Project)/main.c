#define F_CPU 8000000UL
#define Button PB0
#define LED_Pin PD4

/*
 * Interrupt based led control
 * Author: Fatemeh Jamalzahi
 */

#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#include <stdio.h>



void Pin_Config(void);
void Delay_10ms(void);
int main(void)
{	
	
    Pin_Config();
    
    while (1) 
	
    {	
		
		PORTD |= (1<<LED_Pin);
		Delay_10ms();
		PORTD &= ~(1<<LED_Pin);
		Delay_10ms();
		
		
	}
}

void Pin_Config(void)
{
	DDRD |= (1<<LED_Pin);
	PORTD &= ~(1<<LED_Pin);
}
void Delay_10ms(void)
{
	TCNT0 = 179;//start counting 
	TCCR0 = (1<<CS02)|(1<<CS00);
	while((TIFR&(1<<TOV0))==0);//untill of counter is counting
	TCCR0=0;//stop timer
	TIFR |= (1<<TOV0);//ãÞÏÇÑ Ýá ÑÇ Èå ÕæÑÊ ÏÓÊ? ÕÝÑ ã?˜ä?ã
	//Ï?ÊÇ Ô?Ê ã?å ÈÑÇ? ÕÝÑ ˜ÑÏä ãÞÏÇÑ ÈÇ?Ï ãÞÏÇÑ ?˜ ÈÏ?ã ÊÇ Ñ?ÓÊ ÈÔå
}


