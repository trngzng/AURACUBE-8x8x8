#ifndef __calculate_H__
#define __calculate_H__

#include "LED.h"
#include "stm32f10x.h"

extern int8_t Get_Point[3];																					//获取某个点的坐标
extern const uint8_t Dat_print[];																			//打印函数使用
extern const uint8_t MathSum[];																				//数字,滚动字幕使用,从上至下
extern void Frame(const uint8_t *Data, uint8_t red, uint8_t green, uint8_t blue, int8_t direction);
extern void Move(uint8_t *Data_Move, uint8_t d, uint8_t b, uint8_t c, uint8_t e);

uint8_t Word_Swap(uint8_t temp);																			//高低位转换
//void ColorPoint(int8_t x,int8_t y,int8_t z,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut);				//点的选择与颜色设置
void Funnel_Shape(int8_t number, uint8_t red, uint8_t green, uint8_t blue);									//一点点的形成漏斗的形状函数
void line(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue);																//3维坐标中画线
void Rotat(int16_t number, uint8_t red, uint8_t green, uint8_t blue);										//简单的旋转线
void Line_Change(int8_t number, uint8_t red, uint8_t green, uint8_t blue);									//由线慢慢变化
void Page(int8_t number, uint8_t red, uint8_t green, uint8_t blue, int8_t way);								//像翻书一样的效果，一面一面的显示
void GetPoint(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2, int8_t Number);				//获取两点形成的线中的某个点的坐标，数组Get_Point[3]接收
void PlaneXY(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue, int8_t fill);													//3维坐标中画方框,垂直于xy的平面
void Change_PlaneXY(int8_t number, uint8_t red, uint8_t green, uint8_t blue);								//垂直xy面的拉动效果
void PlaneYZ(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue, int8_t fill);													//3维坐标中画方框,垂直于yz的平面
void PlaneZX(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue, int8_t fill);													//3维坐标中画方框,垂直于zx的平面
void Box(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue, int8_t fill, int8_t Up_Down);									//3维坐标中画箱子
void Box_Change(int8_t number, uint8_t red, uint8_t green, uint8_t blue, int8_t Up_Down);					//4个正方体旋转效果
void DNA_Change(int16_t number, uint8_t red, uint8_t green, uint8_t blue);									//DNA旋转效果
void Waveform(int16_t number, uint8_t red, uint8_t green, uint8_t blue);									//波浪的变化效果
void print(int number, const uint8_t *Data, uint8_t red, uint8_t green, uint8_t blue, char m, int8_t direction);	//打印图案
void Mov_Show(int number, const uint8_t *Data, uint8_t red, uint8_t green, uint8_t blue, int8_t direction);			//滚动字幕
void sphere(int x0, int y0, int z0, int r, uint8_t R, uint8_t G, uint8_t B);

#endif







