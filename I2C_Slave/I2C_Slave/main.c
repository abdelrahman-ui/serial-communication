/*
 * I2C_Slave.c
 *
 * Created: 5/12/2020 2:02:13 AM
 * Author : User™
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


#define  LED_0  0
#define  LED_1  1
#define  LED_2  2

void I2C_init(unsigned char Slave_addr)
{
	TWAR=Slave_addr;
}
unsigned char I2C_Read_Data()
{
	TWCR=(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while((TWCR&(1<<TWINT))==0);
	while((TWCR&(0xf8))!=0x80);
}   
int main(void)
{
	DDRD|=(1<<LED_0)|(1<<LED_1)|(1<<LED_2);
	I2C_init(0x20);
    /* Replace with your application code */
    while (1) 
	
    {
		 unsigned char stutes=I2C_Read_Data();
		 switch(stutes)
		 {
			 case 'A':
				PORTD|=(1<<LED_0);
				_delay_ms(1000);
				break;
			case 'B':
				PORTD|=(1<<LED_1);
				_delay_ms(1000);
				break;	
			case 'C':
				PORTD|=(1<<LED_2);
				_delay_ms(1000);
				break;
		 }
		
    }
}

 