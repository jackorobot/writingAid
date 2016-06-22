/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

#include <stdio.h>
#include <asf.h>
#include "conf_board.h"
#include "conf_clock.h"
#include "serialHandler.h"
#include "motorDriver.h"
#include "encoders.h"
#include "Kinematics.h"
#include "limitSwitch.h"

#include <math.h>

void initPosition(void);

//Global data
encoder enc1;
encoder enc2;

limitSwitch lsw1;
limitSwitch lsw2;

int main (void)
{
	//Initialization functions ASF
	sysclk_init();
	board_init();
	
	//Initialize the serial communication handler for USART0
	serialInit();
	
	//Start the initialization of the motor driverd
	initMotorDriver();
	
	//Set and initialize encoder data
	enc1.number = 1;
	enc1.steps = 0;
	enc1.fullRotations = 0;
	enc1.cpr = 200;
	
	initEncoder(&enc1);
	
	enc2.number = 2;
	enc2.steps = 0;
	enc2.fullRotations = 0;
	enc2.cpr = 200;
	
	initEncoder(&enc2);
	
	initLimitSwitches();
	
	lsw1.axis = 1;
	readLimitSwitch(&lsw1);
	
	lsw2.axis = 2;
	readLimitSwitch(&lsw2);
	
	//Enable all interrupts, last thing to do before starting the main loop
	cpu_irq_enable();
	
	//Start PIO Clocks
	PMC->PMC_PCER0 = PMC_PCER0_PID11 | PMC_PCER0_PID12 | PMC_PCER0_PID13 | PMC_PCER0_PID14;
	
	//Enable the drives
	enableDrive(1);
	enableDrive(2);
	
	//Calibrate the rotary encoders
	//calibrate();
	
	while(1)
	{
		//////////////////////////////////////////////////////////////////////////
		// Should not be needed in final product but needed not for motors testing
		// Fixing the interrupt could be solution?
		//////////////////////////////////////////////////////////////////////////
		
		//Reset the drives
		if (PIOA->PIO_PDSR & D1NFAULT)
		{
			resetClearDrive(1);
		}
		else
		{
			resetSetDrive(1);
		}
		
		//Reset the drives
		if (PIOC->PIO_PDSR & D2NFAULT)
		{
			resetClearDrive(2);
		}
		else
		{
			resetSetDrive(2);
		}
		
		//////////////////////////////////////////////////////////////////////////
		//Testing the motor
		//////////////////////////////////////////////////////////////////////////
		writeForcePercentage(1, 10.0);
		writeForcePercentage(2, 10.0);
		
		char buffer[128];
		
		snprintf(buffer, sizeof(buffer), "\e[1;1H\e[?25l");
		serialPutS(buffer);
		
		snprintf(buffer, sizeof(buffer), "============================================\n\r");
		serialPutS(buffer);
		
		//////////////////////////////////////////////////////////////////////////
		// Testing the rotary encoder
		//////////////////////////////////////////////////////////////////////////
		snprintf(buffer, sizeof(buffer), "ENCODER 1: %d steps                \n\r", enc1.steps);
		serialPutS(buffer);
		
		snprintf(buffer, sizeof(buffer), "ENCODER 2: %d steps                \n\r", enc2.steps);
		serialPutS(buffer);
		
		//////////////////////////////////////////////////////////////////////////
		// Testing the limit switches
		//////////////////////////////////////////////////////////////////////////
		snprintf(buffer, sizeof(buffer), "LSW1: %s, %s               \n\r", lsw1.active ? "ACTIVE" : "INACTIVE", lsw1.error ? "ERROR" : "NO ERROR");
		serialPutS(buffer);
		
		snprintf(buffer, sizeof(buffer), "LSW2: %s, %s               \n\r", lsw2.active ? "ACTIVE" : "INACTIVE", lsw2.error ? "ERROR" : "NO ERROR");
		serialPutS(buffer);
		
		//ENDLINE
		snprintf(buffer, sizeof(buffer), "============================================\n\r");
		serialPutS(buffer);
	}
}

void calibrate(void){
	//Drive the motor to the limit switch while the limit switch is not active
	while(!lsw1.active){
		writeForcePercentage(1, 20.0);
	}
	writeForcePercentage(1, 0.0);
	enc1.fullRotations = 0;
	enc1.steps = 0;
	
	while(enc1.steps != 0){
		enc1.fullRotations = 0;
		enc1 .steps = 0;
	}
	
	while(!lsw2.active){
		writeForcePercentage(2, 20.0);
	}
	writeForcePercentage(2, 0.0);
	
	while(enc2.steps != 0){
		enc2.fullRotations = 0;
		enc2.steps = 0;
	}
}