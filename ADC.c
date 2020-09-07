/*
 * ADC.c
 *
 * Created: 1/26/2020 11:42:21 PM
 *  Author: Ahmed
 */ 




#include <inttypes.h>
#include "ADC.h"
#include "std_macros.h"
void ADC0_init(){
	ADCSRA=0X87;
	ADMUX=0XE0;
}
uint8_t ADC_Read(){
	ADCSRA|=(1<<ADSC);
	while((ADCSRA&(1<<ADIF))==0);
	return ADCH;
}
