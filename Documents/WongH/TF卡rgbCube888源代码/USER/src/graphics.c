#include "graphics.h"

uint8_t mode = 0;
uint8_t modeNext = 0;
uint8_t modeWait = 0;
uint8_t modeWaitUp = 0;

uint32_t counter = 0;
uint32_t gCounter = 0;
//uint32_t gCounterMax = 3000;
uint32_t gCounterMax = 6000;


uint32_t eCounter = 0;
uint32_t eCounter2 = 0;
uint32_t eNum = 0;
uint8_t eFadeout = 0;
uint8_t eFadeoutDone = 0;
uint8_t boxesCycle = 0;

uint32_t eInterval1 = 0;
uint32_t eInterval2 = 0;

int8_t rgb_dir, rot = 1;
float phase = 0; 			//myPI
float distort = 1;
uint8_t bottom = 0;
uint8_t top = 8;
float narrow = 0;
float speed = 1;
uint8_t speedDelay = 40;
uint8_t speedDirection = 0;
uint8_t narrowDirection = 0;

uint8_t testState;
uint8_t previousTestState;

uint8_t posX, posY, posZ;

uint8_t posHue;
uint8_t posBright;

uint8_t pos2X, pos2Y, pos2Z;

uint8_t pos1Hue;
uint8_t pos1Bright;

uint8_t pos2Hue;
uint8_t pos2Bright;

uint8_t pos3X, pos3Y, pos3Z;

uint8_t pos3Hue;
uint8_t pos3Bright;

uint8_t R, G, B;
uint8_t Tx, Ty, Tz = 0;
uint32_t TLoops = 0;
uint32_t TMax = 50000;
uint8_t TDone = 0;

uint8_t posIT = 0;

float X, Y, Z = 0;

float vXpos, vYpos, vZpos = 0;
float vX, vY, vZ = 0;
int vDir = 0;

float vXpos2, vYpos2, vZpos2 = 0;
float vX2, vY2, vZ2 = 0;
int vDir2 = 0;

uint8_t pos;
uint8_t delaya;
uint8_t delayb;
uint8_t delayc;
uint32_t delaymax;

uint8_t xPos;
uint8_t yPos;
uint8_t zPos;

uint8_t i;
uint8_t y;

uint8_t z;
uint8_t a;

swarm swarms[26];
uint8_t numSwarms = 0;
uint8_t createSwarms = 12;

uint8_t boxPos[8][5];
uint8_t lastToMove = 0;
uint8_t numBoxes = 5;

#define LIGHTNINGINTERVAL 100 // How many raindrops between random lightning strikes, on average
#define MAXLIGHTNING 3       // Maximum number of flashes per lightning strike
#define SHOWCLOUDS 1         // Display a "cloud" layer at the top and grass at the bottom

uint8_t drop1XPos;
uint8_t drop1YPos;
uint8_t drop1ZPos;

uint8_t drop2XPos;
uint8_t drop2YPos;
uint8_t drop2ZPos;

uint8_t drop3XPos;
uint8_t drop3YPos;
uint8_t drop3ZPos;

uint8_t drop4XPos;
uint8_t drop4YPos;
uint8_t drop4ZPos;

uint8_t drop5XPos;
uint8_t drop5YPos;
uint8_t drop5ZPos;

void randomTest()
{
	set(0, 0, 0, random(255), random(255), random(255));
	delay(200);
}

void rasterOnce(uint8_t R, uint8_t G, uint8_t B, uint32_t speed)
{
	uint32_t x, y, z;
	for (z = 0; z < 8; z++)
	{
		for (y = 0; y < 8; y++)
		{
			for (x = 0; x < 8; x++)
			{
				set(x, y, z, R, G, B);
				delay(speed);
				clear(x, y, z);
			}
		}
	}
}


void raster(uint8_t R, uint8_t G, uint8_t B, uint32_t speed, uint32_t loops)
{
	uint32_t x;
	clearAll();
	for (x = 0; x < loops; x++)
		rasterOnce(R, G, B, speed);
}

void rasterChaseOnce(uint8_t R, uint8_t G, uint8_t B, uint32_t speed)
{
	uint32_t x, y, z, xx, yy, zz;
	for (z = 0; z < 8; z++)
	{
		for (y = 0; y < 8; y++)
		{
			for (x = 0; x < 8; x++)
			{
				zz = z;
				if (y % 2 == 0)
					xx = x;
				else
					xx = 7 - x;

				if (z % 2 == 0)
					yy = y;
				else
					yy = 7 - y;
				set(xx, yy, zz, R, G, B);
				delay(speed);
				clear(xx, yy, zz);
			}
		}
	}
}

void rasterChaseDimOnce(uint8_t R, uint8_t G, uint8_t B, uint32_t speed, uint8_t brightness, uint8_t loops)
{
	uint32_t x, y, z, xx, yy, zz;
	uint8_t oR, oG, oB;
	uint8_t oldR, oldG, oldB;
	for (z = 0; z < 8; z++)
	{
		for (y = 0; y < 8; y++)
		{
			for (x = 0; x < 8; x++)
			{
				zz = z;
				if (y % 2 == 0)
					xx = x;
				else
					xx = 7 - x;

				if (z % 2 == 0)
					yy = y;
				else
					yy = 7 - y;
				oldR = getR(xx, yy, zz);
				oldG = getG(xx, yy, zz);
				oldB = getB(xx, yy, zz);
				set(xx, yy, zz, R, G, B);
				delay(speed);
				if (oldR == 0 && oldG == 0 && oldB == 0) {
					//dimmer(R,G,B,&oR,&oG,&oB,0.98);
				}
				else
				{
					//dimmer(R,G,B,&oR,&oG,&oB,calcBright);
					hueToRGB(60, brightness, &oR, &oG, &oB);
				}
				set(xx, yy, zz, oR, oG, oB);
			}
		}
	}
}

void rasterChase(uint8_t R, uint8_t G, uint8_t B, uint32_t speed, uint32_t loops)
{
	uint32_t x;
	clearAll();
	for (x = 0; x < loops; x++)
		rasterChaseDimOnce(R, G, B, speed, x, loops);
}

void setup(void)
{
	// Serial port options for control of the Cube using serial commands are:
	// 0: Control via the USB connector (most common).
	// 1: Control via the RXD and TXD pins on the main board.
	// -1: Don't attach any serial port to interact with the Cube.

	//randomSeed(analogRead(0));
	counter = 0;
	mode = 0;

	testState = 0;
	previousTestState = 0;
	pos = 0;
	delaya = 250;
	delayb = 100;
	delayc = 50;
	delaymax = 1000;
	xPos = 0;
	yPos = 0;
	zPos = 0;
	i = 255;
	y = 0;
	z = 0;
	a = 0;
	drop1ZPos = 2;
	drop2ZPos = 0;
	drop3ZPos = 1;
	drop4ZPos = 3;
	drop5ZPos = 4;

	posX = random(8);
	posY = random(8);
	posZ = random(8);
	posHue = random(255);
	posBright = 255;
	pos2X = random(8);
	pos2Y = random(8);
	pos2Z = random(8);
	pos2Hue = random(255);
	pos2Bright = 255;
	pos3Hue = random(255);
	pos3Bright = 255;
	fill_colour_wheel();
}

void move(void) {
	int x, y, z;
	x = random(3);
	y = random(3);
	z = random(3);
	if (x == 1)
	{
		if (posX < 7)
			posX++;
	}
	if (y == 1)
	{
		if (posY < 7)
			posY++;
	}
	if (z == 1)
	{
		if (posZ < 7)
			posZ++;
	}
	if (x == 2)
	{
		if (posX > 0)
			posX--;
	}
	if (y == 2)
	{
		if (posY > 0)
			posY--;
	}
	if (z == 2)
	{
		if (posZ > 0)
			posZ--;
	}
}

void move2(void) {
	int x, y, z;
	x = random(3);
	y = random(3);
	z = random(3);
	if (x == 1)
	{
		if (pos2X < 7)
			pos2X++;
	}
	if (y == 1)
	{
		//mode++;
		if (z == 1)
		{
			if (pos2Z < 7)
				pos2Z++;
		}
		if (x == 2)
		{
			if (pos2X > 0)
				pos2X--;
		}
		if (y == 2)
		{
			if (pos2Y > 0)
				pos2Y--;
		}
		if (z == 2)
		{
			if (pos2Z > 0)
				pos2Z--;
		}
	}
}

void move3(void) {
	int x, y, z;
	x = random(3);
	y = random(3);
	z = random(3);
	if (x == 1)
	{
		if (pos3X < 7) 
			pos3X++; 
	}
	if (y == 1)
	{
		if (pos3Y < 7) 
			pos3Y++; 
	}
	if (z == 1) 
	{
		if (pos3Z < 7) 
			pos3Z++; 
	}
	if (x == 2) 
	{
		if (pos3X > 0) 
			pos3X--; 
	}
	if (y == 2) 
	{
		if (pos3Y > 0) 
			pos3Y--; 
	}
	if (z == 2) 
	{
		if (pos3Z > 0) 
			pos3Z--; 
	}
}

void setOthers()
{
	uint8_t x, y, z;
	uint8_t r1, g1, b1;
	float calB, cal2B, cal3B;
	float dist;
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			for (z = 0; z < 8; z++)
			{
				dist = 0;
				dist = dist + (abs(posX - x));
				dist = dist + (abs(posY - y));
				dist = dist + (abs(posZ - z));
				calB = posBright / (pow(dist, 3) + 1);
				dist = 0;
				dist = dist + (abs(pos2X - x));
				dist = dist + (abs(pos2Y - y));
				dist = dist + (abs(pos2Z - z));
				cal2B = pos2Bright / (pow(dist, 3) + 1);
				dist = 0;
				dist = dist + (abs(pos3X - x));
				dist = dist + (abs(pos3Y - y));
				dist = dist + (abs(pos3Z - z));
				cal3B = pos3Bright / (pow(dist, 3) + 1);

				hueToRGB(posHue, calB, &R, &G, &B);
				r1 = R;
				g1 = G;
				b1 = B;
				hueToRGB(pos2Hue, cal2B, &R, &G, &B);
				r1 = r1 + R;
				g1 = g1 + G;
				b1 = b1 + B;
				hueToRGB(pos3Hue, cal3B, &R, &G, &B);
				r1 = r1 + R;
				g1 = g1 + G;
				b1 = b1 + B;
				if (r1 > 255) r1 = 255;
				if (g1 > 255) g1 = 255;
				if (b1 > 255) b1 = 255;
				set(x, y, z, r1, g1, b1);
				//delay(10);
			}
		}
	}
}

void mover0(void) 
{
	{
		move();
		move2();
		move3();
		setOthers();
		//  cube.set(posX, posY, posZ, WHITE);
		posHue++;
		if (posHue > 255) 
			posHue = 0; 

		pos2Hue++;
		if (pos2Hue > 255) 
			pos2Hue = 0; 

		pos3Hue++;
		if (pos3Hue > 255) 
			pos3Hue = 0; 
		delay(100);
	}
}

void mover2(void) {
	int x, y, z;
	x = random(3);
	y = random(3);
	z = random(3);
	if (x == 1) 
	{
		if (posX < 7) 
			posX++; 
	}
	if (y == 1) 
	{
		if (posY < 7) 
			posY++; 
	}
	if (z == 1) 
	{
		if (posZ < 7)
			posZ++; 
	}
	if (x == 2) 
	{
		if (posX > 0) 
			posX--; 
	}
	if (y == 2) 
	{
		if (posY > 0) 
			posY--; 
	}
	if (z == 2) {
		if (posZ > 0) 
			posZ--; 
	}
}

void setOthers2() {
	uint8_t x, y, z;
	float calB;
	float dist;
	for (x = 0; x < 8; x++) 
	{
		for (y = 0; y < 8; y++)
		{
			for (z = 0; z < 8; z++) 
			{
				dist = 0;
				dist = dist + (abs(posX - x));
				dist = dist + (abs(posY - y));
				dist = dist + (abs(posZ - z));
				calB = posBright / (pow(dist, 2) + 1);
				hueToRGB(posHue, calB, &R, &G, &B);
				set(x, y, z, R, G, B);
			}
		}
	}
}

void run1(void) {
	{
		mover2();
		setOthers2();
		posHue++;
		if (posHue > 255) 
			posHue = 0;

		delay(delaya);
	}
}

void cycleCubeColours()
{

	if (pos == 0)
		setAll(RED);
	if (pos == 1) 
		setAll(GREEN);
	if (pos == 2) 
		setAll(BLUE);
	if (pos == 3)
		setAll(ORANGE);
	if (pos == 4) 
		setAll(PINK);
	if (pos == 5)
		setAll(0x00, 0x44, 0xA);
	pos++;
	if (pos > 5) 
		pos = 0;
	delay(700);
}

void stepThroughLEDs()
{
	setAll(BLACK);
	set(xPos, yPos, zPos, WHITE);
	xPos++;
	if (xPos > 7)
	{
		xPos = 0;
		yPos++;
		if (yPos > 7)
		{
			yPos = 0;
			zPos++;
			if (zPos > 7)
				zPos = 0;
		}
	}
	delay(50);
}


void fadeWhite()
{
	if (y == 0) 
	{
		i--;
		if (i < 1) 
			y = 1;
	}
	else
	{
		i++;
		if (i > 254) 
			y = 0;
	}
	setAll(i, i, i);
	delay(10);
}

void randomPastel()
{
	uint8_t w;
	if (gCounter == 1)
	{
		setEffect("fadein", 0, 0, 0.5);
		setEffect("slide", 15, 0, 0);
		eFadeout = 1;
	}
	if (eFadeoutDone == 1)
	{
		setEffect("slide", 15, 0, 0);
		setEffect("fadeout", 0, 0, 0.5);
	}
	for (w = 0; w < 5; w++)
	{
		set(random(8), random(8), random(8), random(255), random(255), random(255));
		delay(2);
	}
}

void moveUpSetup()
{
	posX = random(8);
	posY = random(8);
	posZ = random(8);
	posHue = random(255);
	posBright = random(255);
	pos2X = random(8);
	pos2Y = random(8);
	pos2Z = random(8);
	pos1Hue = random(255);
	pos1Bright = random(255);
	pos2Hue = random(255);
	pos2Bright = random(255);
	pos3Hue = random(255);
	pos3Bright = random(255);
}

void lightning()
{
	if (random(LIGHTNINGINTERVAL) == 1)
	{
		int lightningFlashes = random(MAXLIGHTNING + 1);
		int i = 0;
		while (i < lightningFlashes)
		{
			setAll(WHITE);
			delay(50);
			setAll(BLACK);
			delay(150);
			i++;
		}
	}
}

/**
 * Display a white cloud layer at the top of the cube
 */
void clouds()
{
	if (SHOWCLOUDS)
	{
		setPlaneY(0, GREEN);
		setPlaneY(7, WHITE);
	}
}

void weather()
{
	if (drop1ZPos == 8)
	{
		drop1XPos = random(8);
		drop1YPos = random(8);
	}

	if (drop2ZPos == 8)
	{
		drop2XPos = random(8);
		drop2YPos = random(8);
	}

	if (drop3ZPos == 8)
	{
		drop3XPos = random(8);
		drop3YPos = random(8);
	}

	if (drop4ZPos == 8)
	{
		drop4XPos = random(8);
		drop4YPos = random(8);
	}

	if (drop5ZPos == 8)
	{
		drop5XPos = random(8);
		drop5YPos = random(8);
	}

	setAll(BLACK);
	clouds();

	if (drop1ZPos > 0)
	{
		drop1ZPos--;
		set(drop1XPos, drop1ZPos, drop1YPos, BLUE);
	}
	else 
		drop1ZPos = 8;


	if (drop2ZPos > 0)
	{
		drop2ZPos--;
		set(drop2XPos, drop2ZPos, drop2YPos, BLUE);
	}
	else
		drop2ZPos = 8;


	if (drop3ZPos > 0)
	{
		drop3ZPos--;
		set(drop3XPos, drop3ZPos, drop3YPos, BLUE);
	}
	else 
		drop3ZPos = 8;


	if (drop4ZPos > 0)
	{
		drop4ZPos--;
		set(drop4XPos, drop4ZPos, drop4YPos, BLUE);
	}
	else 
		drop4ZPos = 8;


	if (drop5ZPos > 0)
	{
		drop5ZPos--;
		set(drop5XPos, drop5ZPos, drop5YPos, BLUE);
	}
	else 
		drop5ZPos = 8;


	lightning();
	delay(40);
}

void rise()
{
	int8_t i = 0;
	int8_t xPos = 0;
	int8_t yPos = 0;
	int8_t zPos = 0;

	while (yPos < 8)
	{
		zPos = 7;
		while (zPos != -1)
		{
			xPos = 0;
			while (xPos < 8)
			{
				set(xPos, yPos, zPos, RED);
				xPos++;
				i++;
				delay_ms(6);
			}
			zPos--;
		}
		yPos++;
	}
}

/**
 * Extinguish one LED at a time, starting from the top
 */
void fall()
{
	int8_t xPos = 7;
	int8_t yPos = 7;
	int8_t zPos = 7;

	while (yPos > -1)
	{
		xPos = 7;
		while (xPos > -1)
		{
			zPos = 7;
			while (zPos > -1)
			{
				set(xPos, yPos, zPos, BLACK);
				zPos--;
				delay_ms(6);
			}
			xPos--;
		}
		yPos--;
	}
}

void heart()
{
	rise();
	delay(40);
	fall();
	delay(100);
	rise();
	delay(40);
	fall();
	delay(delaya);
	delay(random(250));
}

void moveUp()
{
	//  uint8_t r1,g1,b1;
	uint8_t r;
	uint8_t x, y, t;
	//  r1=255;
	//  g1=0;
	//  b1=0;
	x = 0;
	y = 0;
	for (t = 0; t < 12; t++) 
	{
		hueToRGB(posHue, posBright, &R, &G, &B);
		set(x, y, z, R, G, B);
		if (z == 0 && a == 1)
		{
			hueToRGB(pos1Hue, pos1Bright, &R, &G, &B);
			set(x, y, 3, R, G, B);
			hueToRGB(pos2Hue, pos2Bright, &R, &G, &B);
			set(x, y, 2, R, G, B);
			hueToRGB(pos3Hue, pos3Bright, &R, &G, &B);
			set(x, y, 1, R, G, B);
		}
		if (z == 1 && a == 1) 
		{
			hueToRGB(pos2Hue, pos2Bright, &R, &G, &B);
			set(x, y, 3, R, G, B);
			hueToRGB(pos3Hue, pos3Bright, &R, &G, &B);
			set(x, y, 2, R, G, B);
		}
		if (z == 2 && a == 1)
		{
			hueToRGB(pos3Hue, pos3Bright, &R, &G, &B);
			set(x, y, 3, R, G, B);
		}
		if (z == 1)
		{
			hueToRGB(pos1Hue, pos1Bright, &R, &G, &B);
			set(x, y, 0, R, G, B);
		}
		if (z == 2) 
		{
			hueToRGB(pos1Hue, pos1Bright, &R, &G, &B);
			set(x, y, 1, R, G, B);
			hueToRGB(pos2Hue, pos2Bright, &R, &G, &B);
			set(x, y, 0, R, G, B);
		}
		if (z == 3) {
			hueToRGB(pos1Hue, pos1Bright, &R, &G, &B);
			set(x, y, 2, R, G, B);
			hueToRGB(pos2Hue, pos2Bright, &R, &G, &B);
			set(x, y, 1, R, G, B);
			hueToRGB(pos3Hue, pos3Bright, &R, &G, &B);
			set(x, y, 0, R, G, B);
		}
		if (x == 0 && y == 1 && z == 3) 
		{
			for (r = 0; r < 4; r++) 
			{
				hueToRGB(posHue, posBright, &R, &G, &B);
				set(1, 1, r, R, G, B);
				set(1, 2, r, R, G, B);
				set(2, 2, r, R, G, B);
				set(2, 1, r, R, G, B);
			}
		}
		if (x == 0 && y == 1 && z == 0 && a == 1)
		{
			for (r = 0; r < 4; r++)
			{
				hueToRGB(pos1Hue, pos1Bright, &R, &G, &B);
				set(1, 1, r, R, G, B);
				set(1, 2, r, R, G, B);
				set(2, 2, r, R, G, B);
				set(2, 1, r, R, G, B);
			}
		}
		if (x == 0 && y == 1 && z == 1 && a == 1)
		{
			for (r = 0; r < 4; r++) 
			{
				hueToRGB(pos2Hue, pos2Bright, &R, &G, &B);
				set(1, 1, r, R, G, B);
				set(1, 2, r, R, G, B);
				set(2, 2, r, R, G, B);
				set(2, 1, r, R, G, B);
			}
		}
		if (x == 0 && y == 1 && z == 2 && a == 1)
		{
			for (r = 0; r < 4; r++) 
			{
				hueToRGB(pos3Hue, pos3Bright, &R, &G, &B);
				set(1, 1, r, R, G, B);
				set(1, 2, r, R, G, B);
				set(2, 2, r, R, G, B);
				set(2, 1, r, R, G, B);
			}
		}
		delay(100);
		if (t < 3) 
			x++;
		if (t >= 3 && t < 6) 
			y++;
		if (t >= 6 && t < 9)
			x--;
		if (t >= 9)
			y--;
	}
	if (z < 3)
		z++;
	else
	{
		z = 0;
		a = 1;
	}
}

double map(double in, double inMin, double inMax, double outMin, double outMax) {
	double out;
	out = (in - inMin) / (inMax - inMin)*(outMax - outMin) + outMin;
	return out;
}

void sineWave()
{
	uint8_t x, y;
	uint8_t R, G, B;
	if (gCounter == 1)
	{
		setAll(BLACK);
		setEffect("slide", 12, 0, 0);
		eFadeout = 3;
		rgb_dir = 0;
		narrow = 0;
		narrowDirection = 0;
	}
	for (x = 0; x < 8; x++) 
	{
		for (y = 0; y < 8; y++)
		{
			X = myMap(x, 0, 7, -2, 2);
			Y = myMap(y, 0, 7, -2, 2);

			//RECALCULTE PREVIOUS Z
//			Z = mySin(phase - myPI/8 + mySqrt(X*X + Y*Y));
//			Z = myRound(myMap(Z,-1,1,0,7));

			Z = sin(phase - myPI / 8 + sqrt(X * X + Y * Y));
			Z = myRound(myMap(Z, -1, 1, 0, 7));

			//CLEAR PREVIOUS Z
			set(x, Z, y, BLACK);

			//CALCULATE NEXT Z
//			Z = mySin(phase + mySqrt(X*X + Y*Y));
//			Z = myRound(myMap(Z,-1,1,0,7));

			Z = sin(phase + sqrt(X * X + Y * Y));
			Z = myRound(myMap(Z, -1, 1, 0, 7));

			get_colour(colourPos + Z * 10, &R, &G, &B);

			set(x, Z, y, R, G, B); //arrayP[ar(x, y, Z)] = colourWheel.get_colour(colourPos + Z*10);		

		}
	}

	increment_colour_pos(2);

	phase += myPI / 8;
	if (phase >= 2 * myPI) 
		phase -= 2 * myPI;

	delay(35);
}

void spin()
{
	uint8_t x, y, z;
	uint8_t R, G, B;
	if (gCounter == 1)
	{
		setEffect("fadein", 0, 0, 0);
		eFadeout = 2;
	}
	for (x = 0; x < SIZE; x++)
	{
		for (y = 0; y < SIZE; y++) 
		{
			for (z = 0; z < SIZE; z++)
			{
				X = (x - 3.5)*mySin(phase + myMap(y, 0, SIZE, 0, distort*myPI / 2));
				Z = (z - 3.5)*myCos(phase + myMap(y, 0, SIZE, 0, distort*myPI / 2));
				if (myAbs(X - Z) < 0.7)
				{
					get_colour(colourPos + x * 2 + y * 3, &R, &G, &B);
					set(x, z, y, R, G, B); //arrayP[ar(x, y, Z)] = colourWheel.get_colour(colourPos + Z*10);		
				}
				else 
					set(x, z, y, BLACK);
			}
		}
	}

	increment_colour_pos(2);

	distort += 0.02 * rgb_dir;

	if (distort > 1.5 || distort < 0.5)
		rgb_dir *= -1;


	phase += myPI / 10;

	if (phase >= 2 * myPI) 
		phase -= 2 * myPI;
}


void spiral(void)
{
	uint8_t z, i;
	uint8_t R, G, B;

	if (gCounter == 1)
	{
		setEffect("flash", 12, 4, 0);
		setEffect("increase", 0, 0, 0);
		narrow = 0;
	}
	//Calculate frame
	setAll(BLACK);
	for (z = bottom; z < top; z++) 
	{
		for (i = 0; i < 4; i++) 
		{
			Y = myCos(phase + myMap(z, 0, SIZE - 1, 0, 2 * myPI) + i*myPI / 8);
			X = mySin(phase + myMap(z, 0, SIZE - 1, 0, 2 * myPI) + i*myPI / 8);
			Y = myMap(Y, -1.1, 0.9, narrow, (float)SIZE - 1 - narrow);
			X = myMap(X, -1.1, 0.9, narrow, (float)SIZE - 1 - narrow);
			get_colour(colourPos + 10 * z, &R, &G, &B);
			set(X, z, Y, R, G, B);
		}
	}

	increment_colour_pos(2);

	phase += myPI / 5 * speed;
	if (phase >= 2 * myPI) 
		phase -= 2 * myPI;

	delay(50);
}

void spiral2(void)
{
	uint8_t z, i;
	uint8_t R, G, B;
	//Calculate frame
	setAll(BLACK);
	for (z = bottom; z < top; z++) 
	{
		for (i = 0; i < 4; i++)
		{
			Y = myCos(phase + myMap(z, 0, SIZE - 1, 0, 2 * myPI) + i*myPI / 8);
			X = mySin(phase + myMap(z, 0, SIZE - 1, 0, 2 * myPI) + i*myPI / 8);
			Y = myMap(Y, -1.1, 0.9, narrow, (float)SIZE - 1 - narrow);
			X = myMap(X, -1.1, 0.9, narrow, (float)SIZE - 1 - narrow);
			get_colour(colourPos + 10 * z, &R, &G, &B);
			set(X, z, Y, R, G, B);
		}
	}
	increment_colour_pos(2);
}

void runSpiral2()
{
	uint8_t ran = 0;
	if (gCounter == 1)
	{
		speedDelay = 35;
		slideDirX = 0;
		ran = random(2);
		if (ran == 1) 
			slideDirY = 3;
		else 
			slideDirY = 1;
		slideDirZ = 0;
		setEffect("slide", 30, 0, 1);
		eFadeout = 1;
	}
	if (eFadeoutDone == 1)
	{
		slideDirX = 0;
		ran = random(2);
		if (ran == 1) 
			slideDirY = 4;
		else 
			slideDirY = 2;
		slideDirZ = 0;
		setEffect("slide", 30, 0, 1);
	}

	if (speedDirection == 0)
	{
		if (eNum == 0) 
			speedDelay = speedDelay + (speedDelay / 30);
		//if (speedDelay > 60) speedDelay++;
		//if (speedDelay > 90) speedDelay++;
		//if (speedDelay > 120) speedDelay++;
	}
	else
	{
		if (eNum == 0)
			speedDelay = speedDelay - (speedDelay / 30);
		//if (speedDelay > 60) speedDelay--;
	   // if (speedDelay > 90) speedDelay--;speedDelay--;
	   // if (speedDelay > 120) speedDelay--;speedDelay--;speedDelay--;		 
	}
	if (speedDelay < 40) 
		speedDirection = 0;
	if (speedDelay > 120)
	{
		delay(25);
		speedDirection = 1;
		if (rot == 0)
			rot = 1;
		else 
			rot = 0;
		if (narrowDirection == 0)
		{
			narrow--;
			if (narrow < 0)
			{
				narrow = 0;
				narrowDirection = 1;
			}
		}
		else
		{
			narrow++;
			if (narrow > 2)
			{
				narrow = 2;
				narrowDirection = 0;
			}
		}
	}
	spiral2();
	if (rot == 0)
	{
		phase -= myPI / 5 * speed;
		if (phase <= 0)
			phase += 2 * myPI;
	}
	else
	{
		phase += myPI / 5 * speed;
		if (phase >= 2 * myPI) 
			phase -= 2 * myPI;
	}
	delay(speedDelay);
}

void textWelcome()
{
	if (gCounter == 1)
	{
		modeWait = 1;
		beginText();
	}
	animateText();
}

void textCube()
{
	if (gCounter == 1)
	{
		modeWait = 1;
		beginText7();
	}
	animateText7();
}

void textScroll()
{
	if (gCounter == 1)
	{
		initScrollText();
		modeWait = 1;
		posIT = 0;
		setAll(BLACK);
	}
	scrollText(posIT);
	posIT++;

	delay(150);
}

int getRound(float myFloat)
{
	double integral;
	float fraction = (float)modf(myFloat, &integral);

	if (fraction >= 0.5)
		integral += 1;
	if (fraction <= -0.5)
		integral -= 1;

	return (int)integral;
}

void accelerateVelocity(int gravity, float aX, float aY, float aZ)
{
	if (gravity == 1)
	{
		vY += aY / 100;

		if (vYpos < 1 && vDir == 0)
		{
			vY = 0;
			vDir = 1;
		}
		if (vYpos > (SIZE - 1) && vDir == 1)
		{
			vY = 0;
			vDir = 0;
		}
	}
	else
	{
		vX += aX / 100;
		vY += aY / 100;
		vZ += aZ / 100;
	}
}

void moveVelocity(int bounces, int accelerate, int gravity, float aX, float aY, float aZ, int size, int sizeZ)
{
	float newX = vXpos + vX / 100;
	float newY = vYpos + vY / 100;
	float newZ = vZpos + vZ / 100;

	if (newX + size > SIZE || newX - size < 0)
	{
		if (bounces == 1) 
			vX = -vX; 
		else 
			vX = 0; 
	}
	if (newY + size > SIZE || newY - size < 0)
	{
		if (bounces == 1) 
			vY = -vY; 
		else 
			vY = 0; 
	}
	if (newZ + size > SIZE || newZ - size < 0 || newZ - sizeZ < 0)
	{
		if (bounces == 1) 
			vZ = -vZ; 
		else 
			vZ = 0; 
	}
	vXpos += vX / 100;
	vYpos += vY / 100;
	vZpos += vZ / 100;
	if (accelerate == 1)
		accelerateVelocity(gravity, aX, aY, aZ); 
}

void moveVelocity2(int bounces, int accelerate, int gravity, float aX, float aY, float aZ, int size)
{
	float newX = vXpos2 + vX2 / 100;
	float newY = vYpos2 + vY2 / 100;
	float newZ = vZpos2 + vZ2 / 100;

	if (newX + size > SIZE || newX - size < 0)
	{
		if (bounces == 1) 
			vX2 = -vX2; 
		else 
			vX2 = 0; 
	}
	if (newY + size > SIZE || newY - size < 0)
	{
		if (bounces == 1) 
			vY2 = -vY2; 
		else 
			vY2 = 0; 
	}
	if (newZ + size > SIZE || newZ - size < 0)
	{
		if (bounces == 1) 
			vZ2 = -vZ2; 
		else 
			vZ2 = 0; 
	}
	vXpos2 += vX2 / 100;
	vYpos2 += vY2 / 100;
	vZpos2 += vZ2 / 100;
	if (accelerate == 1) 
		accelerateVelocity(gravity, aX, aY, aZ); 
}

void bounceSphere()
{
	if (gCounter == 1)
	{
		vXpos = 4;
		vYpos = 4;
		vZpos = 4;
		vX = 3;
		vY = 8;
		vZ = 4;
		eFadeout = 1;
	}
	if (eFadeoutDone == 1)
	{
		setEffect("fadeout", 0, 0, 0.05);
		setEffect("dissolve", 0, 0, 0);
	}
	setAll(BLACK);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 2, R, 150, B);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 4, R, 1, B);
	delay(6);
	moveVelocity(1, 0, 0, 3, 3, 3, 0, 4);
}

void bounceSphere2()
{
	if (gCounter == 1)
	{
		vXpos = 3;
		vYpos = 4;
		vZpos = 4;
		vX = 3;
		vY = 8;
		vZ = 4;

		vXpos2 = 2;
		vYpos2 = 4;
		vZpos2 = 2;
		vX2 = 4;
		vY2 = 7;
		vZ2 = 4;
		//setEffect("showboth",0,0,0);
		setEffect("stripe", 20, 0, 0);
	}
	//setLED=0;
	setAll(BLACK);
	//sphere(getRound(vXpos),getRound(vYpos),getRound(vZpos),2,40,80,90);
	//sphere(getRound(vXpos),getRound(vYpos),getRound(vZpos),2,YELLOW);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 2, 255, 100, 0);
	//sphere(getRound(vXpos2),getRound(vYpos2),getRound(vZpos2),2,90,20,40);
  //setLED=1;
  //setAll(BLACK);
	sphere(getRound(vXpos2), getRound(vYpos2), getRound(vZpos2), 2, 255, 1, 255);
	//sphere(getRound(vXpos2),getRound(vYpos2),getRound(vZpos2),2,0,255,255);
	delay(10);
	moveVelocity(1, 0, 0, 3, 3, 3, 2, 0);
	moveVelocity2(1, 0, 0, 3, 3, 3, 2);
}

void drawSpheres2()
{
	if (gCounter == 1)
	{
		setEffect("undissolve", 0, 0, 0);
		modeWait = 1;
		vXpos = 4;
		vYpos = 4;
		vZpos = 4;
		B = random(255);
		R = random(255);
	}
	delay(1200);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 2, R, 200, B);
	delay(1200);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 4, R, 0, B);
	delay(1200);
	delay(100);
}

void drawSpheres()
{
	vXpos = 4;
	vYpos = 4;
	vZpos = 4;
	B = random(255);
	R = random(255);
	modeWait = 1;
	setAll(BLACK);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 1, RED);
	delay(800);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 2, R, 200, B);
	delay(800);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 3, 80, 160, 40);
	delay(800);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 4, R, 0, B);
	delay(800);
	setAll(BLACK);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 3, 80, 160, 40);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 2, R, 200, B);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 1, RED);
	delay(800);
	setAll(BLACK);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 2, R, 200, B);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 1, RED);
	delay(800);
	setAll(BLACK);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 1, RED);
	delay(800);
	setAll(BLACK);
	setEffect("undissolve", 0, 0, 0);
	setEffect("fadein", 0, 0, 0.5);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 2, R, 200, B);
	sphere(getRound(vXpos), getRound(vYpos), getRound(vZpos), 4, R, 0, B);
	while (eNum != 0)
	{
		// wait for undissolve
		delay(100);
	}
	modeWaitUp = 1;
	delay(200);
}

void draw()
{
	set(0, 0, 0, 255, 0, 0);
	delay(2000);
	set(0, 0, 0, 0, 255, 0);
	delay(2000);
	set(0, 0, 0, 0, 0, 255);
	delay(2000);
	setAdd = 1;
	clear(0, 0, 0);
	set(0, 0, 0, 255, 0, 0);
	delay(2000);
	set(0, 0, 0, 0, 255, 0);
	delay(2000);
	set(0, 0, 0, 0, 0, 255);
	delay(2000);
	set(0, 0, 0, 255, 0, 0);
	delay(2000);
	set(0, 0, 0, 0, 255, 0);
	delay(2000);
	set(0, 0, 0, 0, 0, 255);
	delay(2000);
	setAdd = 0;
	modeWaitUp = 1;
	delay(2000);
}

void nextGraphic()
{
	showLED = 3;
	counter = 0;
	modeWait = 0;
	modeWaitUp = 0;
	eCounter = 0;
	eCounter2 = 0;
	setAdd = 0;
	eNum = 0;
	eFadeout = 0;
	eFadeoutDone = 0;
	setLED = 0;
	setAll(BLACK);
	setLED = 1;
	setAll(BLACK);
	setLED = 2;
	setAll(BLACK);
	setLED = 0;
	modeNext = 1;
}

void prevGraphic()
{
	showLED = 3;
	counter = 0;
	modeWait = 0;
	modeWaitUp = 0;
	eCounter = 0;
	eCounter2 = 0;
	setAdd = 0;
	eNum = 0;
	eFadeout = 0;
	eFadeoutDone = 0;
	setLED = 0;
	setAll(BLACK);
	setLED = 1;
	setAll(BLACK);
	setLED = 2;
	setAll(BLACK);
	setLED = 0;
	modeNext = 2;
}

void checkFade()
{
	if (eFadeout == 0 || eFadeoutDone == 3)
		nextGraphic();

	if (eFadeout == 1)
	{
		// roll your own fade out. You must set it !
		if (counter == gCounterMax + 1)
			eFadeoutDone = 1;
	}
	if (eFadeout == 2)
	{
		if (counter == gCounterMax + 1)
		{
			eFadeoutDone = 1;
			setEffect("fadeout", 0, 0, 0);
		}
	}
	if (eFadeout == 3)
	{
		if (counter == gCounterMax + 1)
		{
			eFadeoutDone = 1;
			setEffect("slide", 0, 0, 0);
		}
	}
	if (eFadeout == 4)
	{
		if (counter == gCounterMax + 1)
		{
			eFadeoutDone = 1;
			setEffect("dissolve", 0, 0, 0);
		}
	}
	if (eFadeout > 4)
	{
		setAll(GREEN);
		delay(1000);
		eFadeoutDone = 3;
	}
}

void controlGraphics()
{
	if (eNum > 0 || fadeMax != 100)
		doEffect();
	else
	{
		if (inFadeMax == 1)
		{
			showLED = 0;
			inFadeMax = 0;
		}
	}

	if (modeWait)
	{
		if (modeWaitUp)
			checkFade();
	}
	else
	{
		counter++;
		if (counter > gCounterMax)
			checkFade();
	}
}

void moveFind(uint8_t direction, uint8_t near)
{
	int found = 0;
	TLoops = 0;
	while (!found)
	{
		TLoops++;
		if (TLoops > TMax)
		{
			TDone = 1;
			found = 1;
		}
		Tx = random8();
		Ty = random8();
		Tz = random8();
		//		  if ((direction==0 && Ty-near > 0) || (direction==1 && Ty+near <7))
		if ((direction == 0 && Ty > 0) || (direction == 1 && Ty < 7))
		{
			if (near)
			{
				if (direction == 0)
				{
					if (!isClear(setLED, Tx, Ty, Tz))
					{
						if (isClear(1, Tx, Ty - 1, Tz))
							found = 1;
					}
				}
				else
				{
					if (!isClear(setLED, Tx, Ty, Tz))
					{
						if (isClear(1, Tx, Ty + 1, Tz))
							found = 1;
					}
				}
			}
			else
			{
				if (!isClear(setLED, Tx, Ty, Tz))
					found = 1;
			}
		}
	}
}

void changeColour(uint8_t direction, int8_t y)
{
	if (direction)
	{
		if (B < 205)
			B += 50;
		else 
			B = 255;
		if (G > 50)
			G -= 50;
		else
			G = 0;
	}
	else
	{
		if (G < 205) 
			G += 50;
		else
			G = 255;
		if (B > 50) 
			B -= 50;
		else
			B = 0;
	}
}

void moveTowards(uint8_t direction, uint8_t near, uint8_t random, uint8_t changeCol)
{
	if ((Tx == 0 && Ty == 0 && Tz == 0) || random)
		moveFind(direction, near);
	else
	{
		if (!((direction == 0 && Ty - near > 0) || (direction == 1 && Ty + near < 7)))
			moveFind(direction, near);
	}
	if (!TDone)
	{
		R = getR(Tx, Ty, Tz);
		G = getG(Tx, Ty, Tz);
		B = getB(Tx, Ty, Tz);
		set(Tx, Ty, Tz, BLACK);
		if (direction == 0)
		{
			if (Ty == 0)
				Ty = 1;
			Ty = Ty - 1;
		}
		else
		{
			Ty = Ty + 1;
			if (Ty > 7)
				Ty = 7;
		}
		if (changeCol)
			changeColour(direction, Ty);
		set(Tx, Ty, Tz, R, G, B);
		delay(30);
	}
}

void drawRandom()
{
	uint8_t x, y;
	uint8_t R, G, B;
	for (i = 1; i < 20; i++)
	{
		x = random8();
		y = random8();
		randomColour(&R, &G, &B);
		if (isClear(setLED, x, 0, y) && isClear(setLED, x, 1, y) && isClear(setLED, x, 6, y) && isClear(setLED, x, 7, y)) set(x, 0, y, R, G, B);
		x = random8();
		y = random8();
		randomColour(&R, &G, &B);
		if (isClear(setLED, x, 0, y) && isClear(setLED, x, 1, y) && isClear(setLED, x, 6, y) && isClear(setLED, x, 7, y)) set(x, 1, y, R, G, B);
		x = random8();
		y = random8();
		randomColour(&R, &G, &B);
		if (isClear(setLED, x, 0, y) && isClear(setLED, x, 1, y) && isClear(setLED, x, 6, y) && isClear(setLED, x, 7, y)) set(x, 7, y, R, G, B);
		x = random8();
		y = random8();
		randomColour(&R, &G, &B);
		if (isClear(setLED, x, 0, y) && isClear(setLED, x, 1, y) && isClear(setLED, x, 6, y) && isClear(setLED, x, 7, y)) set(x, 6, y, R, G, B);
	}
	copyBuffer(0, 1); // store the start position
}

void drawAll()
{
	uint8_t x, y;
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			i = random(4);
			if (i > 1)
			{
				i += 4;
				set(x, i, y, BLUE);
			}
			else
				set(x, i, y, GREEN);
		}
	}
	copyBuffer(0, 1); // store the start position
}

void moveToEnd()
{
	if (gCounter == 1)
	{
		setEffect("shake", 20, 0, 0);
		//modeWait=1;
		randomFade();
	}
	setAll(BLACK);
	drawAll();
	TMax = 800;
	TDone = 0;
	while (!TDone)
	{
		moveTowards(1, 1, 0, 1);
	}
	TDone = 0;
	while (!TDone)
	{
		moveTowards(0, 1, 0, 1);
	}
	setAll(BLACK);
	drawRandom();
	TMax = 10000;
	TDone = 0;
	while (!TDone)
	{
		moveTowards(1, 1, 0, 0);
	}
	TMax = 10000;
	TDone = 0;
	while (!TDone)
	{
		moveTowards(0, 1, 0, 0);
	}
	TMax = 10000;
	TDone = 0;
	while (!TDone)
	{
		moveTowards(1, 1, 1, 0);
	}
	TMax = 10000;
	TDone = 0;
	while (!TDone)
	{
		moveTowards(0, 1, 1, 0);
	}
	delay(300);
}

int swarmClear(uint8_t x, uint8_t y, uint8_t z)
{
	uint8_t i, clear = 1;
	for (i = 0; i < numSwarms; i++)
	{
		if (swarms[i].hX == x && swarms[i].hY == y && swarms[i].hZ == z) 
			clear = 0;
		if (swarms[i].tX == x && swarms[i].tY == y && swarms[i].tZ == z)
			clear = 0;
	}
	return clear;
}

int moveTowardsQueen(uint8_t n)
{
	uint8_t notOk = 1;
	int8_t x2, y2, z2 = 0;
	int8_t dX, dY, dZ = 0;
	uint8_t qX, qY, qZ = 0;
	uint8_t ranDir2 = 0;
	qX = swarms[0].hX;
	qY = swarms[0].hY;
	qZ = swarms[0].hZ;
	x2 = swarms[n].hX;
	y2 = swarms[n].hY;
	z2 = swarms[n].hZ;
	dX = swarms[n].dirX;
	dY = swarms[n].dirY;
	dZ = swarms[n].dirZ;
	ranDir2 = random(10);
	// normally continue on path if closer to queen
	if (ranDir2 < 6)
	{
		if ((qX > x2 && dX != -1) || (qX < x2 && dX != 1)) // ok for X 
		{
			if ((qY > y2 && dY != -1) || (qY < y2 && dY != 1)) // ok for Y 			 
			{
				if ((qZ > z2 && dZ != -1) || (qZ < z2 && dZ != 1)) // ok for Z 
					notOk = 0;
			}
		}
	}
	if (notOk)
	{
		// change direction but still no ok
		swarms[n].dirX = swarms[0].o2DirX;
		swarms[n].dirY = swarms[0].o2DirY;
		swarms[n].dirZ = swarms[0].o2DirZ;
		notOk = 1;
	}
	return notOk;
}

void swarmMove(uint8_t n)
{
	uint8_t notOk = 1;
	uint32_t counter = 0;
	uint8_t ranDir = 0;
	int8_t ran = 0;
	int8_t x, y, z = 0;
	int8_t x1, y1, z1 = 0;
	x = swarms[n].hX;
	y = swarms[n].hY;
	z = swarms[n].hZ;
	swarms[n].o2DirX = swarms[n].oDirX;
	swarms[n].o2DirY = swarms[n].oDirY;
	swarms[n].o2DirZ = swarms[n].oDirZ;
	swarms[n].oDirX = swarms[n].dirX;
	swarms[n].oDirY = swarms[n].dirY;
	swarms[n].oDirZ = swarms[n].dirZ;
	if (n > 0)
	{
		// move towards the queen
		moveTowardsQueen(n);
		if (!(notOk))
		{
			x1 = x + swarms[n].dirX;
			y1 = y + swarms[n].dirY;
			z1 = z + swarms[n].dirZ;
		}
	}
	while (notOk)
	{
		if (notOk)
		{
			ranDir = random(10);
			if (ranDir < 9)
			{
				x1 = x + swarms[n].dirX;
				y1 = y + swarms[n].dirY;
				z1 = z + swarms[n].dirZ;
				if (!(x1 < 0 || x1>7 || y1 < 0 || y1>7 || z1 < 0 || z1>7 || (swarms[n].dirX == 0 && swarms[n].dirY == 0 && swarms[n].dirZ == 0)))
					notOk = 0;
			}
		}
		if (notOk)
		{
			ran = random(3) - 1;
			x1 = x + ran;
			swarms[n].dirX = ran;
			ran = random(3) - 1;
			y1 = y + ran;
			swarms[n].dirY = ran;
			ran = random(3) - 1;
			z1 = z + ran;
			swarms[n].dirZ = ran;
			if (x1 >= 0 && x1 < 8 && y1 >= 0 && y1 < 8 && z1 >= 0 && z1 < 8)
			{
				if (!(x1 == x && y1 == y && z1 == z)) //we dont want to find ourself
					notOk = 0;
			}
		}
		counter++;
		if (counter > 10000)
		{
			setAll(RED);
			delay(1000);
			notOk = 0;
		}
	}
	swarms[n].hX = x1;
	swarms[n].hY = y1;
	swarms[n].hZ = z1;
	swarms[n].tX = x;
	swarms[n].tY = y;
	swarms[n].tZ = z;
}

void createTail(uint8_t n, uint8_t x, uint8_t y, uint8_t z, uint8_t *error)
{
	uint8_t notOk = 1;
	//	uint8_t dir=0;
	int8_t ran = 0;
	int8_t x1, y1, z1 = 0;
	*error = 0;
	while (notOk)
	{
		ran = random(3) - 1;
		x1 = x + ran;
		ran = random(3) - 1;
		y1 = y + ran;
		ran = random(3) - 1;
		z1 = z + ran;
		if (x1 >= 0 && x1 < 8 && y1 >= 0 && y1 < 8 && z1 >= 0 && z1 < 8)
		{
			if (!(x1 == x && y1 == y && z1 == z)) //we dont want to find ourself
				notOk = 0;

			if (!(swarmClear(x1, y1, z1)))
				notOk = 0;
		}
	}
	swarms[n].tX = x1;
	swarms[n].tY = y1;
	swarms[n].tZ = z1;
}

void swarmSetup()
{
	int8_t ran;
	uint8_t notOk = 1;
	uint8_t error = 0;
	uint8_t x, y, z, i = 0;
	numSwarms = 0;
	ran = random(3);
	R = 0; G = 0; B = 0;
	if (ran == 0) R = 255;
	if (ran == 1) G = 255;
	if (ran == 2) B = 255;
	ran = random(15);
	createSwarms = 10 + ran;
	for (i = 0; i < createSwarms; i++)
	{
		notOk = 1;
		while (notOk)
		{
			x = random8();
			y = random8();
			z = random8();
			if ((swarmClear(x, y, z)))
			{
				swarms[i].hX = x;
				swarms[i].hY = y;
				swarms[i].hZ = z;
				createTail(i, x, y, z, &error);
				notOk = 0;
			}
		}
		swarms[i].dirX = 0;
		swarms[i].dirY = 0;
		swarms[i].dirZ = 0;
		swarms[i].R = R;
		swarms[i].G = G;
		swarms[i].B = B;
		numSwarms++;
	}
}

void drawSwarms()
{
	uint8_t i;
	for (i = 1; i < numSwarms; i++)
	{
		set(swarms[i].hX, swarms[i].hY, swarms[i].hZ, swarms[i].R, swarms[i].G, swarms[i].B);
		dimmer(swarms[i].R, swarms[i].G, swarms[i].B, &R, &G, &B, 0.87);
		set(swarms[i].tX, swarms[i].tY, swarms[i].tZ, R, G, B);
	}
	set(swarms[0].hX, swarms[0].hY, swarms[0].hZ, WHITE);
	set(swarms[0].tX, swarms[0].tY, swarms[0].tZ, 25, 25, 25);
}


void doSwarm()
{
	uint8_t i;
	if (gCounter == 1)
	{
		setEffect("fadein", 0, 0, 0);
		eFadeout = 2;
		swarmSetup();
	}
	setAll(BLACK);
	drawSwarms();
	for (i = 1; i < numSwarms; i++)
		swarmMove(i);

	swarmMove(0);
	delay(150);
}

const uint8_t around[29] = {
0,1,2,3,4,5,6,7,15,23,31,39,47,55,63,62,61,60,59,58,57,56,48,40,32,24,16,8,0
};

void boxes()
{
	char i, j;
	if (gCounter == 1)
	{
		NumCount = 0;
		boxesCycle = 0;
		modeWait = 1;
		clearAll();
		randomColour(&Color_red, &Color_green, &Color_blue);
	}
	if (NumCount < 50)
	{
		switch (NumCount / 29)
		{
			case 0:
				if (NumCount > 7)
					i = around[NumCount - 8] % 8;
				j = around[NumCount - 8] / 8;
				line(i, j, 0, i, j, 7, 0, 0, 0);
			case 1:
				i = around[NumCount % 29] % 8;
				j = around[NumCount % 29] / 8;
				line(i, j, 0, i, j, 7, Color_red, Color_green, Color_blue);
				break;
		}
	}
	else if (NumCount < 56)
	{
		i = NumCount - 49;
		line(1, 0, i, 6, 0, i, 0, 0, 0);
		line(1, 7, i, 6, 7, i, 0, 0, 0);
		line(0, 1, i, 0, 6, i, 0, 0, 0);
		line(7, 1, i, 7, 6, i, 0, 0, 0);
	}
	else if (NumCount < 62)
	{
		i = (NumCount - 54) / 2;
		Box(i, i, i, 7 - i, 7 - i, 7 - i, Color_red, Color_green, Color_blue, 0, 0);
	}
	else if (NumCount < 70)
	{
		i = (69 - NumCount) / 2;
		Box(i, i, i, 7 - i, 7 - i, 7 - i, 0, 0, 0, 0, 0);
	}

	if (++NumCount >= 70)
	{
		NumCount = 0;
		boxesCycle++;
		if (boxesCycle > 1)
		{
			modeWaitUp = 1;
			delay(100);
		}
	}
	delay(100);
}

void drawBoxes()
{
	if (boxPos[0][0] != 0) 
		Box(0, 0, 0, 3, 3, 3, boxPos[0][1], boxPos[0][2], boxPos[0][3], 1, 0);
	else 
		Box(0, 0, 0, 3, 3, 3, BLACK, 1, 0);

	if (boxPos[1][0] != 0) 
		Box(4, 0, 0, 7, 3, 3, boxPos[1][1], boxPos[1][2], boxPos[1][3], 1, 0);
	else 
		Box(4, 0, 0, 7, 3, 3, BLACK, 1, 0);

	if (boxPos[2][0] != 0) 
		Box(4, 4, 0, 7, 7, 3, boxPos[2][1], boxPos[2][2], boxPos[2][3], 1, 0);
	else 
		Box(4, 4, 0, 7, 7, 3, BLACK, 1, 0);

	if (boxPos[3][0] != 0)
		Box(0, 4, 0, 3, 7, 3, boxPos[3][1], boxPos[3][2], boxPos[3][3], 1, 0);
	else 
		Box(0, 4, 0, 3, 7, 3, BLACK, 1, 0);

	if (boxPos[4][0] != 0) 
		Box(0, 0, 4, 3, 3, 7, boxPos[4][1], boxPos[4][2], boxPos[4][3], 1, 0);
	else 
		Box(0, 0, 4, 3, 3, 7, BLACK, 1, 0);

	if (boxPos[5][0] != 0) 
		Box(4, 0, 4, 7, 3, 7, boxPos[5][1], boxPos[5][2], boxPos[5][3], 1, 0);
	else 
		Box(4, 0, 4, 7, 3, 7, BLACK, 1, 0);

	if (boxPos[6][0] != 0)
		Box(4, 4, 4, 7, 7, 7, boxPos[6][1], boxPos[6][2], boxPos[6][3], 1, 0);
	else 
		Box(4, 4, 4, 7, 7, 7, BLACK, 1, 0);

	if (boxPos[7][0] != 0) 
		Box(0, 4, 4, 3, 7, 7, boxPos[7][1], boxPos[7][2], boxPos[7][3], 1, 0);
	else 
		Box(0, 4, 4, 3, 7, 7, BLACK, 1, 0);
}

void moveSlow(uint8_t from, uint8_t to)
{
	uint32_t delayTm = 100;
	if (from == 0 && to == 1)
	{
		Box(0, 0, 0, 1, 3, 3, BLACK, 1, 0);
		Box(1, 0, 0, 4, 3, 3, boxPos[0][1], boxPos[0][2], boxPos[0][3], 1, 0);
		delay(delayTm);
		Box(0, 0, 0, 2, 3, 3, BLACK, 1, 0);
		Box(2, 0, 0, 5, 3, 3, boxPos[0][1], boxPos[0][2], boxPos[0][3], 1, 0);
		delay(delayTm);
		Box(0, 0, 0, 3, 3, 3, BLACK, 1, 0);
		Box(3, 0, 0, 6, 3, 3, boxPos[0][1], boxPos[0][2], boxPos[0][3], 1, 0);
		delay(delayTm);
	}
	if (from == 0 && to == 3)
	{
		Box(0, 0, 0, 3, 1, 3, BLACK, 1, 0);
		Box(0, 1, 0, 3, 4, 3, boxPos[0][1], boxPos[0][2], boxPos[0][3], 1, 0);
		delay(delayTm);
		Box(0, 0, 0, 3, 2, 3, BLACK, 1, 0);
		Box(0, 2, 0, 3, 5, 3, boxPos[0][1], boxPos[0][2], boxPos[0][3], 1, 0);
		delay(delayTm);
		Box(0, 0, 0, 3, 3, 3, BLACK, 1, 0);
		Box(0, 3, 0, 3, 6, 3, boxPos[0][1], boxPos[0][2], boxPos[0][3], 1, 0);
		delay(delayTm);
	}
	if (from == 0 && to == 4)
	{
		Box(0, 0, 0, 3, 3, 1, BLACK, 1, 0);
		Box(0, 0, 1, 3, 3, 4, boxPos[0][1], boxPos[0][2], boxPos[0][3], 1, 0);
		delay(delayTm);
		Box(0, 0, 0, 3, 3, 2, BLACK, 1, 0);
		Box(0, 0, 2, 3, 3, 5, boxPos[0][1], boxPos[0][2], boxPos[0][3], 1, 0);
		delay(delayTm);
		Box(0, 0, 0, 3, 3, 3, BLACK, 1, 0);
		Box(0, 0, 3, 3, 3, 6, boxPos[0][1], boxPos[0][2], boxPos[0][3], 1, 0);
		delay(delayTm);
	}
	if (from == 1 && to == 0)
	{
		Box(6, 0, 0, 7, 3, 3, BLACK, 1, 0);
		Box(3, 0, 0, 6, 3, 3, boxPos[1][1], boxPos[1][2], boxPos[1][3], 1, 0);
		delay(delayTm);
		Box(5, 0, 0, 7, 3, 3, BLACK, 1, 0);
		Box(2, 0, 0, 5, 3, 3, boxPos[1][1], boxPos[1][2], boxPos[1][3], 1, 0);
		delay(delayTm);
		Box(4, 0, 0, 7, 3, 3, BLACK, 1, 0);
		Box(1, 0, 0, 4, 3, 3, boxPos[1][1], boxPos[1][2], boxPos[1][3], 1, 0);
		delay(delayTm);
	}
	if (from == 1 && to == 2)
	{
		Box(4, 0, 0, 7, 1, 3, BLACK, 1, 0);
		Box(4, 1, 0, 7, 4, 3, boxPos[1][1], boxPos[1][2], boxPos[1][3], 1, 0);
		delay(delayTm);
		Box(4, 0, 0, 7, 2, 3, BLACK, 1, 0);
		Box(4, 2, 0, 7, 5, 3, boxPos[1][1], boxPos[1][2], boxPos[1][3], 1, 0);
		delay(delayTm);
		Box(4, 0, 0, 7, 3, 3, BLACK, 1, 0);
		Box(4, 3, 0, 7, 6, 3, boxPos[1][1], boxPos[1][2], boxPos[1][3], 1, 0);
		delay(delayTm);
	}
	if (from == 1 && to == 5)
	{
		// bugs
		Box(4, 0, 0, 7, 3, 1, BLACK, 1, 0);
		Box(6, 0, 0, 7, 3, 1, BLACK, 1, 0);
		Box(4, 0, 1, 7, 3, 4, boxPos[1][1], boxPos[1][2], boxPos[1][3], 1, 0);
		delay(delayTm);
		Box(4, 0, 0, 7, 3, 2, BLACK, 1, 0);
		Box(5, 0, 0, 7, 3, 2, BLACK, 1, 0);
		Box(4, 0, 2, 7, 3, 5, boxPos[1][1], boxPos[1][2], boxPos[1][3], 1, 0);
		delay(delayTm);
		Box(4, 0, 0, 7, 3, 3, BLACK, 1, 0);
		Box(4, 0, 3, 7, 3, 6, boxPos[1][1], boxPos[1][2], boxPos[1][3], 1, 0);
		delay(delayTm);
	}
	if (from == 4 && to == 5)
	{
		Box(0, 0, 4, 1, 3, 7, BLACK, 1, 0);
		Box(1, 0, 4, 4, 3, 7, boxPos[4][1], boxPos[4][2], boxPos[4][3], 1, 0);
		delay(delayTm);
		Box(0, 0, 4, 2, 3, 7, BLACK, 1, 0);
		Box(2, 0, 4, 5, 3, 7, boxPos[4][1], boxPos[4][2], boxPos[4][3], 1, 0);
		delay(delayTm);
		Box(0, 0, 4, 3, 3, 7, BLACK, 1, 0);
		Box(3, 0, 4, 6, 3, 7, boxPos[4][1], boxPos[4][2], boxPos[4][3], 1, 0);
		delay(delayTm);
	}
	if (from == 4 && to == 7)
	{
		Box(0, 0, 4, 3, 1, 7, BLACK, 1, 0);
		Box(0, 1, 4, 3, 4, 7, boxPos[4][1], boxPos[4][2], boxPos[4][3], 1, 0);
		delay(delayTm);
		Box(0, 0, 4, 3, 2, 7, BLACK, 1, 0);
		Box(0, 2, 4, 3, 5, 7, boxPos[4][1], boxPos[4][2], boxPos[4][3], 1, 0);
		delay(delayTm);
		Box(0, 0, 4, 3, 3, 7, BLACK, 1, 0);
		Box(0, 3, 4, 3, 6, 7, boxPos[4][1], boxPos[4][2], boxPos[4][3], 1, 0);
		delay(delayTm);
	}
	if (from == 4 && to == 0)
	{
		// bugs
		Box(0, 0, 6, 3, 3, 7, BLACK, 1, 0);
		Box(2, 0, 6, 3, 3, 7, BLACK, 1, 0);
		Box(0, 0, 3, 3, 3, 6, boxPos[4][1], boxPos[4][2], boxPos[4][3], 1, 0);
		delay(delayTm);
		Box(0, 0, 5, 3, 3, 7, BLACK, 1, 0);
		Box(2, 0, 5, 3, 3, 6, BLACK, 1, 0);
		Box(0, 0, 2, 3, 3, 5, boxPos[4][1], boxPos[4][2], boxPos[4][3], 1, 0);
		delay(delayTm);
		Box(0, 0, 4, 3, 3, 7, BLACK, 1, 0);
		Box(0, 0, 1, 3, 3, 4, boxPos[4][1], boxPos[4][2], boxPos[4][3], 1, 0);
		delay(delayTm);
	}
	if (from == 5 && to == 4)
	{
		Box(6, 0, 4, 7, 3, 7, BLACK, 1, 0);
		Box(3, 0, 4, 6, 3, 7, boxPos[5][1], boxPos[5][2], boxPos[5][3], 1, 0);
		delay(delayTm);
		Box(5, 0, 4, 7, 3, 7, BLACK, 1, 0);
		Box(2, 0, 4, 5, 3, 7, boxPos[5][1], boxPos[5][2], boxPos[5][3], 1, 0);
		delay(delayTm);
		Box(4, 0, 4, 7, 3, 7, BLACK, 1, 0);
		Box(1, 0, 4, 4, 3, 7, boxPos[5][1], boxPos[5][2], boxPos[5][3], 1, 0);
		delay(delayTm);
	}
	if (from == 5 && to == 6)
	{
		Box(4, 0, 4, 7, 1, 7, BLACK, 1, 0);
		Box(4, 1, 4, 7, 4, 7, boxPos[5][1], boxPos[5][2], boxPos[5][3], 1, 0);
		delay(delayTm);
		Box(4, 0, 4, 7, 2, 7, BLACK, 1, 0);
		Box(4, 2, 4, 7, 5, 7, boxPos[5][1], boxPos[5][2], boxPos[5][3], 1, 0);
		delay(delayTm);
		Box(4, 0, 4, 7, 3, 7, BLACK, 1, 0);
		Box(4, 3, 4, 7, 6, 7, boxPos[5][1], boxPos[5][2], boxPos[5][3], 1, 0);
		delay(delayTm);
	}
	if (from == 5 && to == 1)
	{
		Box(4, 0, 6, 7, 3, 7, BLACK, 1, 0);
		Box(4, 0, 3, 7, 3, 6, boxPos[5][1], boxPos[5][2], boxPos[5][3], 1, 0);
		delay(delayTm);
		Box(4, 0, 5, 7, 3, 7, BLACK, 1, 0);
		Box(4, 0, 2, 7, 3, 5, boxPos[5][1], boxPos[5][2], boxPos[5][3], 1, 0);
		delay(delayTm);
		Box(4, 0, 4, 7, 3, 7, BLACK, 1, 0);
		Box(4, 0, 1, 7, 3, 4, boxPos[5][1], boxPos[5][2], boxPos[5][3], 1, 0);
		delay(delayTm);
	}

	// Next Set

	if (from == 3 && to == 2)
	{
		Box(0, 4, 0, 1, 7, 3, BLACK, 1, 0);
		Box(1, 4, 0, 4, 7, 3, boxPos[3][1], boxPos[3][2], boxPos[3][3], 1, 0);
		delay(delayTm);
		Box(0, 4, 0, 2, 7, 3, BLACK, 1, 0);
		Box(2, 4, 0, 5, 7, 3, boxPos[3][1], boxPos[3][2], boxPos[3][3], 1, 0);
		delay(delayTm);
		Box(0, 4, 0, 3, 7, 3, BLACK, 1, 0);
		Box(3, 4, 0, 6, 7, 3, boxPos[3][1], boxPos[3][2], boxPos[3][3], 1, 0);
		delay(delayTm);
	}
	if (from == 3 && to == 0)
	{
		Box(0, 6, 0, 3, 7, 3, BLACK, 1, 0);
		Box(0, 3, 0, 3, 6, 3, boxPos[3][1], boxPos[3][2], boxPos[3][3], 1, 0);
		delay(delayTm);
		Box(0, 5, 0, 3, 7, 3, BLACK, 1, 0);
		Box(0, 2, 0, 3, 5, 3, boxPos[3][1], boxPos[3][2], boxPos[3][3], 1, 0);
		delay(delayTm);
		Box(0, 4, 0, 3, 7, 3, BLACK, 1, 0);
		Box(0, 1, 0, 3, 4, 3, boxPos[3][1], boxPos[3][2], boxPos[3][3], 1, 0);
		delay(delayTm);
	}
	if (from == 3 && to == 7)
	{
		Box(0, 4, 0, 3, 7, 1, BLACK, 1, 0);
		Box(0, 4, 1, 3, 7, 4, boxPos[3][1], boxPos[3][2], boxPos[3][3], 1, 0);
		delay(delayTm);
		Box(0, 4, 0, 3, 7, 2, BLACK, 1, 0);
		Box(0, 4, 2, 3, 7, 5, boxPos[3][1], boxPos[3][2], boxPos[3][3], 1, 0);
		delay(delayTm);
		Box(0, 4, 0, 3, 7, 3, BLACK, 1, 0);
		Box(0, 4, 3, 3, 7, 6, boxPos[3][1], boxPos[3][2], boxPos[3][3], 1, 0);
		delay(delayTm);
	}
	if (from == 2 && to == 3)
	{
		Box(6, 4, 0, 7, 7, 3, BLACK, 1, 0);
		Box(3, 4, 0, 6, 7, 3, boxPos[2][1], boxPos[2][2], boxPos[2][3], 1, 0);
		delay(delayTm);
		Box(5, 4, 0, 7, 7, 3, BLACK, 1, 0);
		Box(2, 4, 0, 5, 7, 3, boxPos[2][1], boxPos[2][2], boxPos[2][3], 1, 0);
		delay(delayTm);
		Box(4, 4, 0, 7, 7, 3, BLACK, 1, 0);
		Box(1, 4, 0, 4, 7, 3, boxPos[2][1], boxPos[2][2], boxPos[2][3], 1, 0);
		delay(delayTm);
	}
	if (from == 2 && to == 1)
	{
		Box(4, 6, 0, 7, 7, 3, BLACK, 1, 0);
		Box(4, 3, 0, 7, 6, 3, boxPos[2][1], boxPos[2][2], boxPos[2][3], 1, 0);
		delay(delayTm);
		Box(4, 5, 0, 7, 7, 3, BLACK, 1, 0);
		Box(4, 2, 0, 7, 5, 3, boxPos[2][1], boxPos[2][2], boxPos[2][3], 1, 0);
		delay(delayTm);
		Box(4, 4, 0, 7, 7, 3, BLACK, 1, 0);
		Box(4, 1, 0, 7, 4, 3, boxPos[2][1], boxPos[2][2], boxPos[2][3], 1, 0);
		delay(delayTm);
	}
	if (from == 2 && to == 6)
	{ // Box bugs - double clear
		Box(4, 4, 0, 7, 7, 1, BLACK, 1, 0);
		Box(6, 4, 0, 7, 7, 1, BLACK, 1, 0);
		Box(4, 4, 1, 7, 7, 4, boxPos[2][1], boxPos[2][2], boxPos[2][3], 1, 0);
		delay(delayTm);
		Box(4, 4, 0, 7, 7, 2, BLACK, 1, 0);
		Box(5, 4, 0, 7, 7, 2, BLACK, 1, 0);
		Box(4, 4, 2, 7, 7, 5, boxPos[2][1], boxPos[2][2], boxPos[2][3], 1, 0);
		delay(delayTm);
		Box(4, 4, 0, 7, 7, 3, BLACK, 1, 0);
		Box(4, 4, 3, 7, 7, 6, boxPos[2][1], boxPos[2][2], boxPos[2][3], 1, 0);
		delay(delayTm);
	}
	if (from == 7 && to == 6)
	{
		Box(0, 4, 4, 1, 7, 7, BLACK, 1, 0);
		Box(1, 4, 4, 4, 7, 7, boxPos[7][1], boxPos[7][2], boxPos[7][3], 1, 0);
		delay(delayTm);
		Box(0, 4, 4, 2, 7, 7, BLACK, 1, 0);
		Box(2, 4, 4, 5, 7, 7, boxPos[7][1], boxPos[7][2], boxPos[7][3], 1, 0);
		delay(delayTm);
		Box(0, 4, 4, 3, 7, 7, BLACK, 1, 0);
		Box(3, 4, 4, 6, 7, 7, boxPos[7][1], boxPos[7][2], boxPos[7][3], 1, 0);
		delay(delayTm);
	}
	if (from == 7 && to == 4)
	{
		Box(0, 6, 4, 3, 7, 7, BLACK, 1, 0);
		Box(0, 3, 4, 3, 6, 7, boxPos[7][1], boxPos[7][2], boxPos[7][3], 1, 0);
		delay(delayTm);
		Box(0, 5, 4, 3, 7, 7, BLACK, 1, 0);
		Box(0, 2, 4, 3, 5, 7, boxPos[7][1], boxPos[7][2], boxPos[7][3], 1, 0);
		delay(delayTm);
		Box(0, 4, 4, 3, 7, 7, BLACK, 1, 0);
		Box(0, 1, 4, 3, 4, 7, boxPos[7][1], boxPos[7][2], boxPos[7][3], 1, 0);
		delay(delayTm);
	}
	if (from == 7 && to == 3)
	{
		// bugs
		Box(0, 4, 6, 3, 7, 7, BLACK, 1, 0);
		Box(2, 4, 6, 3, 7, 7, BLACK, 1, 0);
		Box(0, 4, 3, 3, 7, 6, boxPos[7][1], boxPos[7][2], boxPos[7][3], 1, 0);
		delay(delayTm);
		Box(0, 4, 5, 3, 7, 7, BLACK, 1, 0);
		Box(2, 4, 5, 3, 7, 6, BLACK, 1, 0);
		Box(0, 4, 2, 3, 7, 5, boxPos[7][1], boxPos[7][2], boxPos[7][3], 1, 0);
		delay(delayTm);
		Box(0, 4, 4, 3, 7, 7, BLACK, 1, 0);
		Box(0, 4, 1, 3, 7, 4, boxPos[7][1], boxPos[7][2], boxPos[7][3], 1, 0);
		delay(delayTm);
	}

	if (from == 6 && to == 7)
	{
		Box(6, 4, 4, 7, 7, 7, BLACK, 1, 0);
		Box(3, 4, 4, 6, 7, 7, boxPos[6][1], boxPos[6][2], boxPos[6][3], 1, 0);
		delay(delayTm);
		Box(5, 4, 4, 7, 7, 7, BLACK, 1, 0);
		Box(2, 4, 4, 5, 7, 7, boxPos[6][1], boxPos[6][2], boxPos[6][3], 1, 0);
		delay(delayTm);
		Box(4, 4, 4, 7, 7, 7, BLACK, 1, 0);
		Box(1, 4, 4, 4, 7, 7, boxPos[6][1], boxPos[6][2], boxPos[6][3], 1, 0);
		delay(delayTm);
	}
	if (from == 6 && to == 5)
	{
		Box(4, 6, 4, 7, 7, 7, BLACK, 1, 0);
		Box(4, 3, 4, 7, 6, 7, boxPos[6][1], boxPos[6][2], boxPos[6][3], 1, 0);
		delay(delayTm);
		Box(4, 5, 4, 7, 7, 7, BLACK, 1, 0);
		Box(4, 2, 4, 7, 5, 7, boxPos[6][1], boxPos[6][2], boxPos[6][3], 1, 0);
		delay(delayTm);
		Box(4, 4, 4, 7, 7, 7, BLACK, 1, 0);
		Box(4, 1, 4, 7, 4, 7, boxPos[6][1], boxPos[6][2], boxPos[6][3], 1, 0);
		delay(delayTm);
	}
	if (from == 6 && to == 2)
	{
		Box(4, 4, 6, 7, 7, 7, BLACK, 1, 0);
		Box(4, 4, 3, 7, 7, 6, boxPos[6][1], boxPos[6][2], boxPos[6][3], 1, 0);
		delay(delayTm);
		Box(4, 4, 5, 7, 7, 7, BLACK, 1, 0);
		Box(4, 4, 2, 7, 7, 5, boxPos[6][1], boxPos[6][2], boxPos[6][3], 1, 0);
		delay(delayTm);
		Box(4, 4, 4, 7, 7, 7, BLACK, 1, 0);
		Box(4, 4, 1, 7, 7, 4, boxPos[6][1], boxPos[6][2], boxPos[6][3], 1, 0);
		delay(delayTm);
	}
}

void moveBoxes2()
{
	uint8_t i, j, k, ran, ran2, found = 0;
	found = 0;
	while (!found)
	{
		ran = random8();
		ran2 = random(3);
		if ((ran != lastToMove) || numBoxes == 1)
		{
			if (ran == 0 && boxPos[ran][0] != 0)
			{
				if (boxPos[1][0] == 0 && ran2 == 0 && boxPos[1][4] != boxPos[0][0])
					found = 1, i = 1;
				if (boxPos[3][0] == 0 && ran2 == 1 && boxPos[3][4] != boxPos[0][0])
					found = 1, i = 3;
				if (boxPos[4][0] == 0 && ran2 == 2 && boxPos[4][4] != boxPos[0][0])
					found = 1, i = 4;
			}
			if (ran == 1 && boxPos[ran][0] != 0)
			{
				if (boxPos[0][0] == 0 && ran2 == 0 && boxPos[0][4] != boxPos[1][0])
					found = 1, i = 0;
				if (boxPos[2][0] == 0 && ran2 == 1 && boxPos[2][4] != boxPos[1][0])
					found = 1, i = 2;
				if (boxPos[5][0] == 0 && ran2 == 2 && boxPos[5][4] != boxPos[1][0])
					found = 1, i = 5;
			}
			if (ran == 2 && boxPos[ran][0] != 0)
			{
				if (boxPos[1][0] == 0 && ran2 == 0 && boxPos[1][4] != boxPos[2][0])
					found = 1, i = 1;
				if (boxPos[3][0] == 0 && ran2 == 1 && boxPos[3][4] != boxPos[2][0])
					found = 1, i = 3;
				if (boxPos[6][0] == 0 && ran2 == 2 && boxPos[6][4] != boxPos[2][0])
					found = 1, i = 6;
			}
			if (ran == 3 && boxPos[ran][0] != 0)
			{
				if (boxPos[0][0] == 0 && ran2 == 0 && boxPos[0][4] != boxPos[3][0])
					found = 1, i = 0;
				if (boxPos[2][0] == 0 && ran2 == 1 && boxPos[2][4] != boxPos[3][0])
					found = 1, i = 2;
				if (boxPos[7][0] == 0 && ran2 == 2 && boxPos[7][4] != boxPos[3][0])
					found = 1, i = 7;
			}
			if (ran == 4 && boxPos[ran][0] != 0)
			{
				if (boxPos[0][0] == 0 && ran2 == 0 && boxPos[0][4] != boxPos[4][0])
					found = 1, i = 0;
				if (boxPos[5][0] == 0 && ran2 == 1 && boxPos[5][4] != boxPos[4][0])
					found = 1, i = 5;
				if (boxPos[7][0] == 0 && ran2 == 2 && boxPos[7][4] != boxPos[4][0])
					found = 1, i = 7;
			}
			if (ran == 5 && boxPos[ran][0] != 0)
			{
				if (boxPos[1][0] == 0 && ran2 == 0 && boxPos[1][4] != boxPos[5][0])
					found = 1, i = 1;
				if (boxPos[4][0] == 0 && ran2 == 1 && boxPos[4][4] != boxPos[5][0])
					found = 1, i = 4;
				if (boxPos[6][0] == 0 && ran2 == 2 && boxPos[6][4] != boxPos[5][0])
					found = 1, i = 6;
			}
			if (ran == 6 && boxPos[ran][0] != 0)
			{
				if (boxPos[2][0] == 0 && ran2 == 0 && boxPos[2][4] != boxPos[6][0])
					found = 1, i = 2;
				if (boxPos[5][0] == 0 && ran2 == 1 && boxPos[5][4] != boxPos[6][0])
					found = 1, i = 5;
				if (boxPos[7][0] == 0 && ran2 == 2 && boxPos[7][4] != boxPos[6][0])
					found = 1, i = 7;
			}
			if (ran == 7 && boxPos[ran][0] != 0)
			{
				if (boxPos[3][0] == 0 && ran2 == 0 && boxPos[3][4] != boxPos[7][0])
					found = 1, i = 3;
				if (boxPos[4][0] == 0 && ran2 == 1 && boxPos[4][4] != boxPos[7][0])
					found = 1, i = 4;
				if (boxPos[6][0] == 0 && ran2 == 2 && boxPos[6][4] != boxPos[7][0])
					found = 1, i = 6;
			}
		}
		k++;
		if (k > 50) // we can't find a good match so find any one
		{
			// clear the previous box histories
			for (j = 0; j < 8; j++)
				boxPos[j][4] = 0;
		}
	}
	boxPos[i][0] = boxPos[ran][0];
	boxPos[i][1] = boxPos[ran][1];
	boxPos[i][2] = boxPos[ran][2];
	boxPos[i][3] = boxPos[ran][3];
	boxPos[i][4] = boxPos[ran][0]; //store the history of what box was here
	boxPos[ran][0] = 0;
	lastToMove = i;
	moveSlow(ran, i);
}

void mBoxes()
{
	uint8_t i, ran, found = 0;
	uint32_t col = 0;
	if (gCounter == 1)
	{
		//randomFade();
		for (i = 0; i < 8; i++)
			boxPos[i][0] = 0;

		col = random32(100);
		numBoxes = random(7) + 1;
		// populate boxes
		for (i = 0; i < numBoxes; i++)
		{
			found = 0;
			while (!found)
			{
				ran = random8();
				if (boxPos[ran][0] == 0)
				{
					boxPos[ran][0] = i + 1;
					get_colour((col + i * 70), &R, &G, &B);
					boxPos[ran][1] = R;
					boxPos[ran][2] = G;
					boxPos[ran][3] = B;
					found = 1;
				}
			}
		}
		drawBoxes();
		delay(300);
	}
	moveBoxes2();
	drawBoxes();
	delay(300);
}
void box2(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2, uint8_t R, uint8_t G, uint8_t B)
{
	uint8_t size = 0;
	size = z2 - z1;
	if (y2 - y1 > size) size = y2 - y1;
	if (x2 - x1 > size) size = x2 - x1;
	size = 3;
	line(x1, y1, z1, x2, y2, z1, R, G, B);
	line(x1, y1, z1 + size, x2, y2, z2 + size, R, G, B);
	line(x1, y1, z1, x2, y1 - (y2 - y1), z2, R, G, B);
	line(x1, y1, z1 + size, x2, y1 - (y2 - y1), z2 + size, R, G, B);
	line(x2, y1 - (y2 - y1), z2, x2 + (x2 - x1), y1, z2, R, G, B);
	line(x2, y1 - (y2 - y1), z1 + size, x2 + (x2 - x1), y1, z2 + size, R, G, B);
	line(x2, y2, z1, x2 + (x2 - x1), y1, z2, R, G, B);
	line(x2, y2, z1 + size, x2 + (x2 - x1), y1, z2 + size, R, G, B);

	line(x1, y1, z1, x1, y1, z1 + size, R, G, B);
	line(x2, y2, z2, x2, y2, z2 + size, R, G, B);
	line(x2, y1 - (y2 - y1), z1, x2, y1 - (y2 - y1), z1 + size, R, G, B);
	line(x2 + (x2 - x1), y1, z1, x2 + (x2 - x1), y1, z1 + size, R, G, B);
}

void spinningBox()
{
	Box(0 + y, 1, 1, 3 + y, 4, 4, BLACK, 0, 0);
	Box(0 + y, 1, 1, 3 + y, 4, 4, RED, 0, 0);
	delay(200);
	Box(0 + y, 1, 1, 3 + y, 4, 4, BLACK, 0, 0);
	box2(0 + y, 3, 1, 2 + y, 5, 1, RED);
	delay(200);
	box2(0 + y, 3, 1, 2 + y, 5, 1, BLACK);
	Box(1 + y, 1, 1, 4 + y, 4, 4, RED, 0, 0);
	delay(200);
	y = y + 1;
	if (y > 5) { y = 0; setAll(BLACK); }
}

void spinBoxes()
{
	if (gCounter == 1)
	{
		modeWait = 1;
		clearAll();
		randomColour(&Color_red, &Color_green, &Color_blue);
	}
	Box_Change(gCounter - 1, Color_red, Color_green, Color_blue, 0);
	delay(80);
	if (gCounter > 108)
	{
		modeWaitUp = 1;
	}
}

void flashtst()
{
	if (gCounter == 1)
	{
		modeWait = 1;
		NumCount = 0;
		setAll(BLACK);
		Color_red = 255;
	}
	//DNA_Change(NumCount,PINK);
	//Box_Change(NumCount,PINK,0); Up to 108
	NumCount++;
	delay(80);
}


void textIT()
{
	uint8_t word = 0;
	if (gCounter == 1)
	{
		modeWait = 1;
		posIT = 0;
	}
	if (gCounter < 50)
	{
		R = 0xff;
		G = 0x14;
		B = 0x44;
	}

	if (gCounter > 52)
		R = G = B = 0;

	if (gCounter > 58)
	{
		word = 1;
		R = 0xff; 
		G = 0x45; 
		B = 0x00;
	}

	if (gCounter > 110)
		R = G = B = 0;

	if (gCounter == 140)
		initScrollText();

	if (gCounter > 140)
	{
		scrollText(gCounter - 141);
		delay(150);
	}

	if (gCounter > 250)
		modeWaitUp = 1;

	if (gCounter < 140)
	{
		setAll(BLACK);
		line(3, 0, 3, 3, 7, 3, R, G, B);
		line(4, 0, 3, 4, 7, 3, R, G, B);
		line(3, 0, 4, 3, 7, 4, R, G, B);
		line(4, 0, 4, 4, 7, 4, R, G, B);
		if (posIT < 6)
		{
			line(3, 7, 4, 0, 7, 6 - posIT, R, G, B);
			line(3, 6, 4, 0, 6, 6 - posIT, R, G, B);
			line(4, 7, 3, 7, 7, posIT + 1, R, G, B);
			line(4, 6, 3, 7, 6, posIT + 1, R, G, B);
			if (!word)
			{
				line(3, 0, 4, 0, 0, 6 - posIT, R, G, B);
				line(3, 1, 4, 0, 1, 6 - posIT, R, G, B);
				line(4, 0, 3, 7, 0, posIT + 1, R, G, B);
				line(4, 1, 3, 7, 1, posIT + 1, R, G, B);
			}
		}
		if (posIT > 5 && posIT < 12)
		{
			line(3, 7, 3, posIT - 5, 7, 0, R, G, B);
			line(3, 6, 3, posIT - 5, 6, 0, R, G, B);
			line(4, 7, 4, 12 - posIT, 7, 7, R, G, B);
			line(4, 6, 4, 12 - posIT, 6, 7, R, G, B);
			if (!word)
			{
				line(3, 0, 3, posIT - 5, 0, 0, R, G, B);
				line(3, 1, 3, posIT - 5, 1, 0, R, G, B);
				line(4, 0, 4, 12 - posIT, 0, 7, R, G, B);
				line(4, 1, 4, 12 - posIT, 1, 7, R, G, B);
			}
		}
		posIT++;
		if (posIT < 6)
		{
			line(3, 7, 3, 0, 7, 6 - posIT, R, G, B);
			line(3, 6, 3, 0, 6, 6 - posIT, R, G, B);
			line(4, 7, 4, 7, 7, posIT + 1, R, G, B);
			line(4, 6, 4, 7, 6, posIT + 1, R, G, B);
			if (!word)
			{
				line(3, 0, 3, 0, 0, 6 - posIT, R, G, B);
				line(3, 1, 3, 0, 1, 6 - posIT, R, G, B);
				line(4, 0, 4, 7, 0, posIT + 1, R, G, B);
				line(4, 1, 4, 7, 1, posIT + 1, R, G, B);
			}
		}
		if (posIT > 5 && posIT < 12)
		{
			line(4, 7, 3, posIT - 5, 7, 0, R, G, B);
			line(4, 6, 3, posIT - 5, 6, 0, R, G, B);
			line(3, 7, 4, 12 - posIT, 7, 7, R, G, B);
			line(3, 6, 4, 12 - posIT, 6, 7, R, G, B);
			if (!word)
			{
				line(4, 0, 3, posIT - 5, 0, 0, R, G, B);
				line(4, 1, 3, posIT - 5, 1, 0, R, G, B);
				line(3, 0, 4, 12 - posIT, 0, 7, R, G, B);
				line(3, 1, 4, 12 - posIT, 1, 7, R, G, B);
			}
		}
		if (posIT > 10) posIT = 0;
		delay(70);
	}
}

void blank()
{
	setAll(BLACK);
	delay(50);
}

void loop()
{
	if (power == 1)
	{
		if (modeNext == 1) // next graphic
		{
			gCounter = 0;
			modeNext = 0;
			showLED = 0;
			setLED = 0;
			mode++;
			fadeLevel = fadeMax;
			if (mode > NUMGRAPHICS)
				mode = 3;
		}
		if (modeNext == 2) // previous graphic
		{
			gCounter = 0;
			modeNext = 0;
			showLED = 0;
			setLED = 0;
			mode--;
			fadeLevel = fadeMax;
			if (mode < 3) 
				mode = NUMGRAPHICS;
		}

		gCounter++;

		/*	if (mode==0) textIT();
			if (mode==1) blank();
			if (mode==2) blank();
			if (mode==3) sineWave();
			if (mode==4) blank();
			if (mode==5) blank();
		if (mode==6) textIT();
			if (mode==7) blank();
			if (mode==8) blank();
			if (mode==9) doSwarm();
			if (mode==10) blank();
			if (mode==11) blank();
	*/
		if (mode == 0)
			textWelcome();
		if (mode == 1) 
			textCube();
		if (mode == 2) 
			textScroll();
		if (mode == 3)
			boxes();
		if (mode == 4)
			spinBoxes();
		if (mode == 5) 
			mBoxes();
		if (mode == 6) 
			sineWave();
		if (mode == 7)
			drawSpheres();
		if (mode == 8)
			bounceSphere();
		if (mode == 9) 
			bounceSphere2();
		if (mode == 10) 
			spin();
		if (mode == 11)
			randomPastel();
		if (mode == 12) 
			doSwarm();
		if (mode == 13)
			runSpiral2();

		//if (mode==7) mover0();
		//if (mode==12) moveToEnd();
		//if (mode==8) spiral();
		//if (mode==9) heart();
		//if (mode==8) spiral();
		//if (mode==9) runSpiral2();
		//spiral();
		//spin();
		//sineWave();
		//if (mode==0) run0();
		//if (mode==1) run1();
		//if (mode==2) cycleCubeColours();
		//if (mode==3) stepThroughLEDs();
		//if (mode==4) fadeWhite();
		//if (mode==5) randomPastel();
		//if (mode==6) heart();
		//if (mode==7) weather();
		//if (mode==8) moveUp();
		//
	}
}

