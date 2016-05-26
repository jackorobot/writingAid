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
	float diameter; //mm
	float resolution;
	
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
	
} positions;
extern void calculatePositonMotor(positions *arms);
extern void calculatePositionPen(positions *arms);
extern void calculateNewPositionPen(positions *arms);
extern void calculateRotations(positions * arms);
#endif /* KINEMATICS_H_ */