/*
 * Kinematics.h
 *
 * Created: 4-5-2016 14:23:39
 *  Author: wardb
 */ 

#ifndef KINEMATICS_H_
#define KINEMATICS_H_

#include <asf.h>

typedef struct positions {
	uint32_t rotaryEncoder1;
	uint32_t rotaryEncoder2;
	
	
	
	float positionPenX;
	float positionPenY;
	float positionSlider1;
	float positionSlider2;
	
	float newPositionSlider1;
	float newPositionSlider2;
	float newPositionPenX;
	float newPositionPenY;
	
	float armLength; 
	
	float movementSlider1;
	float movementSlider2;
	
	float rotationsMotor1;
	float rotationsMotor2;
	
	uint32_t motorTicks1;
	uint32_t motorTicks2;
	
};
#endif /* KINEMATICS_H_ */