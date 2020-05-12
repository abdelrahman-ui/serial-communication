/*
 * UART_Recive_complet_interrupt.c
 *
 * Created: 5/6/2020 1:20:32 PM
 * Author : User™
 */ 

#define F_CPU	16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define BAUD 9600
#define BAUD_EQ		((F_CPU/(BAUD*16UL))-1)

 void uart_Init();
 void uartSend(char data);
 void uartSendString(char *str);
 unsigned char uartReceive();

 void uart_Init(){
	  //Initialize Baud rate
	  UBRRL=BAUD_EQ;
	  //TXEN and Receive
	  UCSRB=(1<<UDRIE)|(1<<TXEN)|(1<<RXEN);
	  //frame size 8 bis , no parity , one stop bit
	  UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
 }
 //uart send char
 void uartSend(char data){
	 //Send data
	 while(!(UCSRA&(1<<UDRE)));//polling
	 UDR=data;
 }
 //uart receive
 unsigned char uartReceive(){
	 //
	 while(!(UCSRA&(1<<RXC)));
	 return UDR;
 }
 //uart send string
void uartSendString(char *str){
	
	unsigned char i=0;
	while(str[i]!='\0'){
		uartSend(str[i]);	
		i++; 
	 }//while
}
volatile char send,send_flag;
int main(void){


	
   uart_Init();
	 sei();
	uartSendString("Welcome to Interfacing\r\n");	
	 char i=0;
    while (1) 
    {
		
		if(send_flag!=0)
		
//	unsigned char cmd = uartReceive();
	uartSendString("Robot Command\r\n");	
	
	_delay_ms(1000);
    }//while
}//main


ISR(USART_UDRE_vect){
	
	send_flag=1;
	UDR=send;
	
}

