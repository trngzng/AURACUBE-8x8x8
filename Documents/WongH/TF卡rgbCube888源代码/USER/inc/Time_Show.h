#ifndef __Time_Show_H__
#define __Time_Show_H__

#include "stm32f10x.h"
#include "LED.h"
#include "timer.h"
#include "calculate.h"
#include "snake.h"
#include "adc.h"
#include "fft.h"

void Cartoon(void);																//动画显示
void ReadW25Q64(void);															//读取内存颗粒的数据
void Snake_scrolling(void);														//蛇显示移动
void BOX_move(uint8_t flashorder);

#endif







