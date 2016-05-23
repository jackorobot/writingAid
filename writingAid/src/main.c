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

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "conf_board.h"
#include "conf_clock.h"
#include "serialHandler.h"
#include "motorDriver.h"

int main (void)
{
	//Initialization functions ASF
	sysclk_init();
	board_init();
	
	serialInit();
	
	//Enable all interrupts, last thing to do before starting the main loop
	cpu_irq_enable();
	
	while(1)
	{
		serialPutS("Hello world!\r\n");
	}
}
