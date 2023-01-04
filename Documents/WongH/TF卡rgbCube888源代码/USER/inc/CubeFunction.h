#ifndef __CubeFunction_H__
#define __CubeFunction_H__

#include "stm32f10x.h"
#include "stdlib.h"
#include "graphics.h"

float mySin(float x);
float myCos(float x);
float myTan(float x);
float mySqrt(float x);
float myMap(float in, float inMin, float inMax, float outMin, float outMax);
int16_t myRound(float x);
float myAbs(float x);

#endif
