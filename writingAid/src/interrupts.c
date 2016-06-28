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
		//Start TC0 running
		TC0->TC_CHANNEL[0]->TC_CCR = TC_CCR_SWTRG;
	}
	
	NVIC_ClearPendingIRQ(PIOA_IRQn);
}

void PIOB_Handler(void)
{
	//Interrupt of encoder 1
	if(PIOB->PIO_ISR & (ENC1A | ENC1B))
	{
		readEncoder(&enc1);
	}
	
	//Interrupt of limitswitches
	if (PIOB->PIO_ISR & LSW1NO)
	{
		//Start TC0 running
		TC0->TC_CHANNEL[0]->TC_CCR = TC_CCR_SWTRG;
	}
	
	NVIC_ClearPendingIRQ(PIOB_IRQn);
}

void PIOC_Handler(void)
{
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
	
	NVIC_ClearPendingIRQ(PIOC_IRQn);
}

void PIOD_Handler(void)
{	
	//Interrupt of encoder 2
	if (PIOD->PIO_ISR & (ENC2B | ENC2I))
	{
		readEncoder(&enc2);
	}
	
	//Interrupt of limitswitch
	if (PIOD->PIO_ISR & (LSW2NO | LSW2NC))
	{
		//Start TC1 running
		TC1->TC_CHANNEL[0]->TC_CCR = TC_CCR_SWTRG;
	}
	
	NVIC_ClearPendingIRQ(PIOD_IRQn);
}

void TC0_Handler()
{
	//Intterrupt of delay timer of limitswitch 1
	readLimitSwitch(&lsw1);
}

void TC1_Handler()
{
	//Interrupt of delay timer of limitswitch 2
	readLimitSwitch(&lsw2);
}