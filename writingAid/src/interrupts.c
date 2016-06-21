/*
 * interrupts.c
 *
 * Created: 25-5-2016 15:46:18
 *  Author: Jesse
 */ 

#include "asf.h"
#include "motorDriver.h"
#include "encoders.h"
#include "limitSwitch.h"

void PIOA_Handler(void)
{
	NVIC_ClearPendingIRQ(PIOA_IRQn);
	
	//Interrupt of Drive 2: Nfault
	if (PIOA->PIO_ISR & D2NFAULT)
	{
		//Interrupt from Drive 2: Nfault pinchange pending
		if (PIOA->PIO_PDSR & D2NFAULT)
		{
			//Nfault is high, then not reset the drive
			resetClearDrive(2);
			}else{
			//Nfault is low, then reset the drive
			resetSetDrive(2);
		}
	}
	//Interrupt of encoder pin
	if (PIOA->PIO_ISR & ENC1I)
	{
		readEncoder(&enc1);
	}
	//Interrupt of encoder pin
	if (PIOA->PIO_ISR & ENC2A)
	{
		readEncoder(&enc2);
	}
	//Interrupt of limitswitches
	if (PIOA->PIO_ISR & LSW1NC){
		readLimitSwitch(&lsw1);
	}
}

void PIOB_Handler(void)
{
	NVIC_ClearPendingIRQ(PIOB_IRQn);
	
	//Interrupt of encoder 1
	if(PIOB->PIO_ISR & (ENC1A | ENC1B))
	{
		readEncoder(&enc1);
	}
	
	//Interrupt of limitswitches
	if (PIOB->PIO_ISR & LSW1NO)
	{
		readLimitSwitch(&lsw1);
	}
}

void PIOC_Handler(void)
{
	NVIC_ClearPendingIRQ(PIOC_IRQn);
	
	//Interrupt of Drive 1: Nfault
	if (PIOC->PIO_ISR & D1NFAULT)
	{
		//Interrupt from Drive 1: Nfault pinchange pending
		if (PIOC->PIO_PDSR & D1NFAULT)
		{
			//Nfault is high, then not reset the drive
			resetClearDrive(1);
		}
		else
		{
			//Nfault is low, then reset the drive
			resetSetDrive(1);
		}
	}
}

void PIOD_Handler(void)
{
	NVIC_ClearPendingIRQ(PIOD_IRQn);
	
	//Interrupt of encoder 2
	if (PIOD->PIO_ISR & (ENC2B | ENC2I))
	{
		readEncoder(&enc2);
	}
	
	//Interrupt of limitswitch
	if (PIOD->PIO_ISR & (LSW2NO | LSW2NC))
	{
		readLimitSwitch(&lsw2);
	}
}