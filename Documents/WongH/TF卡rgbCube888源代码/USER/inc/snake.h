#ifndef _SNAKE_H
#define _SNAKE_H

#include "stdlib.h"
#include "led.h"
#include "calculate.h"

#define Snake_Long 	20  														//最大长度

typedef struct
{
	int8_t Sx;
	int8_t Sy;
	int8_t Sz;
}Coordinate;																	//创建三维坐标的结构体

extern Coordinate Snake[Snake_Long + 1];										//定义贪吃蛇的三维坐标点
extern int8_t Add_X, Add_Y, Add_Z;            									//位移偏移量

uint8_t Collide(void);															//判断贪吃蛇是否有碰撞
void Snake_Start(void);															//蛇身初始化函数
void Snake_Above(void);															//给食物并且判断食物是否在蛇身上面
void Snake_Feed(void);															//判断是否吃食物，吃就长度加1，否则不加，并且判断是否达到最大长度
void Snake_Move(void);															//贪吃蛇的蛇身移动
void Snake_Show(uint8_t snake_red, uint8_t snake_green, uint8_t snake_blue,
	uint8_t feeed_red, uint8_t feeed_green, uint8_t feeed_blue);				//贪吃蛇的显示函数

#endif



