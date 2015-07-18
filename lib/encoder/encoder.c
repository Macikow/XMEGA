/*
 * encoder.c
 *
 * Created: 3/22/2015 5:49:58 PM
 *  Author: Maciej
 */ 
#include "encoder.h"
#include "avr/interrupt.h"
#include <avr/io.h>
#include "util/delay.h"

#define ERASE_MEM_MODE	1
#define NORMAL_MODE  0


void encoderInit(void){
	PORTE.OUTCLR = (1 << 2) |  (1 << 1) | (1 << 0);
	
	PORTE.PIN0CTRL = PORT_ISC_RISING_gc;
	PORTE.INT0MASK  = PIN0_bm;
	PORTE.INTCTRL = PORT_INT0LVL_LO_gc;
	
	PMIC.CTRL = PMIC_HILVLEN_bm | PMIC_LOLVLEN_bm ;
	sei();
}

unsigned char encoderLeft(unsigned char eraseMem){
	static unsigned char mem;
	if (eraseMem)	mem = 0;
	else {
		mem++;
		if(mem == 2){ // wykryto pe³en obrot
			return 1;
		}
		else {
			return 0;
		}
	}	
}
unsigned char  encoderRight(unsigned char eraseMem){
	static unsigned char mem;
	if(eraseMem) mem = 0;
	else{
		mem++;
		if(mem == 2){ // wykryto pe³en obrot
			return 1;
		}
		else {
			return 0;
		}
	}}

ISR(PORTE_INT0_vect){
	unsigned char leftTotem, RightTotem;
	if(PORTE.IN & 0x02){ // w prawo
		encoderLeft(ERASE_MEM_MODE); // jeœli prawo to kasuj pamiêæ dla lewo
		RightTotem = encoderRight(NORMAL_MODE);
	}
	else{ // w lewo
		encoderRight(ERASE_MEM_MODE); // jesli lewo to kasuj pamiêc dla prawo
		leftTotem = encoderLeft(NORMAL_MODE);
	}
	if(leftTotem && counter) counter --;
	if(RightTotem && (counter != 255)) counter ++;
}

