/*
 * XMEGA.c
 *
 * Created: 3/21/2015 8:11:10 PM
 *  Author: Maciej
 */ 
#define F_CPU 32000000UL
#include <avr/io.h>
#include "avr/interrupt.h"
#include "util/delay.h"
#include "lib/74HC165/CHIP74HC165.h"
#include "lib/74HC595/CHIP74HC595.h"
#include "lib/lcd/lcd.h"
#include "lib/spi/spi_driver.h"
#include "lib/vt100/vt100.h"
#include "lib/nRF24/nRF24.h"
#include <stdio.h>


/************************************************************************/
/* UART CONSOLE APP                                                                     */
/************************************************************************/
static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM (uart_putchar, NULL, _FDEV_SETUP_WRITE);

static int uart_putchar (char c, FILE *stream)
{
	if (c == '\n')
	uart_putchar('\r', stream);
	
	// Wait for the transmit buffer to be empty
	while ( !( USARTD0.STATUS & USART_DREIF_bm) );
	
	// Put our character into the transmit buffer
	USARTD0.DATA = c;
	
	return 0;
}
/////////////////////////////////////////////////////////////////////////////





void RC32MHzEnable(void){
	CLK.CTRL = OSC_RC2MEN_bm;
	_delay_us(255);
	Chip74HC595Write(0xA0);
	while(!(OSC.STATUS & OSC_RC2MRDY_bm));
	CPU_CCP = CCP_IOREG_gc;
	CLK.CTRL = CLK_SCLKSEL_RC2M_gc;
	Chip74HC595Write(0xAA);
}

void clearScr(){
  printf("\033[2J"); // Czyœci ekran
  printf("\033[0;0f"); // Ustawia kursor w lewym, górnym rogu
}

void vtMainMenu(void){
	printf(ERASE_FORM_CURRENT_LINE_TO_THE_END);
	printf("\0x1b[K");
	printf("\x1B(");	
	printf("\x1B[3;15H");
	printf(SET_BACK_GREEN);printf(SET_FORE_BLACK);
	printf("MENU");
	printf(SET_BACK_DEFAULT);printf(SET_FORE_WHITE);
	printf("\n\r\t1.Kodowanie Hufmana");
	printf("\n\r\t2.Kodowanie z przeplotem");
	printf("\n\r\t3.Kodowanie Hauffmana");
	printf("\n\r\t4.Poprawic to menu");
}


void Osc32MHz(void) {
	OSC.CTRL     =    OSC_RC32MEN_bm;       // w³¹czenie oscylatora 32MHz
	while(!(OSC.STATUS & OSC_RC32MRDY_bm)); // czekanie na ustabilizowanie siê generatora
	CPU_CCP      =    CCP_IOREG_gc;         // odblokowanie zmiany Ÿród³a sygna³u
	CLK.CTRL     =    CLK_SCLKSEL_RC32M_gc; // zmiana Ÿród³a sygna³u na RC 32MHz
}
int main(void)
{
	Osc32MHz(); // uruchomienie clk =32 Mhz
	uartInit();
	stdout = &mystdout;
	clearScr();
	printf("poczatek programu : obsluga spi\n\r");
	printf(ERASE_SCREEN);
	sei();
	while(1)
	{
		printf("in loop");
		_delay_ms(500);
		
    }
}


ISR(USARTD0_RXC_vect){
	unsigned char RXData;
	RXData = USARTD0.DATA;
	printf("%c",RXData);
	while(1);
	//USARTD0.DATA = RXData;
	//Chip74HC595Write(0x04);
}