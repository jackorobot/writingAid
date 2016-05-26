/*
 * Kinematics.c
 *
 * Created: 4-5-2016 14:23:21
 *  Author: wardb
 */ 

#include "Kinematics.h"
#include <math.h>

extern void calculatePositonMotor(positions *arms){ //float_t positionX, float_t positionY, float_t lenghtArm
	arms->positionSlider1 = arms->positionPenX - sqrtf(pow ( arms->armLength, 2.0) - pow (  arms->positionPenY,2.0));
	arms->positionSlider2 = arms->positionPenX + sqrtf(pow ( arms->armLength, 2.0) - pow ( arms->positionPenY ,2.0));
}

extern void calculatePositionPen(positions *arms){
	arms->positionPenX = (arms->positionSlider1 + arms->positionSlider2)/2.0;
	arms->positionPenY = sqrtf(pow ( arms->armLength,2.0) - pow ( (arms->positionPenX - arms->positionSlider1),2.0)); 
}

extern void calculateNewPositionPen(positions *arms){
	arms->newPositionPenX = (arms->newPositionSlider1 + arms->newPositionSlider2)/2.0;
	arms->newPositionPenY = sqrtf( pow (  arms->armLength,2.0) - pow (  (arms->newPositionPenX - arms->newPositionSlider1), 2.0));
}

extern void calculateRotations(positions * arms){
	arms->movementSlider1 = arms->newPositionSlider1 - arms->positionSlider1; //Positive is right, negative is left 
	arms->movementSlider2 = arms->newPositionSlider2 - arms->positionSlider2; //Positive is right, negative is left
	 
	arms->rotationsMotor1 = arms->movementSlider1 / ( arms->diameter * 3.14 );
	arms->rotationsMotor2 = arms->movementSlider2 / ( arms->diameter * 3.14 );
	 
	arms->motorTicks1 = (uint32_t) arms->rotationsMotor1 * arms->resolution;
	arms->motorTicks2 = (uint32_t) arms->rotationsMotor2 * arms->resolution; 
} 