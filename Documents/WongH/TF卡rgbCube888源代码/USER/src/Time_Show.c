#include "time_show.h"


/*******************************************************************************
 * @name     :void flash0(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :一点一点增加，显示漏斗的形状
*******************************************************************************/
void flash0(uint8_t flashorder)
{
	if(++SpeedSum >= 5)																	//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		if(0 == NumCount)
			clearAll();																	//清除所有缓存
		switch(NumCount/64)
		{
			case 0:
			case 1:
				randomColour(&Color_red,&Color_green,&Color_blue);						//取得随机颜色
				Funnel_Shape(NumCount,Color_red,Color_green,Color_blue);				//一点点的形成漏斗的形状
			break;
			case 2:
			case 3:
				Funnel_Shape(NumCount-128,0,0,0);										//一点点的消灭漏斗的形状
			break;
			case 4:
				randomColour(&Color_red,&Color_green,&Color_blue);						//取得随机颜色
				Funnel_Shape(NumCount-256,Color_red,Color_green,Color_blue);			//一点点的形成漏斗的形状
				Funnel_Shape(383-NumCount,Color_red,Color_green,Color_blue);			//一点点的形成漏斗的形状
			break;
			case 5:
				Funnel_Shape(383-NumCount,0,0,0);										//一点点的消灭漏斗的形状
				Funnel_Shape(NumCount-256,0,0,0);										//一点点的消灭漏斗的形状
			break;
			case 6:
				if(NumCount < 392)
					set(0,NumCount-384,0,Color_red,Color_green,Color_blue);	//点的选择与颜色设置
				else
					line(0,0,NumCount-391,0,7,NumCount-391,Color_red,Color_green,Color_blue);	//3维坐标中画线
			break;
		}

		if(++NumCount >= 399)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}

/*******************************************************************************
 * @name     :void flash1(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :前后面一行一行的移动
*******************************************************************************/
void flash1(uint8_t flashorder)
{
	if(++SpeedSum >= 10)																//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		if(0 == NumCount)
		{
			clearAll();																	//清除所有缓存
			randomColour(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
		}
		Line_Change(NumCount,Color_red,Color_green,Color_blue);							//由线慢慢变化
		if(++NumCount >= 32)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}

/*******************************************************************************
 * @name     :void flash2(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :像翻书一样的效果
*******************************************************************************/
void flash2(uint8_t flashorder)
{
	if(++SpeedSum >= 6)																	//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
//		if(0 == NumCount)
//		{
//			clearAll();																	//清除所有缓存
//			randomColor(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
//		}
		switch(NumCount/15)
		{
			case 0:
				if(0 != NumCount)
					Page(NumCount-1,0,0,0,0);											//去掉之前的缓冲区
				Page(NumCount,Color_red,Color_green,Color_blue,0);					//像翻书一样的效果，一面一面的显示
			break;
			case 1:
				if(15 != NumCount)
					Page(30-NumCount,0,0,0,4);										//去掉之前的缓冲区
				Page(29-NumCount,Color_red,Color_green,Color_blue,4);					//像翻书一样的效果，一面一面的显示
			break;
			case 2:
				if(30 != NumCount)
					Page(NumCount-31,0,0,0,5);										//去掉之前的缓冲区
				Page(NumCount-30,Color_red,Color_green,Color_blue,5);					//像翻书一样的效果，一面一面的显示
			break;
			case 3:
				if(45 != NumCount)
					Page(60-NumCount,0,0,0,3);										//去掉之前的缓冲区
				Page(59-NumCount,Color_red,Color_green,Color_blue,3);					//像翻书一样的效果，一面一面的显示
			break;
			case 4:
				if(60 != NumCount)
					Page(NumCount-61,0,0,0,2);										//去掉之前的缓冲区
				Page(NumCount-60,Color_red,Color_green,Color_blue,2);					//像翻书一样的效果，一面一面的显示
			break;
			case 5:
				if(75 != NumCount)
					Page(90-NumCount,0,0,0,6);										//去掉之前的缓冲区
				Page(89-NumCount,Color_red,Color_green,Color_blue,6);					//像翻书一样的效果，一面一面的显示
			break;
			case 6:
				if(90 != NumCount)
					Page(NumCount-91,0,0,0,7);										//去掉之前的缓冲区
				Page(NumCount-90,Color_red,Color_green,Color_blue,7);					//像翻书一样的效果，一面一面的显示
			break;
			case 7:
				if(105 != NumCount)
					Page(120-NumCount,0,0,0,1);										//去掉之前的缓冲区
				Page(119-NumCount,Color_red,Color_green,Color_blue,1);				//像翻书一样的效果，一面一面的显示
			break;
			default:
				if(NumCount < 127)
					line(0,0,127-NumCount,0,7,127-NumCount,BLACK);	//3维坐标中画线
				else
					set(0,NumCount-127,0,Color_red,Color_green,Color_blue);	//点的选择与颜色设置
			break;
		}
		if(++NumCount >= 134)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}	
	
/*******************************************************************************
 * @name     :void flash3(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :垂直xy面的拉动效果
*******************************************************************************/
void flash3(uint8_t flashorder)
{
	if(++SpeedSum >= 10)																//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		if(0 == NumCount)
		{
			clearAll();																	//清除所有缓存
			randomColour(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
		}
		
		if(NumCount < 8)
			set(NumCount,7,7,Color_red,Color_green,Color_blue);				//点的选择与颜色设置
		else if(NumCount < 15)
			line(0,7,14-NumCount,7,7,14-NumCount,Color_red,Color_green,Color_blue);	//3维坐标中画线
		else if(NumCount < 41)
			Change_PlaneXY(NumCount-15,Color_red,Color_green,Color_blue);				//垂直xy面的拉动效果
		if(++NumCount >= 41)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}

/*******************************************************************************
 * @name     :void flash4(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :4个正方体旋转效果
*******************************************************************************/
void flash4(uint8_t flashorder)
{
	if(++SpeedSum >= 15)																//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		if(0 == NumCount)
		{
			clearAll();																	//清除所有缓存
			randomColour(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
		}
		Box_Change(NumCount,Color_red,Color_green,Color_blue,0);						//4个正方体旋转效果
		if(++NumCount >= 108)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}

/*******************************************************************************
 * @name     :void flash5(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :DNA旋转效果
*******************************************************************************/
void flash5(uint8_t flashorder)
{
	if(++SpeedSum >= 5)																	//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		if(15 == NumCount)
		{
			clearAll();																	//清除所有缓存
			randomColour(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
		}
		if(NumCount < 7)
			line(0,0,7-NumCount,7,0,7-NumCount,BLACK);		//3维坐标中画线
		else if(NumCount < 15)
			set(14-NumCount,0,0,BLACK);				//点的选择与颜色设置
		else if(NumCount < 23)
			set(NumCount-15,NumCount-15,0,Color_red,Color_green,Color_blue);	//点的选择与颜色设置
		else if(NumCount < 30)
			line(0,0,NumCount-22,7,7,NumCount-22,Color_red,Color_green,Color_blue);	//3维坐标中画线
		else if(NumCount < 285)
			DNA_Change(NumCount-30,Color_red,Color_green,Color_blue);					//DNA旋转效果
		if(++NumCount >= 285)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}

/*******************************************************************************
 * @name     :void flash6(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :波浪的变化效果
*******************************************************************************/
void flash6(uint8_t flashorder)
{
	if(++SpeedSum >= 10)																//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		if(0 == NumCount)
		{
			clearAll();																	//清除所有缓存
			randomColour(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
		}
		Waveform(NumCount,Color_red,Color_green,Color_blue);							//波浪的变化效果
		if(++NumCount >= 204)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}

/*******************************************************************************
 * @name     :void flash7(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :打印图案
*******************************************************************************/
void flash7(uint8_t flashorder)
{
	if(++SpeedSum >= 5)																	//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		if(0 == NumCount%77)
		{
			clearAll();																	//清除所有缓存
			randomColour(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
		}
		print(NumCount,Dat_print+NumCount/77*8,Color_red,Color_green,Color_blue,1,0);	//打印图案
		if(++NumCount >= 1155)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}

/*******************************************************************************
 * @name     :void flash8(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :滚动字幕
*******************************************************************************/
void flash8(uint8_t flashorder)
{
	if(++SpeedSum >= 15)																//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		if(0 == NumCount)
		{
			clearAll();																	//清除所有缓存
			randomColour(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
		}
		scrollText(NumCount);
		//Mov_Show(NumCount,MathSum,Color_red,Color_green,Color_blue,1);					//滚动字幕
		if(++NumCount >= 152)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}

const uint8_t Circle[29]={
0,1,2,3,4,5,6,7,15,23,31,39,47,55,63,62,61,60,59,58,57,56,48,40,32,24,16,8,0
};
/*******************************************************************************
 * @name     :void flash9(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :滚动平面
*******************************************************************************/
void flash9(uint8_t flashorder)
{
	char i,j;
	if(++SpeedSum >= 15)																//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		if(0 == NumCount)
		{
			clearAll();																	//清除所有缓存
			randomColour(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
		}
		if(NumCount < 50)
		{
			switch(NumCount/29)
			{
				case 0:
					if(NumCount > 7)
					i = Circle[NumCount-8]%8;
					j = Circle[NumCount-8]/8;
					line(i,j,0,i,j,7,0,0,0);											//去掉之前的一束
				case 1:
					i = Circle[NumCount%29]%8;
					j = Circle[NumCount%29]/8;
					line(i,j,0,i,j,7,Color_red,Color_green,Color_blue);				//3维坐标中画线
				break;
			}
		}
		else if(NumCount < 56)
		{
			i = NumCount-49;
			line(1,0,i,6,0,i,0,0,0);												
			line(1,7,i,6,7,i,0,0,0);												
			line(0,1,i,0,6,i,0,0,0);												
			line(7,1,i,7,6,i,0,0,0);												
		}
		else if(NumCount < 62)
		{
			i = (NumCount-54)/2;
			Box(i,i,i,7-i,7-i,7-i,Color_red,Color_green,Color_blue,0,0);				//3维坐标中画箱子
		}
		else if(NumCount < 70)
		{
			i = (69-NumCount)/2;
			Box(i,i,i,7-i,7-i,7-i,0,0,0,0,0);											//3维坐标中画箱子
		}
			
		if(++NumCount >= 70)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}

/*******************************************************************************
 * @name     :void flash10(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :读取数组图片
*******************************************************************************/
void flash10(uint8_t flashorder)
{
	char i,j;
	int mm,kk;
	if(++SpeedSum >= 15)																//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		if(0 == NumCount%20)
			randomColour(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
			
		for(j = 0; j < 8; j++)
		{
			mm = 192*j;
			for(i = 0; i < 64; i++)
			{
				kk = 3*i;
		//		if(Shape[i+NumCount%154*64] & (0x80 >> j))
				{
					rgbled[setLED][rgb_order[kk+1]+mm] = Color_red; 			
					rgbled[setLED][rgb_order[kk+0]+mm] = Color_green;			
					rgbled[setLED][rgb_order[kk+2]+mm] = Color_blue;	
				}	
		//		else
				{
					rgbled[setLED][rgb_order[kk+0]+mm] = 0; 			
					rgbled[setLED][rgb_order[kk+1]+mm] = 0;			
					rgbled[setLED][rgb_order[kk+2]+mm] = 0;	
				}
			}				
		}		
		
		if(++NumCount >= 308)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}

/*******************************************************************************
 * @name     :void flash11(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :模拟波浪图案
*******************************************************************************/
void flash11(uint8_t flashorder)
{
	char i,j;
	int mm,kk;
	if(++SpeedSum >= 15)																//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		if(0 == NumCount%20)
			randomColour(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
			
		for(j = 0; j < 8; j++)
		{
			mm = 192*j;
			for(i = 0; i < 64; i++)
			{
				kk = 3*i;
	//			if(Waveled[i+NumCount%29*64] & (0x80 >> j))
				{
					rgbled[setLED][rgb_order[kk+1]+mm] = Color_red; 			
					rgbled[setLED][rgb_order[kk+0]+mm] = Color_green;			
					rgbled[setLED][rgb_order[kk+2]+mm] = Color_blue;	
				}	
	//			else
				{
					rgbled[setLED][rgb_order[kk+0]+mm] = 0; 			
					rgbled[setLED][rgb_order[kk+1]+mm] = 0;			
					rgbled[setLED][rgb_order[kk+2]+mm] = 0;	
				}
			}				
		}		
		
		if(++NumCount >= 116)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}

/*******************************************************************************
 * @name     :void flash12(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :读取海量数组
*******************************************************************************/
void flash12(uint8_t flashorder)
{
	char i,j;
	if(++SpeedSum >= 15)																//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
			
		for(j = 0; j < 8; j++)
		{
//			mm = 192*j;
	//		nn = 32*j;
			for(i = 0; i < 32; i++)
			{
		//		kk = 6*i;
	/*			rgbled[rgb_order[kk+0]+mm] =  Dmax[768*NumCount+i+nn] & 0x0f;			//(红色)取数据的低4位				
				rgbled[rgb_order[kk+3]+mm] = (Dmax[768*NumCount+i+nn] >> 4)& 0x0f;		//(红色)取数据的高4位				
				rgbled[rgb_order[kk+1]+mm] =  Dmax[768*NumCount+i+nn+256] & 0x0f;		//(绿色)取数据的低4位				
				rgbled[rgb_order[kk+4]+mm] = (Dmax[768*NumCount+i+nn+256] >> 4)& 0x0f;	//(绿色)取数据的高4位				
				rgbled[rgb_order[kk+2]+mm] =  Dmax[768*NumCount+i+nn+512] & 0x0f;		//(蓝色)取数据的低4位				
				rgbled[rgb_order[kk+5]+mm] = (Dmax[768*NumCount+i+nn+512] >> 4)& 0x0f;	//(蓝色)取数据的高4位				*/
			}				
		}					

		if(++NumCount >= 275)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}




/*******************************************************************************
 * @name     :void BOX_move(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :正方体的移动，变化
*******************************************************************************/
/*void BOX_move(uint8_t flashorder)
{
	static int8_t colorR1,colorR2,colorR3,colorR4,colorG1,colorG2,colorG3,colorG4,colorB1,colorB2,colorB3,colorB4;
	int i,j;
	if(++SpeedSum >= 30)																//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		
		if(0 == NumCount || 23 == NumCount || 63 == NumCount || 87 == NumCount)
		{
			randomColour(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
			if(0 == NumCount)
			{
				randomColour(&colorR1,&colorG1,&colorB1);								//取得随机颜色
				randomColour(&colorR2,&colorG2,&colorB2);								//取得随机颜色
				randomColour(&colorR3,&colorG3,&colorB3);								//取得随机颜色
				randomColour(&colorR4,&colorG4,&colorB4);								//取得随机颜色
			}
		}
			
		clearAll();																		//清除所有缓存
		if(NumCount < 23)
		{
			i = 12*NumCount;
			Box(BoxDat[i+0] & 0x0f,BoxDat[i+1] & 0x0f,BoxDat[i+2] & 0x0f,
				BoxDat[i+0] >> 4,BoxDat[i+1] >> 4,BoxDat[i+2] >> 4,colorR1,colorG1,colorB1,1,0);				//3维坐标中画箱子
			Box(BoxDat[i+3] & 0x0f,BoxDat[i+4] & 0x0f,BoxDat[i+5] & 0x0f,
				BoxDat[i+3] >> 4,BoxDat[i+4] >> 4,BoxDat[i+5] >> 4,colorR2,colorG2,colorB2,1,0);				//3维坐标中画箱子
			Box(BoxDat[i+6] & 0x0f,BoxDat[i+7] & 0x0f,BoxDat[i+8] & 0x0f,
				BoxDat[i+6] >> 4,BoxDat[i+7] >> 4,BoxDat[i+8] >> 4,colorR3,colorG3,colorB3,1,0);				//3维坐标中画箱子
			Box(BoxDat[i+9] & 0x0f,BoxDat[i+10] & 0x0f,BoxDat[i+11] & 0x0f,
				BoxDat[i+9] >> 4,BoxDat[i+10] >> 4,BoxDat[i+11] >> 4,colorR4,colorG4,colorB4,1,0);				//3维坐标中画箱子
		}
		else if(NumCount < 167)
		{
			if(NumCount < 95)
			{
				i = 207+3*NumCount;							//i = 12*23+3*(NumCount-23);
				j = (NumCount-23)/8;
			}
			else if(NumCount < 167)
			{
				i = 3*NumCount-9;							//i = 12*23+3*(NumCount-95);
				j = (NumCount-95)/8;
			}
			switch(j)
			{
				case 2:
				case 5:
				case 8:
					set(BoxDat[i+0],BoxDat[i+1],BoxDat[i+2],Color_red,Color_green,Color_blue);						//点的选择与颜色设置
				break;
				default:
					if(NumCount < 95)
						Box(BoxDat[i+0] & 0x0f,BoxDat[i+1] & 0x0f,BoxDat[i+2] & 0x0f,
							BoxDat[i+0] >> 4,BoxDat[i+1] >> 4,BoxDat[i+2] >> 4,Color_red,Color_green,Color_blue,1,0);		//3维坐标中画箱子
					else	
						Box(BoxDat[i+0] & 0x0f,BoxDat[i+1] & 0x0f,BoxDat[i+2] & 0x0f,
								BoxDat[i+0] >> 4,BoxDat[i+1] >> 4,BoxDat[i+2] >> 4,Color_red,Color_green,Color_blue,0,0);	//3维坐标中画箱子
				break;
			}
		}
		
		if(++NumCount >= 167)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}
*/

void Line_Cut(uint8_t mode,uint8_t size,int8_t red,int8_t green,int8_t blue)
{
	size %= 3;
	line(2-size,3-size,mode,2-size,4+size,mode,red,green,blue);
	line(3-size,2-size,mode,4+size,2-size,mode,red,green,blue);
	line(3-size,5+size,mode,4+size,5+size,mode,red,green,blue);
	line(5+size,3-size,mode,5+size,4+size,mode,red,green,blue);
}

void Line_Cut1(uint8_t mode,uint8_t size,int8_t red,int8_t green,int8_t blue)
{
	size %= 3;
	//控制左右
//	Line(mode,0,size,mode,3,size,red,green,blue,1);
//	Line(mode,2-size,4,mode,2-size,7,red,green,blue,1);
//	Line(mode,4,7-size,mode,7,7-size,red,green,blue,1);
//	Line(mode,5+size,0,mode,5+size,3,red,green,blue,1);
	//控制前后
	line(0,mode,size,3,mode,size,red,green,blue);
	line(2-size,mode,4,2-size,mode,7,red,green,blue);
	line(4,mode,7-size,7,mode,7-size,red,green,blue);
	line(5+size,mode,0,5+size,mode,3,red,green,blue);
}

/*******************************************************************************
 * @name     :void Line_AddCut(uint8_t flashorder)
 * @param    :flashorder→选择下一次的显示动画
 * @author   :图腾实验室→图腾
 * @details  :线条的增加减少
*******************************************************************************/
void Line_AddCut(uint8_t flashorder)
{
	char i,j;
	int Number;
	if(++SpeedSum >= 8)																	//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
		
		if(0 == NumCount || 264 == NumCount)
		{
			clearAll();																	//清除所有缓存
			randomColour(&Color_red,&Color_green,&Color_blue);							//取得随机颜色
			Color_red++;																//确保每种颜色都有
			if(Color_red > 15)
				Color_red = 15;
			Color_green++;
			if(Color_green > 15)
				Color_green = 15;
			Color_blue++;
			if(Color_blue > 15)
				Color_blue = 15;
		}
		
		if((NumCount >= 0 && NumCount < 192) || (NumCount >= 264 && NumCount < 456))
		{
			i = NumCount%8;
			j = NumCount/8;
			if(NumCount < 192)
				Number = NumCount/64;
			else
				Number = (NumCount-72)/64;
//				Number = (NumCount-264)/64+3;
			//增加
			switch(Number)
			{
				case 0:
					line(0,i,j,7,i,j,Color_red,0,0);									//3维坐标中画线,增加红色
				break;
				case 1:
					line(0,7-i,15-j,7,7-i,15-j,Color_red,Color_green,0);				//3维坐标中画线,增加绿色
				break;
				case 2:
					line(0,i,j-16,7,i,j-16,Color_red,Color_green,Color_blue);			//3维坐标中画线,增加蓝色
				break;
				
				case 3:
					line(i,0,j-33,i,7,j-33,0,0,Color_blue);							//3维坐标中画线,增加蓝色
				break;
				case 4:
					line(48-j,0,7-i,48-j,7,7-i,Color_red,0,Color_blue);				//3维坐标中画线,增加红色
				break;
				case 5:
					line(j-49,0,i,j-49,7,i,Color_red,Color_green,Color_blue);			//3维坐标中画线,增加绿色
				break;
			}
		}
		else if((NumCount >= 192 && NumCount < 264) || (NumCount >= 456 && NumCount < 528))
		{
			if(NumCount < 264)
			{
				j = 2-NumCount%3;
				i = NumCount/3;
			}
			else
			{
				j = NumCount/8;
				i = NumCount%8;
			}
			//减少
			switch(NumCount/24)
			{
				case 8:
					Line_Cut(i-64,j,0,Color_green,Color_blue);							//去掉红色
				break;
				case 9:
					Line_Cut(79-i,j,0,Color_green,0);									//去掉蓝色
				break;
				case 10:
					Line_Cut(i-80,j,0,0,0);												//去掉绿色
				break;
				
				case 19:
					Line_Cut1(i,49-j,Color_red,0,Color_blue);							//去掉绿色
				break;
				case 20:
					Line_Cut1(7-i,52-j,0,0,Color_blue);									//去掉红色
				break;
				case 21:
					Line_Cut1(i,55-j,0,0,0);											//去掉蓝色
				break;
			}
		}
		
		if(++NumCount >= 528)															//动画的次数
		{
			NumCount = 0;
			pictrue_order = flashorder;													//跳到下一个动画
		}
	}
}

/*******************************************************************************
 * @name     :void Cartoon(void)
 * @author   :图腾实验室→图腾
 * @details  :动画显示
*******************************************************************************/
void Cartoon(void)
{
	switch(pictrue_order)
	{
		case 0:
			flash7(1);																	//打印图案
		break;
		case 1:
			flash9(2);																	//滚动平面
		break;
		case 2:
			flash9(3);
			//BOX_move(3);																//正方体的移动，变化
		break;
		case 3:
			flash0(4);																	//漏斗的形状
		break;
		case 4:
			flash2(5);																	//像翻书一样的效果
		break;
		case 5:
			flash4(6);																	//4个正方体旋转效果
		break;
		case 6:
			flash3(7);																	//垂直xy面的拉动效果
		break;
		case 7:
			flash5(8);																	//DNA旋转效果
		break;
		case 8:
			flash6(9);																	//波浪的变化效果
		break;
		case 9:
			flash11(10);																//模拟波浪图案
		break;
		case 10:
			Line_AddCut(11);															//线条的增加减少
		break;
		case 11:
			flash8(12);																	//滚动字幕
		break;
		case 12:
			flash12(13);																//读取海量数组
		break;
		case 13:
			flash10(1);																	//读取数组显示图片
		break;
	}
//			flash1(0);																	//由线慢慢变化
}

/*******************************************************************************
 * @name     :void ReadW25Q64(void)
 * @author   :图腾实验室→图腾
 * @details  :读取内存颗粒的数据
*******************************************************************************/
void ReadW25Q64(void)
{
	if(++SpeedSum >= 10)																//速度控制
	{
		SpeedSum = 0;																	//速度控制变量清0
//		SPI_Flash_Read(Read_Buf,4096*NowSection+768*W25QxxAddress+3,768);				//读取flash，一次性都读完数据，不用每次都发地址，提高效率
//		AxesConvert();																	//将数据转换到坐标上面
//		W25QxxAddress++;
//		if(W25QxxAddress >= W25QxxFrame)												//判断一个扇区需要显示的帧数
//		{
//			W25QxxAddress = 0;															//当前的扇区的地址清0	
//			NowSection++;																//当前的扇区增加	
//			
//			SPI_Flash_Read(W25QxxTempAA,4096*NowSection,3);   							//读取flash
//			W25QxxFrame = W25QxxTempAA[2];												//保存每个扇区需要显示的帧数
//			//W25QxxSection = W25QxxTempAA[0]+(W25QxxTempAA[1] << 8);					//保存需要读取的扇区个数
//			
//			if(NowSection >= W25QxxSection)												//判断扇区是否是需要显示的最大值
//			{
//				NowSection = 0;
//				SPI_Flash_Read(W25QxxTempAA,0,3);   									//读取flash
//				W25QxxFrame = W25QxxTempAA[2];											//保存每个扇区需要显示的帧数
//				W25QxxSection = W25QxxTempAA[0]+(W25QxxTempAA[1] << 8);					//保存需要读取的扇区个数
//			}
//		}	
	}			
}

/*******************************************************************************
 * @name     :void Snake_scrolling(void)
 * @author   :图腾实验室→图腾
 * @details  :蛇显示、移动
*******************************************************************************/
void Snake_scrolling(void)																
{
	if(++SpeedSum >= 40)																//控制移动的速度
	{
		SpeedSum = 0;																	//速度控制变量清0
		Snake_Show(200,10,0,0,200,0);														//贪吃蛇的显示函数
		Snake_Move();																	//贪吃蛇的蛇身移动
		if(1 == Collide())																//判断贪吃蛇是否有碰撞
		{
			Snake_Start();																//蛇身初始化
			Snake_Above();																//给食物并且判断食物是否在蛇身上面
		}
		Snake_Feed();																	//判断是否吃食物，吃就长度加1，否则不加，并且判断是否达到最大长度
	}
}














