/*
 * limitSwitch.h
 *
 * Created: 30-5-2016 11:08:39
 *  Author: Jesse
 */ 


#ifndef LIMITSWITCH_H_
#define LIMITSWITCH_H_

#include <asf.h>

#define LSW11NO PIO_PB26
#define LSW11NC PIO_PA14
#define LSW12NO PIO_PA15
#define LSW12NC PIO_PD0
#define LSW21NO PIO_PD1
#define LSW21NC PIO_PD2
#define LSW22NO PIO_PD3
#define LSW22NC PIO_PD6

typedef struct limitSwitch {
	uint32_t axis;
	uint32_t direction;
	bool noContact;
	bool ncContact;
	bool active;
	bool error;
} limitSwitch;

extern limitSwitch lsw11;
extern limitSwitch lsw21;
extern limitSwitch lsw12;
extern limitSwitch lsw22;

extern void initLimitSwitches(void);

extern void readLimitSwitch(limitSwitch *lsw);
#endif /* LIMITSWITCH_H_ */