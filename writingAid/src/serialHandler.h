/*
 * serial.h
 *
 * Created: 3-5-2016 17:14:16
 *  Author: Jesse
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

#include "sysclk.h"
#include "uart.h"
#include "usart.h"

#define USART_SERIAL				USART0
#define USART_SERIAL_ID				ID_USART0
#define USART_SERIAL_BAUDRATE		115200
#define USART_SERIAL_CHAR_LENGTH	US_MR_CHRL_8_BIT
#define USART_SERIAL_PARITY			US_MR_PAR_NO
#define USART_SERIAL_STOP_BIT		US_MR_NBSTOP_1_BIT

#define SERIAL_RX_SIZE		128
#define SERIAL_TX_SIZE		128

char serialRxBuffer[SERIAL_RX_SIZE];
uint32_t serialRxIn;
uint32_t serialRxOut;
char serialTxBuffer[SERIAL_TX_SIZE];
uint32_t serialTxIn;
uint32_t serialTxOut;

extern void serialInit(void);
extern char serialGet(void);
extern Bool serialRxAvailable(void);
extern void serialPut(char c);
extern void serialPutS(char *s);

#endif /* SERIAL_H_ */