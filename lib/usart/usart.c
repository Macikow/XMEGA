/*
 * usart.c
 *
 * Created: 3/28/2015 1:57:01 PM
 *  Author: Maciej
 */ 
#include <avr/io.h>
#include "../avr_compiler.h"
#include "avr/interrupt.h"
/************************************************************************/
/* 
	BAUD_RATE ustawiony na 2 MHz
                                                                     */
/************************************************************************/
#define BAUD_RATE_FREQ 9600

#define TXD0 PIN3_bm
#define RXD0 PIN2_bm


inline unsigned int baudRate(void){
	return ((F_CPU/16*BAUD_RATE_FREQ) -1);
}
void uartInit(void){
	
	PORTD.OUTSET = TXD0;
	PORTD.DIRSET = TXD0;	// TX jako wyjscie
	PORTD.OUTCLR = RXD0;
	PORTD.DIRCLR = RXD0;	// RX jako wyjscie
	
	USARTD0_BAUDCTRLB =0;
	USARTD0_BAUDCTRLA =207;

	//USARTD0.CTRLC = 0x00;
	USARTD0.CTRLC = 0x03;
	USARTD0.CTRLB = USART_TXEN_bm | USART_RXEN_bm | USART_CLK2X_bm;
	
	USARTD0.CTRLA = USART_RXCINTLVL_HI_gc;
	PMIC.CTRL = PMIC_HILVLEN_bm;
}
