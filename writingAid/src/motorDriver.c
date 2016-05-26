/*
 * motorDriver.c
 *
 * Created: 18-5-2016 15:07:17
 *  Author: Jesse
 */ 

#include "motorDriver.h"
#include <math.h>

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
	
	
	//Start interrupt for driver faults
	NVIC_EnableIRQ(PIOA_IRQn);
	NVIC_EnableIRQ(PIOC_IRQn);
}

extern void setCurrent(uint32_t driver, uint32_t current)
{
	if(current <= 0x1F)
	{
		if(driver == 1)
		{
			//Clear bits from Drive 1
			PIOC->PIO_ODSR &= ~(31 << D1CUR);
			//Write current to Drive 1
			PIOC->PIO_ODSR |= (current << D1CUR);
		}else if (driver == 2)
		{
			//Clear bits from Drive 2
			PIOC->PIO_ODSR &= ~(31 << D2CUR);
			//Write current to Drive 2
			PIOC->PIO_ODSR |= (current << D2CUR);
		}
	}
}

extern void enableDrive(uint32_t driver)
{
	if (driver == 1)
	{
		//Set enable bit of drive 1
		PIOC->PIO_OER = D1ENBL;
	}else if (driver == 2)
	{
		//Set enable bit of drive 2
		PIOB->PIO_OER = D2ENBL;
	}
}

extern void disableDrive(uint32_t driver)
{
	if (driver == 1)
	{
		//Clear enable bit of drive 1
		PIOC->PIO_ODR = D1ENBL;
	} 
	else if (driver == 2)
	{
		//Clear enable bit of drive 2
		PIOB->PIO_ODR = D2ENBL;
	}
}

extern void resetSetDrive(uint32_t driver)
{
	if (driver == 1)
	{
		//Reset Nreset bit of drive 1
		PIOC->PIO_ODR = D1NRESET;
	}else if (driver == 2)
	{
		//Reset Nreset bit of drive 2
		PIOC->PIO_ODR = D2NRESET;
	}
}

extern void resetClearDrive(uint32_t driver)
{
	if (driver == 1)
	{
		//Set Nreset bit of Drive 1
		PIOC->PIO_OER = D1ENBL;
	} 
	else if (driver == 2)
	{
		//Set Nreset bit of Drive 2
		PIOC->PIO_OER = D2ENBL;
	}
}

extern void writeForcePercentage(uint32_t driver, double percentage)
{
	//First calculate the current and get the direction
	bool phase = (percentage < 0.0); //If percentage is negative then phase is 1
	
	double absPercentage = abs(percentage); //Calculate absolute value
	
	double currentDouble = absPercentage / 100.0 * 31.0;
	
	uint32_t current = (uint32_t)currentDouble;
	
	setCurrent(driver, current);
	
	//Write phase to driver
	if (driver == 1)
	{
		if (phase)
		{
			//Phase is 1, write to drive 1
			PIOC->PIO_SODR = D1APHASE;
		}else{
			//Phase is 0, write to drive 1
			PIOC->PIO_CODR = D1APHASE;
		}
	} 
	else if (driver == 2)
	{
		if (phase)
		{
			//Phase is 1, write to drive 2
			PIOB->PIO_SODR = D1APHASE;
		}else{
			//Phase is 0, write to drive 2
			PIOB->PIO_CODR = D1APHASE;
		}
	}
}
