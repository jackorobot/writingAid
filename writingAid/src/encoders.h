/*
 * encoders.h
 *
 * Created: 24-5-2016 13:45:37
 *  Author: Jesse
 */ 


#ifndef ENCODERS_H_
#define ENCODERS_H_

#include "asf.h"

#define ENC1A PIO_PB13
#define ENC1B PIO_PB12
#define ENC1I PIO_PA12

#define ENC2A PIO_PA13
#define ENC2B PIO_PD5
#define ENC2I PIO_PD4

typedef struct {
	uint32_t number; //Encoder hardware number
	int32_t steps; //Encoder steps counted
	int32_t fullRotations; //Encoder full rotations counted
	uint32_t cpr; //Encoder counts per rotation
	bool aSet; //Store if Pin A is set or not
	bool bSet; //Store if Pin B is set or not
	} encoder;

extern void initEncoder(encoder *enc);

extern void readEncoder(encoder *enc);

extern encoder enc1;

extern encoder enc2;

#endif /* ENCODERS_H_ */