/*
 * motorDriver.c
 *
 * Created: 18-5-2016 15:07:17
 *  Author: Jesse
 */ 

#include "motorDriver.h"

void initMotorDriver(void)
{
	//////////////////////////////////////////////////////////////////////////
	//HIER PROBEREN ALLE BITS IN 1 REGEL TE SETTEN
	//////////////////////////////////////////////////////////////////////////
	// DRIVE CONTROL PINS
	//////////////////////////////////////////////////////////////////////////
	//Enable IO pins for drive one and two
	PIOC->PIO_PER = D1DECAY | D1NRESET | D1APHASE | D1ENBL; //Drive 1: Decay, Nreset, Aphase, Enbl
	PIOA->PIO_PER = D1NSLEEP | D1NFAULT; //Drive 1: Nsleep, Nfault
	
	PIOC->PIO_PER = D2DECAY | D2NRESET | D2NSLEEP | D2NFAULT; //Drive 2: Decay, Nreset, Nsleep, Nfault
	PIOB->PIO_PER = D2APHASE | D2ENBL; //Drive 2: Aphase, Enbl
	
	//Set output pins as output
	PIOC->PIO_OER = D1DECAY | D1NRESET | D1APHASE | D1ENBL; //Drive 1: Decay, Nreset, Aphase, Enbl
	PIOA->PIO_OER = D1NSLEEP; //Drive 1: Nsleep
	
	PIOC->PIO_OER = D2DECAY | D2NRESET | D2NSLEEP; //Drive 2: Decay, Nreset, Nsleep
	PIOB->PIO_OER = D2APHASE | D2ENBL; //Drive 2: Aphase, Enbl
	
	//Remove all pull-up resistors
	PIOC->PIO_PUDR = D1DECAY | D1NRESET | D1APHASE | D1ENBL; //Drive 1: Decay, Nreset, Aphase, Enbl
	PIOA->PIO_PUDR = D1NSLEEP | D1NFAULT; //Drive 1: Nsleep, Nfault
	
	PIOC->PIO_PUDR = D2DECAY | D2NRESET | D2NSLEEP | D2NFAULT; //Drive 2: Decay, Nreset, Nsleep, Nfault
	PIOB->PIO_PUDR = D2APHASE | D2ENBL; //Drive 2: Aphase, Enbl
	
	//Set the default states of the output pins
	//Clear output
	PIOC->PIO_CODR = D1ENBL | D1APHASE | D1DECAY | D2DECAY; //Drive 1: Enable, Aphase, Decay. Drive 2: Decay
	PIOB->PIO_CODR = D2APHASE | D2ENBL; //Drive 2: Aphase, Enable
	//Set output
	PIOC->PIO_SODR = D1NRESET | D2NRESET | D2NSLEEP; //Drive 1: Nreset. Drive2: Nreset, Nsleep
	PIOA->PIO_SODR = D1NSLEEP; //Drive 1: Nsleep
	
	//Set output pins as input
	PIOA->PIO_ODR = D1NFAULT; //Drive 1: Nfault
	PIOC->PIO_ODR = D2NFAULT; //Drive 2: Nfault
	
	//Enable pin change interrupt for fault pins
	PIOA->PIO_IER = D1NFAULT; //Drive 1: Nfault
	PIOC->PIO_IER = D2NFAULT; //Drive 2: Nfault
	
	//////////////////////////////////////////////////////////////////////////
	// DRIVE CURRENT PINS
	//////////////////////////////////////////////////////////////////////////
	//Enable Current control pins
	PIOC->PIO_PER = (31 << D1CUR); //Drive 1: Set the 5 bits for current set (1-5)
	PIOC->PIO_PER = (31 << D2CUR); //Drive 2: Set the 5 bits for current set (21-25)
	
	//Enable direct pin manipulation for these pins
	PIOC->PIO_OWER = (31 << D1CUR); //Drive 1: Set the 5 bits for current set (1-5)
	PIOC->PIO_OWER = (31 << D2CUR); //Drive 2: Set the 5 bits for current set (21-25)
	
	//Write zeroes to these pins
	PIOC->PIO_ODSR &= ~(31 << D1CUR); //Drive 1: Set the 5 bits for current set (1-5)
	PIOC->PIO_ODSR &= ~(31 << D2CUR); //Drive 2: Set the 5 bits for current set (21-25)
}