/*
 * motorDriver.h
 *
 * Created: 18-5-2016 15:07:03
 *  Author: Jesse
 */ 


#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_

#include "asf.h"

//IO Definitions Drive 1 Control
#define D1DECAY PIO_PC8
#define D1NRESET PIO_PC9
#define D1APHASE PIO_PC19
#define D1ENBL PIO_PC18
#define D1NSLEEP PIO_PA19
#define D1NFAULT PIO_PA20

//IO Definitions Drive 2 Control
#define D2DECAY PIO_PC15
#define D2NRESET PIO_PC14
#define D2NSLEEP PIO_PC13
#define D2NFAULT PIO_PC12
#define D2APHASE PIO_PB21
#define D2ENBL PIO_PB14

//Current control shift counts
#define D1CUR 1
#define D2CUR 21

extern void initMotorDriver(void);

#endif /* MOTORDRIVER_H_ */