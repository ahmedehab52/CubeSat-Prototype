/*
 * sat_uart.c
 *
 * Created: 1/23/2020 4:08:23 PM
 * Author : Ahmed
 */ 

#include "GPIO.h"
#include "UARTt.h"
#include "command.h"
#include "ADC.h"
#include <avr/interrupt.h>
#include <stdio.h>

#ifndef F_CPU
#define F_CPU    (16000000UL)
#endif  // F_CPU


u8 command_rec[14];
u8 telemetry[21]={0x00,0x01,0x00,0x10};
u8 ADCS_comm[7];
u8 ack[3]={0x00,0XAC,0x00};
u8 Nack[3]={0x00,0xA0,0x00};
volatile u8 x;

ISR(USART_RXC_vect)
{
	SerialReceive(command_rec,14);
	x++;	
}



int main(void)
{ 	
   GPIO_voidInit();
  // GPIO_u8_WritePinDir(0,0, 'A'); // PA0 ---> input  (ADC0)
  	GPIO_u8_WritePinDir(3,1,'d') ;   // relay

   I2C_Master_Init();
   USART_init();
   ADC0_init();
   LCD_Init();
   ds3231_init();
   
   sei();        
  
   char Temperature[10];
   rtc_t rtc_read,rtc; 
   temp_data *temp;
   u8 y=0,true_comm =0,false_comm=0;
   x=0;
	while (1)
     {
		 if (x==1)
		 {
			
		   if(getCRC(command_rec,13)==command_rec[13])
		   {
			   true_comm++;
			   SerialTransmit(ack,3);
			   
			   if(command_rec[0]==0x0A)
			   {
				   ADCS_command(command_rec,ADCS_comm,telemetry);
			   }
			   
			   else if ( (command_rec[0]==0x2A) && (command_rec[1]==0x0F) )
			   {
				   // set RTC
				    
				   		  DELAY_MS(500) ;
				   		  Set_RTC(command_rec,&rtc);
				   		  DELAY_MS(500);
						  display_RTC(&rtc_read);
					  
			   }
			   
			   else if ( (command_rec[0]==0x2A) && (command_rec[1]==0x0A) )
			   {
				   // get temperature
			//	   get_temp(&temp,Temperature,telemetry);
			   }
			   //	 reset_buffer(command_rec);
		   }
		
		   
		   else
		   {
			   //ERROR
			   
			   SerialTransmit(Nack,3);
			   false_comm++;
			   if (false_comm==3)
			   {
				   Emergency_mode();
			   }
		   }
		   
		   x=0;
	   }
     }
	
}
