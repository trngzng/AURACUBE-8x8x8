#include "SNAKE.h"

Coordinate Snake[Snake_Long+1];																				//定义贪吃蛇的三维坐标点

/********************************************************
Add_X： 1为向右
Add_X：-1为向左
Add_Y： 1为向后
Add_Y：-1为向前
Add_Z： 1为向下
Add_Z：-1为向上
Add_X，Add_Y都为0时不动
********************************************************/
int8_t Add_X = 0,Add_Y = 0,Add_Z = 0;            															//位移偏移量
#define Start_Long 	3																						//初始长度
uint8_t New_Long = 0;																						//当前长度

/*******************************************************************************
 * @name     :uint8_t Collide(void)
 * @return   :0不撞，1撞
 * @author   :图腾实验室→图腾
 * @details  :判断贪吃蛇是否有碰撞
*******************************************************************************/
uint8_t Collide(void)
{
	int i;
	
	for(i = 2; i < New_Long; i++)																	
	{
		if(Snake[1].Sx == Snake[i].Sx && Snake[1].Sy == Snake[i].Sy && Snake[1].Sz == Snake[i].Sz)								//判断是否撞自己
			return 1;
	} 	
	if(Snake[1].Sx >= 0 && Snake[1].Sx <= 7 && Snake[1].Sy >= 0 && Snake[1].Sy <= 7 && Snake[1].Sz >= 0 && Snake[1].Sz <= 7)	//判断是否撞墙
		return 0 ;
	else 
		return 1;	  											
}

/*******************************************************************************
 * @name     :void Snake_Start(void)
 * @author   :图腾实验室→图腾
 * @details  :蛇身初始化函数
*******************************************************************************/
void Snake_Start(void)
{
	int i = 0;
	New_Long = Start_Long;																					//初始化蛇的长度
	for(i = 0; i < Snake_Long; i++)
	{
		Snake[i].Sx = 0;
		Snake[i].Sy = 0;										
		Snake[i].Sz = 0;																					//清零
	}	
	Snake[1].Sx = 1;
	Snake[1].Sy = 0;														
	Snake[1].Sz = 0;																						//蛇头

	Snake[2].Sx = 0;
	Snake[2].Sy = 0;														
	Snake[2].Sz = 0;																						//蛇尾
	
	Add_X = 0;
	Add_Y = 0;            												
	Add_Z = 0;            																					//位移偏移量置0，蛇不动
}

/*******************************************************************************
 * @name     :void Snake_Above(void)
 * @author   :图腾实验室→图腾
 * @details  :给食物并且判断食物是否在蛇身上面
*******************************************************************************/
void Snake_Above(void)
{
	int i = 1;
Back:
	srand(TIM2->CNT);																						//给随机一个种子取定时器的值，伪随机
	Snake[0].Sx = (char)(rand()%8);																			//试着给出食物
	Snake[0].Sy = (char)(rand()%8);																			//试着给出食物		
	Snake[0].Sz = (char)(rand()%8);																			//试着给出食物		

	i = 1;
	while(i <= New_Long) 																					//判断食物是否在蛇身上面
	{
		if(Snake[i].Sx == Snake[0].Sx && Snake[i].Sy == Snake[0].Sy && Snake[i].Sz == Snake[0].Sz)			//食物出现在蛇的身上，回去再次取随机数
			goto Back;																						
		i++;
	}        											
}

/*******************************************************************************
 * @name     :void Snake_Feed(void)
 * @author   :图腾实验室→图腾
 * @details  :给食物并且判断食物是否在蛇身上面
*******************************************************************************/
void Snake_Feed(void)
{
	if(Snake[1].Sx == Snake[0].Sx && Snake[1].Sy == Snake[0].Sy && Snake[1].Sz == Snake[0].Sz)				//判断是否吃东西
	{
		New_Long++;																							//长度加1--实际就是从蛇的后面增加一个点，蛇头多了一点，使人的错觉是吃了食物
		if(New_Long != Snake_Long+1)																		//判断是否需要重新给食物
			Snake_Above();																					//给食物并且判断食物是否在蛇身上面
		else if(New_Long == Snake_Long+1) 																	//判断是否达到最大长度
		{
			New_Long = Start_Long;																			//给蛇初始化长度
			Snake_Start();																					//蛇身初始化
			Snake_Above();																					//给食物并且判断食物是否在蛇身上面
		}
	}
}

/*******************************************************************************
 * @name     :void Snake_Move(void)
 * @author   :图腾实验室→图腾
 * @details  :贪吃蛇的蛇身移动
*******************************************************************************/
void Snake_Move(void)
{
	int i = 0;
	if(0 != Add_X || 0 != Add_Y || 0 != Add_Z)																//判断是否需要移动
	{
		for(i = New_Long-1; i; i--)													
		{
			Snake[i].Sx = Snake[i-1].Sx;
			Snake[i].Sy = Snake[i-1].Sy;						
			Snake[i].Sz = Snake[i-1].Sz;																	//贪吃蛇的身体移动(从后面向前移动一位)
		}   
		Snake[1].Sx = Snake[2].Sx+Add_X;
		Snake[1].Sy = Snake[2].Sy+Add_Y;                    				
		Snake[1].Sz = Snake[2].Sz+Add_Z;                    												//贪吃蛇的头部移动
	}
}

/*******************************************************************************
 * @name     :void Snake_Show(uint8_t snake_red,uint8_t snake_green,uint8_t snake_blue,uint8_t feeed_red,uint8_t feeed_green,uint8_t feeed_blue)
 * @param    :snake_red   →蛇身的红色
 * @param    :snake_green →蛇身的绿色
 * @param    :snake_blue  →蛇身的蓝色
 * @param    :feeed_red   →食物的红色
 * @param    :feeed_green →食物的绿色
 * @param    :feeed_blue  →食物的蓝色
 * @author   :图腾实验室→图腾
 * @details  :贪吃蛇的显示函数
*******************************************************************************/
void Snake_Show(uint8_t snake_red,uint8_t snake_green,uint8_t snake_blue,uint8_t feeed_red,uint8_t feeed_green,uint8_t feeed_blue)
{
	int i;
	clearAll();																								//清除所有缓存
	for(i = 1; i < New_Long; i++)																			//将蛇身显示出来
		set(Snake[i].Sx,Snake[i].Sy,Snake[i].Sz,snake_red,snake_green,snake_blue);
	set(Snake[0].Sx,Snake[0].Sy,Snake[0].Sz,feeed_red,feeed_green,feeed_blue);						//显示实物
}



