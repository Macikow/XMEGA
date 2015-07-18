/*
 * nRF24.h
 *
 * Created: 5/5/2015 8:33:20 PM
 *  Author: Maciej
 */ 


#ifndef NRF24_H_
#define NRF24_H_


void nRFSpiInit(void);

unsigned char nRFReadRegister(unsigned char regAddress);

void nRFWriteregister(unsigned char regAddress , unsigned char Data);

void nRFStartUP(void);

void nRFWritePayload(unsigned char *Data);

unsigned char *nRFReadPayload(void);
#endif /* NRF24_H_ */