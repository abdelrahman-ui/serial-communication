/*
 * SPI_1.c
 *
 * Created: 5/6/2020 5:06:32 PM
 * Author : User™
 - MOode 0
 - SPEED 1 MHZ
 - POLLING
 
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> 

#define MOSI 5
#define MISO 6
#define CS  0                                      //WHICH SELECT SS
#define SCK 7
#define LED 2
#define ss_Enable() PORTC&=~(1<<CS)
#define ss_Disable() PORTC|=(1<<CS)
void init_spi();
unsigned char spi_transfar(unsigned char send_byte);

int main(void)
{
   init_spi();
    while (1) 
    {
	      	ss_Enable();
		 		unsigned char recv_byte= spi_transfar(0XAA); // b3at data
				 ss_Disable();
				 _delay_ms(1000);
				 if (recv_byte==0x55)
				 {
					 PORTC^=(1<<LED);
					 _delay_ms(1000);
				 }
				 
				 
				 
				 
    }
}

 void init_spi()
 {
	 //Dirication 
	DDRB|=(1<<MOSI)|(1<<SCK);
	//which i control 
	DDRC|=(1<<LED)|(1<<CS);
	//speed , mode ,work ass Master ,DATA ORDER (MSB)
	SPCR|=(1<<SPE)|(1<<SPR0)|(1<<MSTR)	;
 
 
 }
 unsigned char spi_transfar(unsigned char send_byte)
 {
	 
	 // from mean take data and but it at data reg
	 SPDR=send_byte;
	 while(!(SPSR&(1<<SPIF)));
	 return SPDR;
 }