/*
 * SPI_Salev_Polling.c
 *
 * Created: 5/6/2020 11:49:05 PM
 * Author : User™
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#define  SS		4
#define MOSI	5
#define MISO	6
#define LED0	2
unsigned char SPI_Transfer(unsigned char sendByte){
	
	SPDR =sendByte;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}
int main(void)
{
	DDRB|=(1<<MISO);
	DDRB&=~(1<<SS); //input pin
	DDRC|=(1<<LED0);
	
	SPCR|=(1<<SPE);

	while (1)
	{
		unsigned char recv=SPI_Transfer(0x55);
		_delay_ms(1000);
		if(recv==0xAA){
			PORTC^=(1<<LED0);
			_delay_ms(1000);
		}
	}
}


