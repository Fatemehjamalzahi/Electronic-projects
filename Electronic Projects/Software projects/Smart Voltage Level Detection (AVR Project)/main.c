#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"
#include "Global.h"

/*
 * Smart Voltage Detection System
 * Author: Fatemeh Jamalzahi
 * Description: Reads analog voltage via ADC and controls LED
 */


void ADC_Init();

int ADC_Read(char Channel);

int main()
{
	char String[5];
	int value;
	float Value_finally;
	DDRB = (1<<PB0);
	ADC_Init();
	lcd_init(LCD_DISP_ON);
	lcd_puts("ADC :");
	
	while(1)
	{
		value = ADC_Read(0);
		Value_finally = (value / 4.88)/10;
		Value_finally *=6 ; 
		dtostrf(Value_finally , 3 , 2 , String);
		lcd_puts(String);
		_delay_ms(100);
		lcd_clrscr();
		
		if(Value_finally >= 10)
		{
			PORTB |= (1<<PB0);
		}
		else
		{
			PORTB &= ~(1<<PB0);
		}
	}
}
void ADC_Init(void)
{
	DDRA = 0x00;
	ADCSRA = 0x87;
	ADMUX = 0x40;
	
	
}
int ADC_Read(char Channel)
{
	int ADC_Value_High , ADC_Value_low ; 
	int ADC_Value_Total ;
	
	ADMUX = ADMUX | (Channel & 0x0F);
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA&(1<<ADIF))); //this command wait to flag be one 
	_delay_ms(10);
	
	ADC_Value_low = (int)ADCL ;
	ADC_Value_High = (int)ADCH *256;//low shift to high
	
	ADC_Value_Total = ADC_Value_High + ADC_Value_low;
	return ADC_Value_Total;
	
	
}
