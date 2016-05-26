/*
 * encoders.c
 *
 * Created: 24-5-2016 13:45:25
 *  Author: Jesse
 */ 

#include "encoders.h"

extern void initEncoder(encoder *enc)
{
	if (enc->number == 1)
	{
		//Enable IO Pins
		PIOA->PIO_PER = ENC1I;
		PIOB->PIO_PER = ENC1A | ENC1B;
		
		//Set pins as pure inputs
		PIOA->PIO_ODR = ENC1I;
		PIOB->PIO_ODR = ENC1A | ENC1B;
		
		//Disable pull up pins, because of external pull ups
		PIOA->PIO_PUDR = ENC1I;
		PIOB->PIO_PUDR = ENC1A | ENC1B;
		
		//Enable interrupt for these pins
		PIOA->PIO_IER = ENC1I;
		PIOB->PIO_IER = ENC1A | ENC1B;
		
		//Enable the interrupt for these pins
		NVIC_EnableIRQ(PIOA_IRQn);
		NVIC_EnableIRQ(PIOB_IRQn);
		
	}else if (enc->number == 2)
	{
		//Enable IO Pins
		PIOA->PIO_PER = ENC2A;
		PIOD->PIO_PER = ENC2B | ENC2I;
		
		//Set pins as pure inputs
		PIOA->PIO_ODR = ENC2A;
		PIOD->PIO_ODR = ENC2B | ENC2I;
		
		//Disable pull up pins, because of external pull ups
		PIOA->PIO_PUDR = ENC2A;
		PIOD->PIO_PUDR = ENC2B | ENC2I;
		
		//Enable interrupt for these pins
		PIOA->PIO_IER = ENC2A;
		PIOD->PIO_IER = ENC2B | ENC2I;
		
		//Enable the interrupt for these pins
		NVIC_EnableIRQ(PIOA_IRQn);
		NVIC_EnableIRQ(PIOD_IRQn);
	}
}

extern inline void readEncoder(encoder *enc)
{
	if (enc->number == 1)
	{
		//Read encoder
		if (PIOB->PIO_ISR & ENC1A)
		{
			enc->aSet = (PIOB->PIO_PDSR & ENC1A) ? 1 : 0;
			enc->steps += (enc->aSet != enc->bSet) ? -1 : 1;
		}else if (PIOB->PIO_ISR & ENC1B)
		{
			enc->bSet = (PIOB->PIO_PDSR & ENC1B) ? 1 : 0;
			enc->steps += (enc->aSet == enc->bSet) ? -1 : 1;
		}
	}else if (enc->number == 2)
	{
		//Read encoder
		if (PIOA->PIO_ISR & ENC2A)
		{
			enc->aSet = (PIOA->PIO_PDSR & ENC2A) ? 1 : 0;
			enc->steps += (enc->aSet != enc->bSet) ? -1 : 1;
		}else if (PIOD->PIO_ISR & ENC2B)
		{
			enc->bSet = (PIOA->PIO_PDSR & ENC2B) ? 1 : 0;
			enc->steps += (enc->aSet == enc->bSet) ? -1 : 1;
		}
	}
}