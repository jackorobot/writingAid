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

#include <asf.h>
#include "conf_board.h"
#include "conf_clock.h"
#include "serialHandler.h"
#include "motorDriver.h"
#include "encoders.h"
#include "Kinematics.h"
#include "limitSwitch.h"

#include <math.h>

//Global data
encoder enc1;
encoder enc2;

limitSwitch lsw11;
limitSwitch lsw12;
limitSwitch lsw21;
limitSwitch lsw22;

uint32_t j;

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
	
	enc1.number = 2;
	enc1.steps = 0;
	enc1.fullRotations = 0;
	enc1.cpr = 200;
	
	initEncoder(&enc2);
	
	initLimitSwitches();
	
	lsw11.axis = 1;
	lsw11.direction = 1;
	readLimitSwitch(&lsw11);
	
	lsw12.axis = 1;
	lsw12.direction = 1;
	readLimitSwitch(&lsw12);
	
	lsw21.axis = 1;
	lsw21.direction = 1;
	readLimitSwitch(&lsw21);
	
	lsw22.axis = 1;
	lsw22.direction = 1;
	readLimitSwitch(&lsw22);
	
	//Enable all interrupts, last thing to do before starting the main loop
	cpu_irq_enable();
	
	float x = 0;
	
	while(1)
	{
		float force = sin(x) * 100.0;
		writeForcePercentage(1, force);
		
		x += 0.01;
		if (x > 8.0)
		{
			x = 0.0;
		}
		for (j=0; j <= 100000; j++);
	}
}
