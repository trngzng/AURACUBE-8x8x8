#include "effects.h"

float fadeLevel = 100;
float fadeMax = 100;
float fadeIncrement = 0.2;

uint8_t slideLevel = 0;
uint8_t slideDirX = 0;
uint8_t slideDirY = 0;
uint8_t slideDirZ = 0;
uint8_t shakeDir = 0;
uint8_t eCounterMax = 6;
uint8_t inFadeMax = 0;
uint8_t stripeN = 0;

void copyBuffer(uint8_t from, uint8_t to)
{
	uint32_t i = 0;
	for (i = 0; i < 1536; i++)
		rgbled[to][i] = rgbled[from][i];
}

void fadeIn()
{
	float level;
	uint32_t i = 0;
	fadeLevel = fadeLevel + fadeIncrement;
	if (fadeLevel > 50) 
		fadeLevel = fadeLevel + 2 * fadeIncrement;
	level = fadeLevel / 100;
	if (fadeLevel >= fadeMax)
	{
		fadeLevel = fadeMax;
		eNum = eNum & 65533;  // fadein done
		if (eNum < 256) 
			showLED = 0;
	}
	if (eNum < 256) // not slide or the others. They will fade itself
	{
		for (i = 0; i < 1536; i++)
			rgbled[2][i] = rgbled[0][i] * level;
	}
}

void fadeOut()
{
	float level;
	uint32_t i = 0;
	fadeLevel = fadeLevel - fadeIncrement;
	if (fadeLevel > 50) 
		fadeLevel = fadeLevel - 2 * fadeIncrement;
	level = fadeLevel / 100;
	if (level < 0)
	{
		eNum = eNum & 65531;  // fadeout done
		if (eNum < 256)
		{
			fadeLevel = fadeMax;
			if (eFadeoutDone == 2) 
				eFadeoutDone = 3;
		}
	}
	if (eNum < 256) // not slide or others. They will fade itself
	{
		for (i = 0; i < 1536; i++)
			rgbled[2][i] = rgbled[0][i] * level;
	}
}

void constantDim()
{
	float level;
	uint32_t i = 0;
	showLED = 2;
	level = fadeMax / 100;
	inFadeMax = 1;
	for (i = 0; i < 1536; i++)
		rgbled[2][i] = rgbled[0][i] * level;
}

void flash()
{
	if (eCounter2 > eInterval1 && showLED == 0)
	{
		showLED = 2;
		eCounter2 = 0;
	}
	if (eCounter2 > eInterval2 && showLED == 2)
	{
		showLED = 0;
		eCounter2 = 0;
	}
}

void invert()
{
	uint32_t i = 0;
	for (i = 0; i < 1536; i++)
		rgbled[2][i] = 255 - rgbled[0][i];
}

void background()
{
	uint32_t i = 0;
	for (i = 0; i < 1536; i++)
	{
		rgbled[2][i] = rgbled[0][i];
		if (rgbled[0][i] == 0) 
			rgbled[2][i] = 30;
	}

}

void blackwhite()
{
	float level;
	int x, y, z = 0;
	uint8_t R, G, B = 0;
	level = fadeLevel / 100;
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			for (z = 0; z < 8; z++)
			{
				R = getR(x, y, z);
				G = getR(x, y, z);
				B = getR(x, y, z);
				if (R > G && R > B)
					G = R, B = R;
				if (G > R && G > B)
					R = G, B = G;
				if (B > G && B > R)
				R = B, G = B; 
				setLED = 2;
				set(x, y, z, R*level, G*level, B*level);
				setLED = 0;
			}
		}
	}
}

void increase()
{
	uint32_t i = 0;
	for (i = 0; i < 1536; i++)
	{
		if (rgbled[0][i] > 0)
		{
			rgbled[2][i] = rgbled[0][i] + 50;
			if (rgbled[2][i] > 255)
				rgbled[2][i] = 255;
		}
		else
			rgbled[2][i] = 0;
	}
}

void decrease()
{
	uint32_t i = 0;
	for (i = 0; i < 1536; i++)
	{
		if (rgbled[0][i] > 0)
		{
			if (rgbled[0][i] > 50)
				rgbled[2][i] = rgbled[0][i] - 50;
			else 
				rgbled[2][i] = 0;
		}
		else
			rgbled[2][i] = 0;
	}
}

void slideMove(int x, int y, int z)
{
	float level;
	int count_i = 0, count_j = 0;
	int count_x, count_y;
	int Ox, Px, Qx, Oy, Py, Qy, Oz, Pz, Qz = 0;
	int PPz = 0;
	level = fadeLevel / 100;
	if (slideDirX == 1 || slideDirX == 3)
		Ox = x, Px = 0, Qx = -1;
	else
		Ox = 7 - x, Px = 7, Qx = 1;

	if (slideDirY == 1 || slideDirY == 3)
		Oy = y, Py = 0, Qy = -1;
	else
		Oy = 7 - y, Py = 7, Qy = 1;

	if (slideDirZ == 1 || slideDirZ == 3)
		Oz = z, Pz = 7, PPz = 0, Qz = -1;
	else
		Oz = 7 - z, Pz = 0, PPz = 7, Qz = 1;

	if (slideDirX == 0)
		count_i = (7 - Ox) * 3, count_x = count_i;

	if (slideDirX == 1 || slideDirX == 2)
		count_i = (7 - Ox) * 3, count_x = ((7 - Ox) - (-(Px - 7) + Qx * slideLevel)) * 3;

	if (slideDirX == 3 || slideDirX == 4)
		count_i = Ox * 3, count_x = (Ox + (-(Px - 7) + Qx * slideLevel)) * 3;

	if (slideDirZ == 0)
		count_i += Oz * 24, count_x += Oz * 24;

	if (slideDirZ == 1 || slideDirZ == 2)
		count_i += Oz * 24; count_x += (Oz + (Pz + Qz * slideLevel)) * 24;

	if (slideDirZ == 3 || slideDirZ == 4)
		count_i += (7 - Oz) * 24, count_x += ((7 - Oz) - (Pz + Qz * slideLevel)) * 24;

	if (slideDirY == 0)
		count_j = 192 * (7 - Oy), count_y = count_j;

	if (slideDirY == 1 || slideDirY == 2)
		count_j = 192 * (7 - Oy), count_y = 192 * ((7 - Oy) - (-(Py - 7) + Qy * slideLevel));

	if (slideDirY == 3 || slideDirY == 4)
		count_j = 192 * Oy, count_y = 192 * (Oy + (-(Py - 7) + Qy * slideLevel));

	if ((Ox <= (Px - Qx * slideLevel) || slideDirX == 0) && 
		(Oy <= (Py - Qy * slideLevel) || slideDirY == 0) && 
		(Oz <= (PPz - Qz * slideLevel) || slideDirZ == 0))
	{
		rgbled[2][rgb_order[count_i + 1] + count_j] = rgbled[0][rgb_order[count_x + 1] + count_y] * level;
		rgbled[2][rgb_order[count_i + 0] + count_j] = rgbled[0][rgb_order[count_x + 0] + count_y] * level;
		rgbled[2][rgb_order[count_i + 2] + count_j] = rgbled[0][rgb_order[count_x + 2] + count_y] * level;
	}
	else
	{
		rgbled[2][rgb_order[count_i + 1] + count_j] = 0;
		rgbled[2][rgb_order[count_i + 0] + count_j] = 0;
		rgbled[2][rgb_order[count_i + 2] + count_j] = 0;
	}
}

void slide()
{
	int x, y, z = 0;
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			for (z = 0; z < 8; z++)
				slideMove(x, y, z);
		}
	}

	if (eCounter2 > eInterval1)
	{
		slideLevel++;
		if (slideLevel > 7)
		{
			eNum = eNum & 65279;
			showLED = 0;
			slideLevel = 0;
			fadeLevel = fadeMax;
			if (eFadeoutDone == 2) 
				eFadeoutDone = 3;
		}
		eCounter2 = 0;
	}
}

void shake()
{
	int x, y, z = 0;
	slideLevel = 1;
	slideDirY = 0;
	if (eCounter2 > eInterval1)
	{
		if (shakeDir == 0)
		{
			if (slideDirX == 0) 
				slideDirX = 2;
			else
				slideDirX = 0;
		}

		if (shakeDir == 2)
		{
			if (slideDirX == 0)
				slideDirX = 4;
			else 
				slideDirX = 0;
		}

		if (shakeDir == 1)
		{
			if (slideDirZ == 0)
				slideDirZ = 2;
			else 
				slideDirZ = 0;
		}

		if (shakeDir == 3)
		{
			if (slideDirZ == 0)
				slideDirZ = 4;
			else 
				slideDirZ = 0;
		}
		if (shakeDir == 0 && slideDirX == 0) 
			shakeDir = 2;
		else
		{
			if (shakeDir == 1 && slideDirZ == 0)
				shakeDir = 3;
			else
			{
				if (shakeDir == 2 && slideDirX == 0)
					shakeDir = 1;
				else
				{
					if (shakeDir == 3 && slideDirZ == 0)
						shakeDir = 0;
				}
			}
		}
		eCounter2 = 0;
	}
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			for (z = 0; z < 8; z++)
				slideMove(x, y, z);
		}
	}
}

int isBlank()
{
	uint32_t i = 0;
	int clear = 1;
	for (i = 0; i < 1536; i++)
		if (rgbled[1][i] != 0)
			clear = 0;

	return clear;
}

int isFull()
{
	uint32_t i = 0;
	int full = 1;
	for (i = 0; i < 1536; i++)
		if (rgbled[1][i] == 0) 
			full = 0;

	return(full);
}

void dissolve()
{
	uint32_t i = 0;
	uint8_t notFound = 1;
	int x, y, z = 0;
	float level;
	level = fadeLevel / 100;
	for (i = 0; i < 1536; i++)
		rgbled[2][i] = (rgbled[0][i] & rgbled[1][i]) * level;

	if (isBlank())
	{
		eCounterMax = 6;
		eNum = eNum & 63487;
		showLED = 0;
		fadeLevel = fadeMax;
		if (eFadeoutDone == 2) 
			eFadeoutDone = 3;
	}
	else
	{
		while (notFound)
		{
			x = random(8);
			y = random(8);
			z = random(8);
			if (!isClear(1, x, y, z))
			{
				setLED = 1;
				clear(x, y, z);
				setLED = 0;
				notFound = 0;
			}
		}
	}
}

void unDissolve()
{
	uint32_t i = 0;
	uint8_t notFound = 1;
	int x, y, z = 0;
	float level;
	level = fadeLevel / 100;
	for (i = 0; i < 1536; i++)
		rgbled[2][i] = (rgbled[0][i] & rgbled[1][i]) * level;

	if (isFull())
	{
		eCounterMax = 6;
		eNum = eNum & 61439;
		showLED = 0;
		fadeLevel = fadeMax;
	}
	else
	{
		while (notFound)
		{
			x = random(8);
			y = random(8);
			z = random(8);
			if (isClear(1, x, y, z))
			{
				setLED = 1;
				set(x, y, z, WHITE);
				setLED = 0;
				notFound = 0;
			}
		}
	}
}

void stripe()
{
	uint32_t i = 0;
	int x, z, col = 0;
	float level;
	level = fadeLevel / 100;
	if (stripeN == 2) col = 2;
	if (eCounter2 > eInterval1 || stripeN == 0)
	{
		eCounter2 = 0;
		if (stripeN == 2)
			stripeN = 1;
		else 
			stripeN = 2;
		//Draw Stripe
		eCounterMax = 1;
		setLED = 1;
		for (z = 0; z < 8; z++)
		{
			for (x = 0; x < 8; x++)
			{
				col++;
				if (col > 3) col = 0;
				if (col < 2)
					line(x, 0, z, x, 7, z, 0, 0, 0);
				else
					line(x, 0, z, x, 7, z, 0, 200, 0);
			}
			/*if (col==0)
				col=1;
			else
				col=0;*/
		}
		setLED = 0;
	}

	for (i = 0; i < 1536; i++)
	{
		//levelN=(float)rgbled[1][i]/100;
		  //rgbled[2][i] = ((float)rgbled[0][i] * levelN) * level;
		if (rgbled[0][i] == 0)
			rgbled[2][i] = 0;
		else
			rgbled[2][i] = (rgbled[0][i] + rgbled[1][i]) * level;
	}
}

void runEffect()
{
	if (fadeMax != 100)
	{
		fadeLevel = fadeMax;
		if (eNum < 256 && eNum != 2 && eNum != 4)// set constant fadelevel
			constantDim();
	}
	if (eNum & 1)
		flash();
	if (eNum & 2)
		fadeIn();
	if (eNum & 4)
		fadeOut();
	if (eNum & 16)
		invert();
	if (eNum & 32)
		background();
	if (eNum & 64)
		increase();
	if (eNum & 128)
		decrease();
	if (eNum & 256)
		slide();
	if (eNum & 512)
		shake();
	if (eNum & 1024)
		blackwhite();
	if (eNum & 2048)
		dissolve();
	if (eNum & 4096)
		unDissolve();
	if (eNum & 8192)
		stripe();
}

void doEffect()
{
	if (eCounter > eCounterMax)
	{
		runEffect();
		eCounter = 0;
		eCounter2++;
	}
	else 
		eCounter++;
}

void randomFade()
{
	uint8_t eFadein;
	eFadein = random(3) + 1;
	if (eFadein == 1) 
		setEffect("fadein", 0, 0, 0);
	if (eFadein == 2)
		setEffect("slide", 0, 0, 0);
	if (eFadein == 3)
		setEffect("undissolve", 0, 0, 0);
	eFadeout = random(3) + 2; // skip none and roll your own
}

void setEffect(char e[12], int interval1, int interval2, float increment)
{
	if (interval1 != 0) 
		eInterval1 = interval1;
	if (interval2 != 0) 
		eInterval2 = interval2;
	if (increment != 0) 
		fadeIncrement = increment;
	if (strncmp(e, "flash", 5) == 0)
		eNum = eNum | 1;

	if (strncmp(e, "fadein", 6) == 0)
	{
		eNum = eNum | 2;
		if (increment == 0)
			fadeIncrement = 0.2;
		fadeLevel = 0;
		showLED = 2;
	}

	if (strncmp(e, "fadeout", 7) == 0)
	{
		eNum = eNum | 4;
		if (increment == 0)
			fadeIncrement = 0.2;
		showLED = 2;
	}

	if (strncmp(e, "showboth", 8) == 0)
		eNum = eNum | 8;

	if (strncmp(e, "invert", 6) == 0)
	{
		eNum = eNum | 16;
		showLED = 2;
	}

	if (strncmp(e, "background", 10) == 0)
	{
		eNum = eNum | 32;
		showLED = 2;
	}

	if (strncmp(e, "increase", 8) == 0)
	{
		eNum = eNum | 64;
		showLED = 2;
	}

	if (strncmp(e, "decrease", 8) == 0)
	{
		eNum = eNum | 128;
		showLED = 2;
	}

	if (strncmp(e, "slide", 5) == 0)
	{
		slideLevel = 0;
		if (interval1 == 0) 
			eInterval1 = 10;
		eNum = eNum | 256;
		showLED = 2;
		if (increment == 0)
		{
			slideDirX = random(8);
			slideDirY = random(8);
			slideDirZ = random(8);
			if (slideDirX > 4)
				slideDirX = 0;
			if (slideDirY > 4) 
				slideDirY = 0;
			if (slideDirZ > 4) 
				slideDirZ = 0;
			if (eFadeoutDone == 1)
			{
				if (slideDirX == 1 || slideDirX == 3)
					slideDirX += 1;
				if (slideDirY == 1 || slideDirY == 3)
					slideDirY += 1;
				if (slideDirZ == 1 || slideDirZ == 3)
					slideDirZ += 1;
			}
			else
			{
				if (slideDirX == 2 || slideDirX == 4)
					slideDirX -= 1;
				if (slideDirY == 2 || slideDirY == 4) 
					slideDirY -= 1;
				if (slideDirZ == 2 || slideDirZ == 4) 
					slideDirZ -= 1;
			}
		}
	}
	if (strncmp(e, "shake", 5) == 0)
	{
		eNum = eNum | 512;
		showLED = 2;
	}

	if (strncmp(e, "blackwhite", 10) == 0)
	{
		eNum = eNum | 1024;
		showLED = 2;
	}

	if (strncmp(e, "dissolve", 8) == 0)
	{
		eCounterMax = 1;
		eNum = eNum | 2048;
		showLED = 2;
		setLED = 1;
		setAll(WHITE);
		setLED = 0;
	}

	if (strncmp(e, "undissolve", 10) == 0)
	{
		eCounterMax = 1;
		eNum = eNum | 4096;
		showLED = 2;
		setLED = 1;
		setAll(BLACK);
		setLED = 0;
	}

	if (strncmp(e, "stripe", 6) == 0)
	{
		eCounterMax = 1;
		stripeN = 0;
		eNum = eNum | 8192;
		showLED = 2;
		setLED = 1;
		setAll(BLACK);
		setLED = 0;
	}
	if (eFadeoutDone == 1) 
		eFadeoutDone = 2; //already set
	runEffect(); // have the initial run
}
