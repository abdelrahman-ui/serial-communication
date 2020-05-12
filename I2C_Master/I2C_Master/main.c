/*
 * I2C_Master.c
 *
 * Created: 5/9/2020 5:08:37 PM
 * Author : User™
	-Master transmeter send 
	Send start condition 
	chech twint 
	check statues
	write
	chech twint
	check statues
	load data 
	chech twint
	check statues
	bit rate 100 khz
 */ 
#include "math.h"
#define  F_CPU 16000000UL
#define SCL_FRE100K 100000UL                                                    //The ferq which i need to work in
#define BIT_RATE(TWSR) ((F_CPU/SCL_FRE100K)/(16+2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))) //from data sheet
#include <avr/io.h>
#include <util/delay.h>

#define IN_PUT_PIN_0 0
#define IN_PUT_PIN_1 1
#define IN_PUT_PIN_2 2
void I2C_init()
{
	TWBR=0X00;											//Clear the last one
	TWBR= 0x0c  ;                                  // BIT_RATE(TWSR);									//set 
	
}
void I2C_Start()
{ //send start 
	TWCR=(1<<TWINT)	|(1<<TWSTA)|(1<<TWEN);								//make flag =0,tw_Enable , init bit start @Control Res
	//check at TWINT
	while(!(TWCR&(1<<TWINT)));
	//chechk statues code srom data sheet 
	while((TWSR&0xf8)!=0x08);																//mabd2yan 2wel 3 bit m4 mohemen f h3mel & m3 0xf8
	
}
void I2C_slave_addr(unsigned char addr)
{
	//Clear TWINT
	TWCR=(1<<TWINT)|(1<<TWEN);
	TWDR=addr;
	//check at TWINT
	while(!(TWCR&(1<<TWINT)));
	//chechk statues code srom data sheet
	while((TWSR&0xf8)!=0x18);
}
void I2C_Send_data(unsigned char data)
{
 //Clear TWINT&EN
 TWCR=(1<<TWINT)|(1<<TWEN);
 //send data
 TWDR=data; 
 //check at TWINT
 while(!(TWCR&(1<<TWINT)));
 //chechk statues code srom data sheet
 while((TWSR&0xf8)!=0x28);
}
void I2C_STOP()
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	//check at TWINT
	while(!(TWCR&(1<<TWINT)));
	
}

int main(void)
{
	DDRA&=~(1<<IN_PUT_PIN_0);
	DDRA&=~(1<<IN_PUT_PIN_1);
	DDRA&=~(1<<IN_PUT_PIN_2);
	I2C_init();
    /* Replace with your application code */
    while (1) 
    {
		I2C_Start();
		_delay_ms(100);
		I2C_slave_addr(0x20);									//2NA EL B7DED EL ADDR
		_delay_ms(100);
		 if(PINA&(1<<IN_PUT_PIN_0))
		{
		    I2C_Send_data('A');										//SEND
		   _delay_ms(100);
		    I2C_STOP();
		   _delay_ms(100);
		}
		else if(PINA&(1<<IN_PUT_PIN_1))
		{

			I2C_Send_data('B');										//SEND
			_delay_ms(100);
			I2C_STOP();
			_delay_ms(100);
		}
		else if(PINA&(1<<IN_PUT_PIN_2))
		{
			
			I2C_Send_data('C');										//SEND
			_delay_ms(100);
			I2C_STOP();
			_delay_ms(100);
		}
	}
	
}

