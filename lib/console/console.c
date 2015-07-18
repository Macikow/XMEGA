/*
 * uart.c
 *
 * Created: 3/28/2015 1:40:58 PM
 *  Author: Maciej
 */ 
#include "console.h"



int uart_putchar (char c, FILE *stream)
{
	if (c == '\n')
	uart_putchar('\r', stream);
	
	// Wait for the transmit buffer to be empty
	while ( !( USARTD0.STATUS & USART_DREIF_bm) );
	
	// Put our character into the transmit buffer
	USARTD0.DATA = c;
	
	return 0;
}