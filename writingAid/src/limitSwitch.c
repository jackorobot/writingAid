/*
 * limitSwitch.c
 *
 * Created: 30-5-2016 11:08:27
 *  Author: Jesse
 */ 

#include "limitSwitch.h"

extern void initLimitSwitches(void)
{
	//Enable PIO pins
	PIOA->PIO_PER = LSW1NC;
	PIOB->PIO_PER = LSW1NO;
	PIOD->PIO_PER = LSW2NO | LSW2NC;
	
	//Disable output on these pins
	PIOA->PIO_ODR = LSW1NC;
	PIOB->PIO_ODR = LSW1NO;
	PIOD->PIO_ODR = LSW2NO | LSW2NC;
	
	//Enable interrupts ons these pins
	PIOA->PIO_IER = LSW1NC;
	PIOB->PIO_IER = LSW1NO;
	PIOD->PIO_IER = LSW2NO | LSW2NC;
	
	//Disable pull ups
	PIOA->PIO_PUDR = LSW1NC;
	PIOB->PIO_PUDR = LSW1NO;
	PIOD->PIO_PUDR = LSW2NO | LSW2NC;
	
	//Enable encoder interrupts
	NVIC_EnableIRQ(PIOA_IRQn);
	NVIC_EnableIRQ(PIOB_IRQn);
	NVIC_EnableIRQ(PIOD_IRQn);
}

extern void readLimitSwitch(limitSwitch *lsw)
{
	if (lsw->axis == 1)
	{
			lsw->noContact = (PIOB->PIO_PDSR & LSW1NO) ? 1 : 0;
			lsw->ncContact = (PIOA->PIO_PDSR & LSW1NC) ? 1 : 0;
			lsw->error = lsw->noContact == lsw->ncContact;
			lsw->active = !lsw->error & lsw->noContact & !lsw->ncContact;
	}else if (lsw->axis == 2)
	{
			lsw->noContact = (PIOD->PIO_PDSR & LSW2NO) ? 1 : 0;
			lsw->ncContact = (PIOD->PIO_PDSR & LSW2NC) ? 1 : 0;
			lsw->error = lsw->noContact == lsw->ncContact;
			lsw->active = (lsw->noContact & !lsw->ncContact) | lsw->error;
	}
}
