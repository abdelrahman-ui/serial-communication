/*
 * lcd.h
 *
 * Created: 5/19/2019 11:36:55 AM
 *  Author: Mohamed
 */ 


#ifndef LCD_H_
#define LCD_H_


#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */

#define F_CPU	16000000

#define LCD_Dir				  DDRA			/* Define LCD data port direction */
#define LCD_Port			  PORTA			/* Define LCD data port */
#define LCD_Dir_Control		  DDRB			/* Define LCD Control port direction */
#define LCD_Port_Control	  PORTB			/* Define LCD Control port direction */

#define RS					  1		/* Define Register Select pin */
#define EN					  3
#define RW					  2			/* Define Register Select pin */

void LCD_Init (void) ;
void LCD_Command( unsigned char cmnd );
void LCD_Char( unsigned char data );
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();




#endif /* LCD_H_ */