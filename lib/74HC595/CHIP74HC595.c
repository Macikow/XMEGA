/*
 * _74HC595.c
 *
 * Created: 3/22/2015 5:28:55 PM
 *  Author: Maciej
 */ 
//#define SCK_PORT (PORTC
#include "CHIP74HC595.h"
#include <avr/io.h>
#include "util/delay.h"
// pin definition :
#define SCK_PIN		(1 << 5)
#define SI_PIN		(1 << 7)
#define LOAD_PIN	(1 << 6)

#define CLRSCK ((PORTC.OUTCLR) = SCK_PIN)
#define SETSCK ((PORTC.OUTSET) = SCK_PIN)
#define SETSI ((PORTC.OUTSET) = SI_PIN)
#define CLRSI ((PORTC.OUTCLR) = SI_PIN)
#define SETLOAD ((PORTE.OUTSET) = LOAD_PIN)
#define CLRLOAD ((PORTE.OUTCLR) = LOAD_PIN)



void Chip74HC595Init(void){
	
	PORTC.DIRSET  =  SCK_PIN | SI_PIN ;
	PORTE.DIRSET = LOAD_PIN;
	SETLOAD;
}

void Chip74HC595Write(unsigned char data){
	SPIC.CTRL = 0;
	unsigned char i;
	CLRLOAD;
	for(i=0;i<9;i++){
		CLRSCK;
		_delay_us(5);
		SETSCK;
		if((1<<(7-i)) & data){
			SETSI;
		}
		else CLRSI;
		
	}
	SETLOAD;
	CLRSCK;
}