/*
 * UART_polling.c
 *
 * Created: 5/5/2020 8:16:38 AM
 * Author : Abdelrahman ™
 - Normal Mode 
 - Boat Rate =9600 At 16000000 HZ
 - 8 Bit Fram Size
 - TXEN enable Transmit Enable
 - Recive Enable 
 - Send data UDR
 - No parity 
 - One Stop bit 
 
 */
#define F_CPU 16000000 
#include <avr/io.h>
#include <util/delay.h>


#define BAUD 9600
#define Equation_BAUD ((F_CPU/(16UL*BAUD))-1)

void UART_init();
void UART_Send(char data);
unsigned char UART_Recive();
void UART_Send_String(char *str);

int main(void)
{
	UART_init();
	 
	UART_Send_String("Hallo from mcr \r\n");
    while (1) 
    {
		UART_Send_String("Hallo from mcr \r\n");
		// unsigned char var =UART_Recive();
		/*if the recive (cmd =='W')
		{
			forword();
		}
		*/
		/*UART_Send_String("A\r\n");
		_delay_ms(1000);*/
    }
}




void UART_init()
{
	UBRRL=103;//Equation_BAUD;																//Speed or Broud    ==103
	// Normal Mode  A_syncro
	UCSRB |=(1<<TXEN);																	// Transmit Enable
	UCSRB |=(1<<RXEN)|(1<<RXCIE);																	// Reciver Enable
	UCSRC |=(1<<URSEL);																	// Use UCSRC not UBRRH The Two Have The Addres
	//UCSRC &=~(1<<UMSEL);														    	// A_Syncchronous Mode
	UCSRC |=(1<<UPM1)|(1<<UPM0);														// Disabled Parity
	//UCSRC&=~(1<<USBS);																// One Stop Bit
	
	//Size Equal 8 Bit From UCSRC & UCSRC
	//UCSRB&=~(1<<UCSZ2);
	UCSRC|=(1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL);
}



void UART_Send(char data)
{
	//Send Data
	//Frist check Register Embty or no To send Data
	while(!(UCSRA&(1<<UDRE)))		;						//Polling				//From data if UDRE =1 Is Embety
	UDR=data;
}


unsigned char UART_Recive()
{
	//return When Recive Is complet
	while(!(UCSRA&(1<<RXC)));
	return UDR;
}

void UART_Send_String(char *str)
{
	unsigned char i=0;
	while(str[i]!='\0')
	{
		UART_Send(str[i]); 
		i++;
	}
}