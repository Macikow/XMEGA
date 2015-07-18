/*
 * nRF24.c
 *
 * Created: 5/5/2015 8:33:06 PM
 *  Author: Maciej
 */ 
#include <avr/io.h>
#include "avr/interrupt.h"
#include "util/delay.h"


#define SPI_SCK PIN7_bm
#define SPI_MISO PIN6_bm
#define SPI_MOSI PIN5_bm

#define CE PIN0_bm
#define CSN PIN1_bm
//#define CSN_high  PORTD.OUTSET= CSN//
//#define CSN_low  PORTD.OUTCLR = CSN

//#define CE_high	PORTD.OUTSET= CE
//#define CE_Low PORTD.OUTCLR = CE


// nRF Commands
#define R_REGISTER			0x00
#define W_REGISTER			0x20
#define R_RX_PAYLOAD		0x61
#define W_TX_PAYLOAD		0xA0
#define FLUSH_TX			0xE1
#define FLUSH_RX			0xE2
#define REUSE_TX_PL			0xE3
#define R_RX_PL_WID			0x60
#define W_ACK_PAYLOAD		0xA1
#define W_TX_PAYLOAD_No_ACK	0xB0
#define NOP					0xff


#define SPI_PORT PORTC
#define NRF_MISO (1<<6)
#define NRF_MOSI (1<<7)
#define NRF_SCK (1<<5)

#define NRF_ENABLE_PORT PORTD
#define NRF_CSN (1<<1)
#define NRF_CE  (1<<0)


// bufor trójstanowy  DIR wy³acz w³acz;
#define IO_BUFFOR_DIR_ENABLE	((PORTE.DIRSET) = (1<<6))
#define IO_BUFFOR_ENABLE		((PORTE.OUTCLR) = (1<<6))
#define IO_BUFFOR_DISABLE		((PORTE.OUTSET)=(1<<6))

// spi
#define SPI_MOSI_SCK_INIT	((PORTC.DIRSET)=((NRF_MOSI) | (NRF_SCK)))
#define SPI_MISO_INIT		((PORTC.DIRCLR) = (NRF_MISO))
#define SPI_CE_CSN_INIT		((PORTD.DIRSET)=((NRF_CE)|(NRF_CSN)))

#define SPI_REMAP ((PORTC.REMAP) = (PORT_SPI_bm))

#define NRF_CE_LOW		((PORTD.OUTCLR) = (NRF_CE))
#define NRF_CSN_LOW		((PORTD.OUTCLR) = (NRF_CSN))
#define NRF_CE_HIGH		((PORTD.OUTSET) = (NRF_CE))
#define NRF_CSN_HIGH	((PORTD.OUTSET) = (NRF_CSN))

#define CONFIG 0x00
//////////////// CONFIG
#define PRIM_RX (1 << 0)
#define PWR_UP (1 << 1)
#define CRC0 (1 << 2) // 0 :1bit 1: 2bit
#define EN_CRC (1 << 3)
#define MASK_MAX_RT (1 << 4)
#define MASK_TX_DS (1 << 5)
#define MASK_RX_DR (1 << 6)

#define EN_AA 0x01
//////////////// EN_AA
#define EN_AAP5 (1 << 5)
#define EN_AAP4 (1 << 4)
#define EN_AAP3 (1 << 3)
#define EN_AAP2 (1 << 2)
#define EN_AAP1 (1 << 1)
#define EN_AAP0 (1 << 0)

#define EN_RX_ADDR 0x02
//////////////// EN_AA
#define ERX_P5 (1 << 5)
#define ERX_P4 (1 << 4)
#define ERX_P3 (1 << 3)
#define ERX_P2 (1 << 2)
#define ERX_P1 (1 << 1)
#define ERX_P0 (1 << 10)

#define SETUP_AW 0x03 // RX/TX setup address field with
//////////////// SETUP_AW
#define THREE_BYTES 1
#define FOUR_BYTES 2
#define FIVE_BYTES 3

#define SETUP_RETR 0x04 //
//////////////// SETUP_RETR
//delay
#define MS_250 (0x0 << 4)
#define MS_500 (0x1 << 4)
#define MS_750 (0x2 << 4)
#define MS_1000 (0x3 << 4)
#define MS_1250 (0x4 << 4)
#define MS_1500 (0x5 << 4)
#define MS_1750 (0x6 << 4)
#define MS_2000 (0x7 << 4)
#define MS_2250 (0x8 << 4)
#define MS_2500 (0x9 << 4)
#define MS_2750 (0xA << 4)
#define MS_3000 (0xB << 4)
#define MS_3250 (0xC << 4)
#define MS_3500 (0xD << 4)
#define MS_3750 (0xE << 4)
#define MS_4000 (0xF << 4)
//ARC
#define ARC_1 0
#define ARC_2 1
#define ARC_3 2
#define ARC_4 3
#define ARC_5 4
#define ARC_6 5
#define ARC_7 6
#define ARC_8 7
#define ARC_9 8
#define ARC_10 9
#define ARC_11 10
#define ARC_12 11
#define ARC_13 12
#define ARC_14 13
#define ARC_15 14

#define RF_CH 0x05
//////////////// SETUP_RETR
// jeszcze nie wiem co tu wpisac


#define RF_SETUP 0x06
//////////////// RF_SETUP
#define COUNT_WAVE (1 << 7)
#define RF_DR_LOW (1 << 5)
#define PLL_LOCK (1 << 4)
#define RF_DR_HIGH (1 << 3)
#define RF_POWER_18 (0 << 1)
#define RF_POWER_12 (1 << 1)
#define RF_POWER_6 (2 << 1)
#define RF_POWER_0  (3 << 1)

#define STATUS_NRF 0x07
//////////////// STATUS
#define RX_DR (1 << 6 )  // data ready
#define TX_DS (1 << 5 )
#define MAX_RT (1 << 4)
#define RX_P_0 (0 << 1)
#define RX_P_1 (1 << 1)
#define RX_P_2 (2 << 1)
#define RX_P_3 (3 << 1)
#define RX_P_4 (4 << 1)
#define RX_P_5 (5 << 1)
#define RX_P_5 (7 << 1) // RX_FIFO_EMPTY
#define FIFO_FULL (1 << 0)

#define OBSERVE_TX 0x08
//////////////// OBSERVE_TX
#define PLOS_COUNT_MASK 0xf0
#define ARC_COUNT_MASK 0x0f

#define RPD 0x09
//////////////// RPD
#define RPD_0 (1 << 0)

#define RX_ADDRESS_P0 0x0A // 40 bit
//////////////// P0

#define RX_ADDRESS_P1 0x0B // 40 bit
//////////////// P1

#define RX_ADDRESS_P2 0x0C // 7  bit
//////////////// P2

#define RX_ADDRESS_P3 0x0D //...
//////////////// P3

#define RX_ADDRESS_P4 0x0E
//////////////// P4

#define RX_ADDRESS_P5 0x0F
//////////////// P5

#define TX_ADDRESS 0x10 // 40 bit
//////////////// TX_ADDRESS
#define RX_PW_P0

#define RX_PW_P0 0x11
#define RX_PW_P1 0x12
#define RX_PW_P2 0x13
#define RX_PW_P3 0x14
#define RX_PW_P4 0x15
#define RX_PW_P5 0x16


#define FIFO_STATUS 0x17
/////////////// FIFO_STATUS
#define TX_REUSE (1 << 6)
#define TX_FULL (1 << 5)
#define TX_EMPTY (1 << 4)
#define RX_FULL (1 << 1)
#define RX_EMPTY (1 << 0)

#define DYNPD 0x1C
////////////// DYNPD
#define DPL_P5 (1 << 5)
#define DPL_P4 (1 << 4)
#define DPL_P3 (1 << 3)
#define DPL_P2 (1 << 2)
#define DPL_P1 (1 << 1)
#define DPL_P0 (1 << 0)

#define FEATURE 0x1D
///////////// FEATURE
#define EN_PLD (1 << 2)
#define EN_ACK_PAY (1 << 1)
#define EN_DYN_ACK (1 << 0)

char *RegName(unsigned char Address){
	char *stringTab[30] =  { "CONFIG  ","EN_AA   ","EN_RXADDR","SETUP_AW","SETUP_RETR","RF_CH    ","RF_SETUP","STATUS   ","OBSERVE_TX","RPD     ","RX_ADDR_P0","RX_ADDR_P1","RX_ADDR_P2","RX_ADDR_P3","RX_ADDR_P4","RX_ADDR_P5","TX_ADDR","RX_PW_P0","RX_PW_P1","RX_PW_P2","RX_PW_P3","RX_PW_P4","RX_PW_P6","FIFI_STATUS","ACK_PLD","TX_PLD  ","RX_PLD   ","DYNPD  ","FEATURE"	};
	return stringTab[Address];
}

void IOPortInit(void){
	IO_BUFFOR_DIR_ENABLE;
	IO_BUFFOR_DISABLE;
}


void nRFSpiInit(void){
	SPI_MISO_INIT;
	SPI_MOSI_SCK_INIT;
	SPI_CE_CSN_INIT;
	SPI_REMAP;
	SPIC.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV16_gc ;
	SPIC.INTCTRL = 0x00;
	NRF_CSN_HIGH;
	NRF_CE_LOW;
	IO_BUFFOR_DISABLE;
}
unsigned char nRFReadRegister(unsigned char regAddress)
{
	NRF_CSN_LOW;
	SPIC.DATA = R_REGISTER | regAddress ;
	_delay_us(200);
	SPIC.DATA = NOP;
	_delay_us(200);
	NRF_CSN_HIGH;
	return SPIC.DATA;
}
void nRFWriteregister(unsigned char regAddress , unsigned char Data){
	NRF_CSN_LOW;
	SPIC.DATA = W_REGISTER | regAddress;
	_delay_us(200);
	SPIC.DATA = Data;
	_delay_us(200);
	NRF_CSN_HIGH;
}
void nRFStartUP(void){
	nRFWriteregister(CONFIG, (0x00 | PWR_UP));
	_delay_ms(3);
}
void nRFWritePayload(unsigned char *Data){
	NRF_CSN_LOW;
	SPIC.DATA = W_TX_PAYLOAD;
	_delay_us(200);
	for( unsigned char i= 0 ; i<8 ; i++){
		printf(" %d ", *(Data+i));
		SPIC.DATA = *(Data+i);
		_delay_us(200);
	}
	NRF_CSN_HIGH;
};
unsigned char *nRFReadPayload(void){
	unsigned char buffor[8];
	unsigned char *ptr;
	ptr = &buffor;
	NRF_CSN_LOW;
	SPIC.DATA = R_RX_PAYLOAD;
	_delay_us(200);
	for(unsigned char i=0;i<8;i++){
		*ptr = SPIC.DATA;
		_delay_us(200);
	}
	NRF_CSN_LOW;
}