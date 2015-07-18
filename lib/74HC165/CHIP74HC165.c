/*
 * _74HC165.c
 *
 * Created: 3/22/2015 5:28:06 PM
 *  Author: Maciej
 */ 
#include "CHIP74HC165.h"
#include <avr/io.h>
#include "util/delay.h"

#define SCK_PORT	PORTC
#define LOAD_PORT	PORTE 

#define SCK_PIN		(1 << 5)
#define LOAD_PIN	(1 << 6)
#define SO_PIN		(1 << 6)


#define CLRSCK ((SCK_PORT.OUTCLR) = SCK_PIN)
#define SETSCK ((SCK_PORT.OUTSET) = SCK_PIN)
#define SETLOAD ((LOAD_PORT.OUTSET) = LOAD_PIN)
#define CLRLOAD ((LOAD_PORT.OUTCLR) = LOAD_PIN)


void Chip74HC165Init(void){
	PORTC.DIRSET  =  SCK_PIN ;
	PORTC.DIRCLR = SO_PIN;
	PORTE.DIRSET = LOAD_PIN;
	PORTC.PIN6CTRL = PORT_OPC_PULLUP_gc;
	SETLOAD;
}

unsigned char Chip74HC165Read(void){
	SPIC.CTRL = 0;
	unsigned char outputData=0;
	CLRLOAD;
	for(unsigned char i=0 ; i<=7; i++){
		
		if((PORTC.IN  & 0b01000000) == PIN6_bm){
			PORTA.OUT = i;
			outputData+= (1<<7-i);
		}
		CLRSCK;
		_delay_us(5);
		SETSCK;
		_delay_us(5);
	}
	return outputData;
}