/*
 * Kinematics.c
 *
 * Created: 4-5-2016 14:23:21
 *  Author: wardb
 */ 

#include "Kinematics.h"
#include <math.h>

struct positions positions1;
float diameter = 15; // [mm]
int resolution = 180; // resolution is the amount of holes in the encoder

void calculatePositonMotor(){ //float_t positionX, float_t positionY, float_t lenghtArm
	positions1.positionSlider1 = positions1.positionPenX - sqrtf(pow ( positions1.armLength, 2.0) - pow (  positions1.positionPenY,2.0));
	positions1.positionSlider2 = positions1.positionPenX + sqrtf(pow ( positions1.armLength, 2.0) - pow ( positions1.positionPenY ,2.0));
}

void calculatePositionPen(){
	positions1.positionPenX = (positions1.positionSlider1 + positions1.positionSlider2)/2.0;
	positions1.positionPenY = sqrtf(pow ( positions1.armLength,2.0) - pow ( (positions1.positionPenX - positions1.positionSlider1),2.0)); 
}

void calculateNewPositionPen(){
	positions1.newPositionPenX = (positions1.newPositionSlider1 + positions1.newPositionSlider2)/2.0;
	positions1.newPositionPenY = sqrtf( pow (  positions1.armLength,2.0) - pow (  (positions1.newPositionPenX - positions1.newPositionSlider1), 2.0));
}

void calculateRotations(){
	positions1.movementSlider1 = positions1.newPositionSlider1 - positions1.positionSlider1; //Positive is right, negative is left 
	positions1.movementSlider2 = positions1.newPositionSlider2 - positions1.positionSlider2; //Positive is right, negative is left
	 
	positions1.rotationsMotor1 = positions1.movementSlider1 / ( diameter * 3.14 );
	positions1.rotationsMotor2 = positions1.movementSlider2 / ( diameter * 3.14 );
	 
	positions1.motorTicks1 = (uint32_t) positions1.rotationsMotor1 * resolution;
	positions1.motorTicks2 = (uint32_t) positions1.rotationsMotor2 * resolution; 
} 