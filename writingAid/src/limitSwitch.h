/*
 * limitSwitch.h
 *
 * Created: 30-5-2016 11:08:39
 *  Author: Jesse
 */ 


#ifndef LIMITSWITCH_H_
#define LIMITSWITCH_H_

#include <asf.h>

#define LSW1NO PIO_PB26
#define LSW1NC PIO_PA15
#define LSW2NO PIO_PD1
#define LSW2NC PIO_PD3

typedef struct limitSwitch {
	uint32_t axis;
	bool noContact;
	bool ncContact;
	bool active;
	bool error;
} limitSwitch;

extern limitSwitch lsw1;
extern limitSwitch lsw2;

extern void initLimitSwitches(void);

extern void readLimitSwitch(limitSwitch *lsw);
#endif /* LIMITSWITCH_H_ */