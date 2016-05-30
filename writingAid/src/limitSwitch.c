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
	PIOA->PIO_PER = LSW11NC | LSW12NO;
	PIOB->PIO_PER = LSW11NO;
	PIOD->PIO_PER = LSW12NC | LSW21NO | LSW21NC | LSW22NO | LSW22NC;
	
	//Disable output on these pins
	PIOA->PIO_ODR = LSW11NC | LSW12NO;
	PIOB->PIO_ODR = LSW11NO;
	PIOD->PIO_ODR = LSW12NC | LSW21NO | LSW21NC | LSW22NO | LSW22NC;
	
	//Enable interrupts ons these pins
	PIOA->PIO_IER = LSW11NC | LSW12NO;
	PIOB->PIO_IER = LSW11NO;
	PIOD->PIO_IER = LSW12NC | LSW21NO | LSW21NC | LSW22NO | LSW22NC;
	
	//Disable pull ups
	PIOA->PIO_PUDR = LSW11NC | LSW12NO;
	PIOB->PIO_PUDR = LSW11NO;
	PIOD->PIO_PUDR = LSW12NC | LSW21NO | LSW21NC | LSW22NO | LSW22NC;
	
	//Enable encoder interrupts
	NVIC_EnableIRQ(PIOA_IRQn);
	NVIC_EnableIRQ(PIOB_IRQn);
	NVIC_EnableIRQ(PIOD_IRQn);
}

extern void readLimitSwitch(limitSwitch *lsw)
{
	if (lsw->axis == 1)
	{
		if (lsw->direction == 1)
		{
			lsw->noContact = (PIOB->PIO_PDSR & LSW11NO) ? 1 : 0;
			lsw->ncContact = (PIOA->PIO_PDSR & LSW11NC) ? 1 : 0;
			lsw->error = lsw->noContact ^ lsw->ncContact;
			lsw->active = !lsw->error & lsw->noContact & !lsw->ncContact;
		}
		else if (lsw->direction == 2)
		{
			lsw->noContact = (PIOA->PIO_PDSR & LSW12NO) ? 1 : 0;
			lsw->ncContact = (PIOD->PIO_PDSR & LSW12NC) ? 1 : 0;
			lsw->error = lsw->noContact ^ lsw->ncContact;
			lsw->active = !lsw->error & lsw->noContact & !lsw->ncContact;			
		}
	}else if (lsw->axis == 2)
	{
		if (lsw->direction == 1)
		{
			lsw->noContact = (PIOD->PIO_PDSR & LSW21NO) ? 1 : 0;
			lsw->ncContact = (PIOD->PIO_PDSR & LSW21NC) ? 1 : 0;
			lsw->error = lsw->noContact ^ lsw->ncContact;
			lsw->active = !lsw->error & lsw->noContact & !lsw->ncContact;
		} 
		else if (lsw->direction == 2)
		{
			lsw->noContact = (PIOD->PIO_PDSR & LSW22NO) ? 1 : 0;
			lsw->ncContact = (PIOD->PIO_PDSR & LSW22NC) ? 1 : 0;
			lsw->error = lsw->noContact ^ lsw->ncContact;
			lsw->active = !lsw->error & lsw->noContact & !lsw->ncContact;
		}
	}
}
