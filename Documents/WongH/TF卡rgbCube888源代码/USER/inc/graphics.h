
#ifndef __graphics_H__
#define __graphics_H__

#include "calculate.h"
#include "effects.h"
#include "LED.h"
#include "stm32f10x.h"
#include "math.h"
#include "CubeFunction.h"
#include "ColourWheel.h"
#include "Text.h"

#define myPI  	3.14159265358979323846
#define myDPI 	1.2732395
#define myDPI2 	0.40528473
#define SIZE 8
#define SIZE2 64
#define SIZE3 512

#define NUMGRAPHICS 13

extern float phase;

extern uint32_t counter;
extern uint32_t gCounter;

extern uint32_t eCounter;
extern uint32_t eCounter2;
extern uint32_t eNum;
extern uint32_t eInterval1;
extern uint32_t eInterval2;
extern uint8_t eFadeout;
extern uint8_t eFadeoutDone;

extern uint8_t mode;
extern uint8_t modeNext;
extern uint8_t modeWait;
extern uint8_t modeWaitUp;
extern int8_t rgb_dir;

typedef struct swarm {
	uint8_t hX;
	uint8_t hY;
	uint8_t hZ;
	uint8_t tX;
	uint8_t tY;
	uint8_t tZ;
	int8_t dirX;
	int8_t dirY;
	int8_t dirZ;
	int8_t oDirX;
	int8_t oDirY;
	int8_t oDirZ;
	int8_t o2DirX;
	int8_t o2DirY;
	int8_t o2DirZ;
	uint8_t R;
	uint8_t G;
	uint8_t B;
} swarm;

void raster(uint8_t R, uint8_t G, uint8_t B, uint32_t speed, uint32_t loops);
void rasterChase(uint8_t R, uint8_t G, uint8_t B, uint32_t speed, uint32_t loops);
void setup(void);
void controlGraphics(void);
void nextGraphic(void);
void prevGraphic(void);
void loop(void);

#endif







