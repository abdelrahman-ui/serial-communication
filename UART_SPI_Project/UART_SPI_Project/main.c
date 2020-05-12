/*
 * UART_SPI_Project.c
 *
 * Created: 5/8/2020 1:33:43 AM
 * Author : User™
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define BAUD   9600
#define BAUD_EQ		((F_CPU/(BAUD*16UL))-1)
char uartReceive();
void uartInit();
void uartSend(char data);

int main(void)

{
	void LCD_Init (void);
	uartInit();
	while (1)
	{
		uartSend('C');
		 unsigned char x=uartReceive();
		 LCD_Char('c');
	}
}

void uartInit(){
	//Select Baud Rate
	UBRRL=BAUD_EQ;
	//Enable RX and TX
	UCSRB =(1<<RXEN)|(1<<TXEN);
	//select frame size and number of stop bits
	UCSRC=(1<<URSEL)|(1<<UCSZ0) | (1<<UCSZ1);
}

void uartSend(char data){																	//Transmit
	
	while( !(UCSRA & (1<<UDRE)));
	UDR=data;
}

char uartReceive(){																			
	while( !(UCSRA & (1<<RXC)));
	return UDR;
}
void uart_sendString(char *str){
	char i=0;
	while(str[i]!='\0'){
		uartSend(str[i]);
		i++;
	}
}