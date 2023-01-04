/*
		RGB CUBE Animations MK4
		Nick Schulze September 2013
		HowNotToEngineer.com
*/

#ifndef TEXT_h
#define TEXT_h

#include "graphics.h"
#include "ColourWheel.h"

#define MAX_WORD_LENGTH 80
#define NUM_WORDS 1
#define NUM_WORDS7 1
#define NUM_WORDS_SCROLL 2
#define NUM_CHARS_SCROLL 6
#define letter(x) (x - 'A')

void beginText(void);
void animateText(void);
void beginText7(void);
void animateText7(void);
void animateIT(void);
void scrollText(uint8_t number);
void initScrollText(void);

#endif
