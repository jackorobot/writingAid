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
	
	//Enable filters
	PIOA->PIO_IFER = LSW1NC;
	PIOB->PIO_IFER = LSW1NO;
	PIOD->PIO_IFER = LSW2NO | LSW2NC;
	
	//Setup debounce filter
	PIOA->PIO_DIFSR = LSW1NC;
	PIOB->PIO_DIFSR = LSW1NO;
	PIOD->PIO_DIFSR = LSW2NO | LSW2NC;
	
	PIOA->PIO_SCDR = 8;
	PIOB->PIO_SCDR = 8;
	PIOD->PIO_SCDR = 8;
	
	//Setup delay timer interrupt TC0
	TC0->TC_CHANNEL[0]->TC_CCR = TC_CCR_CLKEN; //Enable timer channel
	TC0->TC_CHANNEL[0]->TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK5; //Use SLCK
	TC0->TC_CHANNEL[0]->TC_CMR = TC_CMR_WAVE; //Set waveform generation mode
	TC0->TC_CHANNEL[0]->TC_CMR = TC_CMR_ACPA_SET; //Set RA compare effect
	TC0->TC_CHANNEL[0]->TC_IER = TC_IER_CPAS; //Register A compare interrupt
	TC0->TC_CHANNEL[0]->TC_RA = 336000; //4 ms delay time
	
	//Setup delay timer interrupt TC1
	TC1->TC_CHANNEL[0]->TC_CCR = TC_CCR_CLKEN; //Enable timer channel
	TC1->TC_CHANNEL[0]->TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK5; //Use SLCK
	TC1->TC_CHANNEL[0]->TC_CMR = TC_CMR_WAVE; //Set waveform generation mode
	TC1->TC_CHANNEL[0]->TC_CMR = TC_CMR_ACPA_SET; //Set RA compare effect
	TC1->TC_CHANNEL[0]->TC_IER = TC_IER_CPAS; //Register A compare interrupt
	TC1->TC_CHANNEL[0]->TC_RA = 336000; //4 ms delay time
	
	//Enable encoder interrupts
	NVIC_EnableIRQ(PIOA_IRQn);
	NVIC_EnableIRQ(PIOB_IRQn);
	NVIC_EnableIRQ(PIOD_IRQn);
	NVIC_EnableIRQ(TC0_IRQn);
	NVIC_EnableIRQ(TC1_IRQn);
}

extern void readLimitSwitch(limitSwitch *lsw)
{
	if (lsw->axis == 1)
	{
			lsw->noContact = (PIOB->PIO_PDSR & LSW1NO) ? 1 : 0;
			lsw->ncContact = (PIOA->PIO_PDSR & LSW1NC) ? 1 : 0;
			lsw->error = lsw->noContact == lsw->ncContact;
			lsw->active = (lsw->noContact & !lsw->ncContact) | lsw->error;
	}else if (lsw->axis == 2)
	{
			lsw->noContact = (PIOD->PIO_PDSR & LSW2NO) ? 1 : 0;
			lsw->ncContact = (PIOD->PIO_PDSR & LSW2NC) ? 1 : 0;
			lsw->error = lsw->noContact == lsw->ncContact;
			lsw->active = (lsw->noContact & !lsw->ncContact) | lsw->error;
	}
}
