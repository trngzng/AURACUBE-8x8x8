/*********************【 NEC解码头文件 】*******************

	 简介：本程序适用于NCE解码：（9ms+4.5ms）引导码+32位编码。
		   可以定义任意I/O作红外接收脚。

 使用条件：占用一个系统定时器，开启定时器中断

 使用说明：上电初始化函数IR_Init()，
		  在定时器0中断中调用IR_NEC()解码函数，
		  解码有效时，IR_BT=1短按，由用户清0，
		  解码存放：用户码高8位NEC[0]，用户码低8位NEC[1]，操作码NEC[2]，操作码反码NEC[3]。

【供用户调用的函数】
	IR_ENC_Init();			//接收初始化,开启定时器0中断400us,红外线解码（解NEC编码）
***************************************************************/
#ifndef _IR_NEC_H
#define _IR_NEC_H

#include "stm32f10x.h"
#include "LED.h"
#include "calculate.h"
#include "snake.h"

extern unsigned char NEC[4];		         									//解码存放：16位用户码、操作码正反码

void IR_ENC_Init(uint16_t psc);													//红外线解码初始化

/*┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈
函数：红外线NEC周期采样解码法（定时中断，下降沿查询周期时间）
全局变量：IR_BT = 0无效
				 1有效，短按
┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈*/
void IR_NEC(void);

void KeyHandle(void);															//遥控的按键处理


#define  Step 200			     												//红外采样步长：300us

extern unsigned char IR_BT;														//解码效果返回：0无效，1有效

#endif




