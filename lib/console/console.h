/*
 * consloe.h
 *
 * Created: 3/28/2015 1:41:11 PM
 *  Author: Maciej
 */ 


#ifndef CONSLOE_H_
#define CONSLOE_H_
#include <stdio.h>
#include <avr/io.h>


int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM (uart_putchar, NULL, _FDEV_SETUP_WRITE);
int uart_putchar(char c, FILE *stream);




#endif /* CONSLOE_H_ */