/*
 * serial.c
 *
 * Created: 3-5-2016 17:14:29
 *  Author: Jesse
 */ 

#include "serialHandler.h"

void serialInit(void)
{
	//Start peripheral clock for usart
	sysclk_enable_peripheral_clock(USART_SERIAL_ID);
	
	const sam_usart_opt_t usartConsoleSettings = {
		USART_SERIAL_BAUDRATE,
		USART_SERIAL_CHAR_LENGTH,
		USART_SERIAL_PARITY,
		USART_SERIAL_STOP_BIT,
		US_MR_CHMODE_NORMAL
	};
	
	//Initialize usart in rs232 mode
	usart_init_rs232(USART_SERIAL, &usartConsoleSettings, sysclk_get_main_hz());
	
	//Enable receiving and sending
	usart_enable_rx(USART_SERIAL);
	usart_enable_tx(USART_SERIAL);
	
	//Enable Interrupt when character is received
	usart_enable_interrupt(USART_SERIAL, US_IER_RXRDY);
	NVIC_EnableIRQ(USART0_IRQn);
}

char serialGet(void)
{
	char c;
	
	c = serialRxBuffer[serialRxOut++];
	if(serialRxOut >= SERIAL_RX_SIZE)
		serialRxOut = 0;
	
	return c;
}

Bool serialRxAvailable(void)
{
	return (serialRxIn != serialRxOut);
}

void serialPut(char c)
{
	serialTxBuffer[serialTxIn++] = c;
	if(serialTxIn >= SERIAL_TX_SIZE)
		serialTxIn = 0;
	
	//Call interrupt
	usart_enable_interrupt(USART_SERIAL, US_IER_TXRDY);
	NVIC_SetPendingIRQ(USART0_IRQn);
	
	while(!usart_is_tx_ready(USART_SERIAL));
}

void serialPutS(char *s)
{
	while(*s)
	{
		serialPut(*s++);
	}
}

void USART0_Handler(void)
{
	NVIC_ClearPendingIRQ(USART0_IRQn);
	//Get the state of the usart
	uint32_t usart_state = usart_get_status(USART_SERIAL);
	
	if(usart_state & US_CSR_RXRDY)
	{	//Receive
		uint32_t c;
		if(usart_read(USART_SERIAL, &c) == 0)
		{
			serialRxBuffer[serialRxIn++] = (char)c;
			if(serialRxIn >= SERIAL_TX_SIZE)
				serialRxIn = 0;
		}
	}
	else if(usart_state & US_CSR_TXRDY)
	{	//Transmit
		if(serialTxIn != serialTxOut)
		{
			usart_write(USART_SERIAL, (uint32_t)serialTxBuffer[serialTxOut++]);
			if(serialTxOut >= SERIAL_TX_SIZE)
				serialTxOut = 0;
		}
		else
		{
			usart_disable_interrupt(USART_SERIAL, US_IER_TXRDY);
		}
	}
}
