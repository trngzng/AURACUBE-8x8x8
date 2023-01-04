#include "calculate.h"

/*******************************************************************************
 * @name     :uint8_t Word_Swap(uint8_t temp)
 * @param    :temp →需要转换的字节
 * @return   :高低位转换后的字节
 * @author   :图腾实验室→图腾
*******************************************************************************/
uint8_t Word_Swap(uint8_t temp)
{
	temp = (temp << 4) | (temp >> 4);
	temp = ((temp << 2) & 0xCC) | ((temp >> 2) & 0x33);
	temp = ((temp << 1) & 0xAA) | ((temp >> 1) & 0x55);
	return temp;
}

/*******************************************************************************
 * @name     :short Sqrt(unsigned long M)
 * @param    :M→被开方数
 * @return   :开平方根之后的数
 * @author   :图腾实验室→图腾
*******************************************************************************/
//short Sqrt(unsigned long M)   
//{
//    unsigned int N,i;
//    unsigned long tmp,ttp; 
//    if(M == 0)             
//        return 0;
//    N = 0;
//    tmp = (M >> 30);        
//    M <<= 2;
//    if(tmp > 1)            
//    {
//        N++;               
//        tmp -= N;
//    }
//    for(i = 15; i; i--)   
//    {
//        N <<= 1;           
//        tmp <<= 2;
//        tmp += (M >> 30);  
//        ttp = N;
//        ttp = (ttp << 1)+1;
//        M <<= 2;
//        if(tmp >= ttp)    
//        {
//            tmp -= ttp;
//            N++;
//        }       
//    }
//    return N;
//}

/*******************************************************************************
 * @name     :void Trans(void)
 * @author   :图腾实验室→图腾
 * @details  :整体数据向右移动一位
*******************************************************************************/
void Trans(void)
{
	char x, y, z;
	int16_t i = 0, j = 0;
	for (z = 0; z < 8; z++)
	{
		for (y = 0; y < 8; y++)
		{
			for (x = 6; x; x--)
			{
				i = x * 3 + (7 - y) * 24;														//计算当前的点在这层的位置
				j = 192 * z;																	//计算当前的点在第几层
				rgbled[setLED][rgb_order[i + 1] + j] = rgbled[1][rgb_order[i - 3 + 1] + j];		//将前面的数据复制到后面		
				rgbled[setLED][rgb_order[i + 0] + j] = rgbled[1][rgb_order[i - 3 + 0] + j];		//将前面的数据复制到后面
				rgbled[setLED][rgb_order[i + 2] + j] = rgbled[1][rgb_order[i - 3 + 2] + j];		//将前面的数据复制到后面
			}
		}
	}
	for (z = 0; z < 8; z++)
	{
		for (y = 0; y < 8; y++)
		{
			i = (7 - y) * 24;																	//计算当前的点在这层的位置
			j = 192 * z;																		//计算当前的点在第几层
			rgbled[setLED][rgb_order[i + 0] + j] = 0;											//将数据清0		
			rgbled[setLED][rgb_order[i + 1] + j] = 0;											//将数据清0	
			rgbled[setLED][rgb_order[i + 2] + j] = 0;											//将数据清0	
		}
	}
}

/*******************************************************************************
 * @name     :int8_t abss(int8_t dat)
 * @param    :dat→需要转换的数据
 * @author   :图腾实验室→图腾
 * @details  :四舍五入，返回十位的数值
*******************************************************************************/
int8_t abss(int8_t dat)
{
	int8_t tpdat = 0;
	tpdat = dat / 10;
	dat = dat - tpdat * 10;
	if (dat >= 5)
		tpdat++;
	return tpdat;
}

/*******************************************************************************
 * @name     :int8_t abs_bj(int8_t dat)
 * @param    :dat→需要转换的数据
 * @author   :图腾实验室→图腾
 * @details  :取数据的绝对值
*******************************************************************************/
int8_t abs_bj(int8_t dat)
{
	if (dat <= 0)
		dat = -dat;
	else
		dat = dat;
	return dat;
}

/*******************************************************************************
 * @name     :void Max(int8_t *a,int8_t *b)
 * @param    :*a→需要转换的数据
 * @param    :*b→需要转换的数据
 * @author   :图腾实验室→图腾
 * @details  :比较函数，大的数值置前，指针函数，直接对原数值操作
*******************************************************************************/
void Max(int8_t *a, int8_t *b)
{
	if ((*a) > (*b))
	{
		*a = *a ^ *b;
		*b = *b ^ *a;
		*a = *a ^ *b;
		//*a = *a + *b - (*b = *a);
	}
}

/*******************************************************************************
 * @name     :int8_t maxt(int8_t datA,int8_t datB,int8_t datC)
 * @param    :datA→需要比较的数据
 * @param    :datB→需要比较的数据
 * @param    :datC→需要比较的数据
 * @author   :图腾实验室→图腾
 * @details  :3个数据比较，返回最大值
*******************************************************************************/
int8_t maxt(int8_t datA, int8_t datB, int8_t datC)
{
	if (datA <= datB)
		datA = datB;
	if (datA <= datC)
		datA = datC;
	return datA;
}


/*void ColorPoint(int8_t x,int8_t y,int8_t z,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut)
{
	if(Add_Cut)												//???????????
	{
		  set(x,y,z,red,green,blue);
	}
	else													//???????????
	{
		  clear(x,y,z);
	}
}
*/

const int Funnel_dat[128] =
{
0,1,2,3,4,5,6,7,15,23,31,39,47,55,63,62,61,60,59,58,57,56,48,40,32,24,16,8,
73,74,75,76,77,78,86,94,102,110,118,117,116,115,114,113,105,97,89,81,
146,147,148,149,157,165,173,172,171,170,162,154,
219,220,228,227,
283,284,292,291,
338,339,340,341,349,357,365,364,363,362,354,346,
393,394,395,396,397,398,406,414,422,430,438,437,436,435,434,433,425,417,409,401,
448,449,450,451,452,453,454,455,463,471,479,487,495,503,511,510,509,508,507,506,505,504,496,488,480,472,464,456
};

/*******************************************************************************
 * @name     :void Funnel_Shape(int8_t number,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut)
 * @param    :number→需要点亮的点
 * @param    :red→红色的大小(范围0--255)
 * @param    :green→绿色的大小(范围0--255)
 * @param    :blue→蓝色的大小(范围0--255)
 * @param    :Add_Cut→增加还是减少，0为减少，其他为增加
 * @author   :图腾实验室→图腾
 * @details  :一点点的形成漏斗的形状函数
*******************************************************************************/

void Funnel_Shape(int8_t number, uint8_t red, uint8_t green, uint8_t blue)
{
	int8_t x = 0, y = 0, z = 0;
	number %= 128;
	x = Funnel_dat[number] % 8;
	y = Funnel_dat[number] % 64 / 8;
	z = Funnel_dat[number] / 64;
	set(x, y, z, red, green, blue);
}

/*******************************************************************************
 * @name     :void Line(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut)
 * @param    :red→红色的大小(范围0--255)
 * @param    :green→绿色的大小(范围0--255)
 * @param    :blue→蓝色的大小(范围0--255)
 * @param    :Add_Cut→增加还是减少，0为减少，其他为增加
 * @author   :图腾实验室→图腾
 * @details  :3维坐标中画线
*******************************************************************************/
void line(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2, uint8_t red, uint8_t green, uint8_t blue)
{
	int8_t mDat = 0, SumX = 0, SumY = 0, SumZ = 0, poorX = 0, poorY = 0, poorZ = 0;
	int8_t i = 0;
	poorX = x2 - x1;
	poorY = y2 - y1;
	poorZ = z2 - z1;
	mDat = maxt(abs(poorX), abs(poorY), abs(poorZ));
	SumX = x1 * 10;
	SumY = y1 * 10;
	SumZ = z1 * 10;
	poorX = poorX * 10 / mDat;
	poorY = poorY * 10 / mDat;
	poorZ = poorZ * 10 / mDat;
	for (i = 0; i < mDat; i++)
	{
		set(abss(SumX), abss(SumY), abss(SumZ), red, green, blue);
		SumX = SumX + poorX;
		SumY = SumY + poorY;
		SumZ = SumZ + poorZ;
	}
	set(x2, y2, z2, red, green, blue);
}

const uint8_t roll[28] =
{
0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x71,0x72,0x73,0x74,0x75,0x76,
0x77,0x67,0x57,0x47,0x37,0x27,0x17,0x07,0x06,0x05,0x04,0x03,0x02,0x01
};

void Rotat(int16_t number, uint8_t red, uint8_t green, uint8_t blue)
{
	char x1, y1, x2, y2, j, i;
	number %= 72;
	if (number < 36)
	{
		clearAll();																		//清除所有缓存
		i = number;
		for (j = 0; j < 8; j++)
		{
			x1 = roll[(i + j) % 28] & 0x0f;
			y1 = roll[(i + j) % 28] & 0xf0;
			y1 = y1 >> 4;
			x2 = roll[(i + j + 14) % 28] & 0x0f;
			y2 = roll[(i + j + 14) % 28] & 0xf0;
			y2 = y2 >> 4;
			line(x1, y1, j, x2, y2, j, red, green, blue);
		}
	}
	else if (number < 72)
	{
		clearAll();																		//清除所有缓存
		i = number - 36;
		for (j = 0; j < 8; j++)
		{
			x1 = roll[27 - (i + j) % 28] & 0x0f;
			y1 = roll[27 - (i + j) % 28] & 0xf0;
			y1 = y1 >> 4;
			x2 = roll[27 - (i + j + 14) % 28] & 0x0f;
			y2 = roll[27 - (i + j + 14) % 28] & 0xf0;
			y2 = y2 >> 4;
			line(x1, y1, j, x2, y2, j, red, green, blue);
		}
	}
}

/*******************************************************************************
 * @name     :void Line_Change(int8_t number,int8_t red,int8_t green,int8_t blue)
 * @param    :number→(范围0--31)
 * @param    :red→红色的大小(范围0--255)
 * @param    :green→绿色的大小(范围0--255)
 * @param    :blue→蓝色的大小(范围0--255)
 * @author   :图腾实验室→图腾
 * @details  :由线慢慢变化
*******************************************************************************/
void Line_Change(int8_t number, uint8_t red, uint8_t green, uint8_t blue)
{
	int8_t j = 0;
	static int8_t datB[8];
	number %= 32;
	if (0 == number)
		for (j = 7; j < 15; j++)
			datB[j - 7] = j;
	if (number < 16)
	{
		for (j = 0; j < 8; j++)
			if ((datB[j] < 8) & (datB[j] >= 0))
				line(0, datB[j], j, 7, datB[j], j, red, green, blue);
		for (j = 0; j < 8; j++)
			if (((datB[j] + 1) < 8) & (datB[j] >= 0))
				line(0, datB[j] + 1, j, 7, datB[j] + 1, j, BLACK);
		for (j = 0; j < 8; j++)
			if (datB[j] > 0)
				datB[j]--;
	}
	else if (number < 32)
	{
		if (16 == number)
			for (j = 0; j < 8; j++)
				datB[j] = 1 - j;

		for (j = 0; j < 8; j++)
			if ((datB[j] < 8) & (datB[j] >= 0))
				line(0, datB[j], j, 7, datB[j], j, red, green, blue);

		for (j = 0; j < 8; j++)
			if (((datB[j] - 1) < 7) & (datB[j] > 0))
				line(0, datB[j] - 1, j, 7, datB[j] - 1, j, red, green, blue);
		for (j = 0; j < 8; j++)
			if (datB[j] < 7)
				datB[j]++;
	}
}

/*******************************************************************************
 * @name     :void Page(int8_t number,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut)
 * @param    :number	→需要点亮第几个面
 * @param    :red		→红色的大小(范围0--255)
 * @param    :green		→绿色的大小(范围0--255)
 * @param    :blue		→蓝色的大小(范围0--255)
 * @param    :Add_Cut	→增加还是减少，0为减少，其他为增加
 * @param    :way		→显示的方向
 * @author   :图腾实验室→图腾
 * @details  :像翻书一样的效果，一面一面的显示
*******************************************************************************/
void Page(int8_t number, uint8_t red, uint8_t green, uint8_t blue, int8_t way)
{
	int8_t i = 0;
	number %= 15;
	way %= 8;
	if (number < 8)
	{
		for (i = 0; i < 8; i++)
		{
			switch (way)
			{
				case 0:														//左边向上面
					line(0, i, 0, 0, i, 7 - number, red, green, blue);
					line(0, i, 7 - number, number, i, 7, red, green, blue);
					break;
				case 1:														//左边向下面
					line(0, i, 7, 0, i, number, red, green, blue);
					line(0, i, number, number, i, 0, red, green, blue);
					break;
				case 2:														//右边向上面
					line(7, i, 0, 7, i, 7 - number, red, green, blue);
					line(7, i, 7 - number, 7 - number, i, 7, red, green, blue);
					break;
				case 3:														//右边向下面
					line(7, i, 7, 7, i, number, red, green, blue);
					line(7, i, number, 7 - number, i, 0, red, green, blue);
					break;
				case 4:														//前边向上面
					line(i, 0, 0, i, 0, 7 - number, red, green, blue);
					line(i, 0, 7 - number, i, number, 7, red, green, blue);
					break;
				case 5:														//前边向下面
					line(i, 0, 7, i, 0, number, red, green, blue);
					line(i, 0, number, i, number, 0, red, green, blue);
					break;
				case 6:														//后边向上面
					line(i, 7, 0, i, 7, 7 - number, red, green, blue);
					line(i, 7, 7 - number, i, 7 - number, 7, red, green, blue);
					break;
				case 7:														//后边向下面
					line(i, 7, 7, i, 7, number, red, green, blue);
					line(i, 7, number, i, 7 - number, 0, red, green, blue);
					break;
			}
		}
	}
	else if (number < 15)
	{
		for (i = 0; i < 8; i++)
		{
			switch (way)
			{
				case 0:														//左边向上面
					line(0, i, 0, number - 7, i, 0, red, green, blue);
					line(number - 7, i, 0, 7, i, 14 - number, red, green, blue);
					break;
				case 1:														//左边向下面
					line(0, i, 7, number - 7, i, 7, red, green, blue);
					line(number - 7, i, 7, 7, i, number - 7, red, green, blue);
					break;
				case 2:														//右边向上面
					line(7, i, 0, 14 - number, i, 0, red, green, blue);
					line(14 - number, i, 0, 0, i, 14 - number, red, green, blue);
					break;
				case 3:														//右边向下面
					line(7, i, 7, 14 - number, i, 7, red, green, blue);
					line(14 - number, i, 7, 0, i, number - 7, red, green, blue);
					break;
				case 4:														//前边向上面
					line(i, 0, 0, i, number - 7, 0, red, green, blue);
					line(i, number - 7, 0, i, 7, 14 - number, red, green, blue);
					break;
				case 5:														//前边向下面
					line(i, 0, 7, i, number - 7, 7, red, green, blue);
					line(i, number - 7, 7, i, 7, number - 7, red, green, blue);
					break;
				case 6:														//后边向上面
					line(i, 7, 0, i, 14 - number, 0, red, green, blue);
					line(i, 14 - number, 0, i, 0, 14 - number, red, green, blue);
					break;
				case 7:														//后边向下面
					line(i, 7, 7, i, 14 - number, 7, red, green, blue);
					line(i, 14 - number, 7, i, 0, number - 7, red, green, blue);
					break;
			}
		}
	}
}

int8_t Get_Point[3];

/*******************************************************************************
 * @name     :void GetPoint(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,int8_t Number)
 * @author   :图腾实验室→图腾
 * @details  :获取两点形成的线中的某个点的坐标，数组Get_Point[3]接收
*******************************************************************************/
void GetPoint(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2, int8_t Number)
{
	int8_t mDat = 0, SumX = 0, SumY = 0, SumZ = 0, poorX = 0, poorY = 0, poorZ = 0;
	poorX = x2 - x1;
	poorY = y2 - y1;
	poorZ = z2 - z1;
	mDat = maxt(abs(poorX), abs(poorY), abs(poorZ));
	SumX = x1 * 10;
	SumY = y1 * 10;
	SumZ = z1 * 10;
	poorX = poorX * 10 / mDat;
	poorY = poorY * 10 / mDat;
	poorZ = poorZ * 10 / mDat;
	Get_Point[0] = SumX + poorX*Number;
	Get_Point[1] = SumY + poorY*Number;
	Get_Point[2] = SumZ + poorZ*Number;
}

/*******************************************************************************
 * @name     :void PlaneXY(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
						   int8_t red,int8_t green,int8_t blue,int8_t Add_Cut,int8_t fill)
 * @param    :red→红色的大小(范围0--255)
 * @param    :green→绿色的大小(范围0--255)
 * @param    :blue→蓝色的大小(范围0--255)
 * @param    :Add_Cut→增加还是减少，0为减少，其他为增加
 * @param    :fill→空心还是实心，0为空心，其他为实心
 * @author   :图腾实验室→图腾
 * @details  :3维坐标中画方框,垂直于xy的平面
*******************************************************************************/
void PlaneXY(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue, int8_t fill)
{
	int8_t i = 0;
	Max(&z1, &z2);
	if (fill)
	{
		for (i = z1; i <= z2; i++)
			line(x1, y1, i, x2, y2, i, red, green, blue);
	}
	else
	{
		line(x1, y1, z1, x2, y2, z1, red, green, blue);
		line(x1, y1, z2, x2, y2, z2, red, green, blue);
		line(x2, y2, z1, x2, y2, z2, red, green, blue);
		line(x1, y1, z1, x1, y1, z2, red, green, blue);
	}
}

/*******************************************************************************
 * @name     :void Change_PlaneXY(int8_t number,int8_t red,int8_t green,int8_t blue)
 * @param    :number→拉动效果的顺序(范围0--35)
 * @param    :red→红色的大小(范围0--255)
 * @param    :green→绿色的大小(范围0--255)
 * @param    :blue→蓝色的大小(范围0--255)
 * @author   :图腾实验室→图腾
 * @details  :垂直xy面的拉动效果
*******************************************************************************/
void Change_PlaneXY(int8_t number, uint8_t red, uint8_t green, uint8_t blue)
{
	int8_t j = 0;
	static int8_t datC[4];
	number %= 36;

	if (number < 8)
	{
		if (0 == number)
			for (j = 7; j < 11; j++)
				datC[j - 7] = j;
		for (j = 0; j < 4; j++)
		{
			if (datC[j] < 8)
				PlaneXY(j, datC[j], j, 7 - j, datC[j], 7 - j, red, green, blue, 0);
			if (datC[j] < 7)
				PlaneXY(j, datC[j] + 1, j, 7 - j, datC[j] + 1, 7 - j, BLACK, 0);
		}
		for (j = 0; j < 4; j++)
			if (datC[j] > 3)
				datC[j]--;
	}
	else if (number < 11)
	{
		if (8 == number)
			for (j = 0; j < 4; j++)
				datC[j] = 5 - j;

		for (j = 1; j < 4; j++)
		{
			if (datC[j] < 4)
				PlaneXY(j, datC[j], j, 7 - j, datC[j], 7 - j, red, green, blue, 0);
			if (datC[j] < 3)
				PlaneXY(j, datC[j] + 1, j, 7 - j, datC[j] + 1, 7 - j, BLACK, 0);
		}
		for (j = 0; j < 4; j++)
			if (datC[j] > 0)
				datC[j]--;
	}
	else if (number < 14)
	{
		if (11 == number)
			for (j = 1; j < 4; j++)
				datC[j] = 4 - j;

		for (j = 1; j < 4; j++)
		{
			if (datC[j] >= 0)
				PlaneXY(j, datC[j], j, 7 - j, datC[j], 7 - j, red, green, blue, 0);
			if (datC[j] > 0)
				PlaneXY(j, datC[j] - 1, j, 7 - j, datC[j] - 1, 7 - j, BLACK, 0);
		}
		for (j = 1; j < 4; j++)
			if (datC[j] < 3)
				datC[j]++;
	}
	else if (number < 17)
	{
		if (14 == number)
			for (j = 0; j < 4; j++)
				datC[j] = j + 1;

		for (j = 1; j < 4; j++)
		{
			if (datC[j] > 3)
				PlaneXY(j, datC[j], j, 7 - j, datC[j], 7 - j, red, green, blue, 0);
			if (datC[j] > 3)
				PlaneXY(j, datC[j] - 1, j, 7 - j, datC[j] - 1, 7 - j, BLACK, 0);
		}
		for (j = 0; j < 4; j++)
			datC[j]++;
	}
	else if (number < 20)
	{
		if (17 == number)
			for (j = 3; j < 6; j++)
				datC[j - 2] = j;

		for (j = 1; j < 4; j++)
		{
			PlaneXY(j, datC[j], j, 7 - j, datC[j], 7 - j, red, green, blue, 0);
			PlaneXY(j, datC[j] + 1, j, 7 - j, datC[j] + 1, 7 - j, BLACK, 0);
		}
		for (j = 0; j < 4; j++)
			if (datC[j] > 3)
				datC[j]--;
	}
	else if (number < 23)
	{
		if (20 == number)
			for (j = 0; j < 4; j++)
				datC[j] = 5 - j;

		for (j = 1; j < 4; j++)
		{
			if (datC[j] < 4)
				PlaneXY(j, datC[j], j, 7 - j, datC[j], 7 - j, red, green, blue, 0);
			if (datC[j] < 3)
				PlaneXY(j, datC[j] + 1, j, 7 - j, datC[j] + 1, 7 - j, BLACK, 0);
		}
		for (j = 0; j < 4; j++)
			if (datC[j] > 0)
				datC[j]--;
	}
	else if (number < 26)
	{
		if (23 == number)
		{
			for (j = 0; j < 4; j++)
				datC[j] = 3 - j;
			datC[0] = 2;
		}
		for (j = 0; j < 3; j++)
		{
			if (datC[j] >= 0)
				PlaneXY(j, datC[j], j, 7 - j, datC[j], 7 - j, red, green, blue, 0);
			if (datC[j] >= 0)
				PlaneXY(j, datC[j] + 1, j, 7 - j, datC[j] + 1, 7 - j, BLACK, 0);
		}
		for (j = 0; j < 4; j++)
			if (j < 5 - (25 - number))
				datC[j]--;
	}
	else if (number < 36)
	{
		if (26 == number)
			for (j = 0; j < 4; j++)
				datC[j] = j - 2;

		for (j = 0; j < 4; j++)
		{
			if (datC[j] >= 0)
				PlaneXY(j, datC[j], j, 7 - j, datC[j], 7 - j, red, green, blue, 0);
			if (datC[j] >= 0)
				PlaneXY(j, datC[j] - 1, j, 7 - j, datC[j] - 1, 7 - j, BLACK, 0);
		}
		for (j = 0; j < 4; j++)
			if (datC[j] < 7)
				datC[j]++;
	}
}

/*******************************************************************************
 * @name     :void PlaneYZ(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
						   int8_t red,int8_t green,int8_t blue,int8_t Add_Cut,int8_t fill)
 * @param    :red→红色的大小(范围0--255)
 * @param    :green→绿色的大小(范围0--255)
 * @param    :blue→蓝色的大小(范围0--255)
 * @param    :Add_Cut→增加还是减少，0为减少，其他为增加
 * @param    :fill→空心还是实心，0为空心，其他为实心
 * @author   :图腾实验室→图腾
 * @details  :3维坐标中画方框,垂直于yz的平面
*******************************************************************************/
void PlaneYZ(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue, int8_t fill)
{
	int8_t i = 0;
	Max(&x1, &x2);
	if (fill)
	{
		for (i = x1; i <= x2; i++)
			line(i, y1, z1, i, y2, z2, red, green, blue);
	}
	else
	{
		line(x1, y1, z1, x1, y2, z2, red, green, blue);
		line(x2, y1, z1, x2, y2, z2, red, green, blue);
		line(x1, y2, z2, x2, y2, z2, red, green, blue);
		line(x1, y1, z1, x2, y1, z1, red, green, blue);
	}
}

/*******************************************************************************
 * @name     :void PlaneZX(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
						   int8_t red,int8_t green,int8_t blue,int8_t Add_Cut,int8_t fill)
 * @param    :red→红色的大小(范围0--255)
 * @param    :green→绿色的大小(范围0--255)
 * @param    :blue→蓝色的大小(范围0--255)
 * @param    :Add_Cut→增加还是减少，0为减少，其他为增加
 * @param    :fill→空心还是实心，0为空心，其他为实心
 * @author   :图腾实验室→图腾
 * @details  :3维坐标中画方框,垂直于zx的平面
*******************************************************************************/
void PlaneZX(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue, int8_t fill)
{
	int8_t i = 0;
	Max(&y1, &y2);

	if (fill)
	{
		for (i = y1; i <= y2; i++)
			line(x1, i, z1, x2, i, z2, red, green, blue);
	}
	else
	{
		line(x1, y1, z1, x2, y1, z2, red, green, blue);
		line(x1, y2, z1, x2, y2, z2, red, green, blue);
		line(x2, y1, z2, x2, y2, z2, red, green, blue);
		line(x1, y1, z1, x1, y2, z1, red, green, blue);
	}
}

/*******************************************************************************
 * @name     :void Box(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
					   int8_t red,int8_t green,int8_t blue,int8_t fill)
 * @brief    :red→红色的大小(范围0--255)
 * @param    :green→绿色的大小(范围0--255)
 * @param    :blue→蓝色的大小(范围0--255)
 * @param    :fill→空心还是实心，0为空心，其他为实心
 * @param    :Up_Down→上下是否颠倒，0为原来的，其他为上下颠倒的
 * @author   :图腾实验室→图腾
 * @details  :画箱子
*******************************************************************************/
void Box(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue, int8_t fill, int8_t Up_Down)
{
	int8_t i = 0;
	int8_t number = abs(z2 - z1);
	if (fill)
	{
		for (i = 0; i <= number; i++)
		{
			if (Up_Down)
				PlaneXY(x1 + i, y1, 7 - z1, x1 + i, y2, 7 - z2, red, green, blue, 1);
			else
				PlaneXY(x1 + i, y1, z1, x1 + i, y2, z2, red, green, blue, 1);
		}
	}
	else
	{
		if (Up_Down)
		{
			PlaneXY(x1, y1, 7 - z1, x1, y2, 7 - z2, red, green, blue, 0);
			PlaneXY(x2, y1, 7 - z1, x2, y2, 7 - z2, red, green, blue, 0);
			line(x1, y1, 7 - z1, x2, y1, 7 - z1, red, green, blue);
			line(x1, y2, 7 - z1, x2, y2, 7 - z1, red, green, blue);
			line(x1, y1, 7 - z2, x2, y1, 7 - z2, red, green, blue);
			line(x1, y2, 7 - z2, x2, y2, 7 - z2, red, green, blue);
		}
		else
		{
			PlaneXY(x1, y1, z1, x1, y2, z2, red, green, blue, 0);
			PlaneXY(x2, y1, z1, x2, y2, z2, red, green, blue, 0);
			line(x1, y1, z1, x2, y1, z1, red, green, blue);
			line(x1, y2, z1, x2, y2, z1, red, green, blue);
			line(x1, y1, z2, x2, y1, z2, red, green, blue);
			line(x1, y2, z2, x2, y2, z2, red, green, blue);
		}
	}
}

const uint8_t box1[24] =
{ 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x16,0x26,0x36,0x46,0x56,0x66,0x65,0x64,0x63,0x62,0x61,0x60,0x50,0x40,0x30,0x20,0x10 };

/*******************************************************************************
 * @name     :void Box_Change(int8_t number,int8_t red,int8_t green,int8_t blue,int8_t Up_Down)
 * @param    :number→显示的效果顺序
 * @param    :red→红色的大小(范围0--255)
 * @param    :green→绿色的大小(范围0--255)
 * @param    :blue→蓝色的大小(范围0--255)
 * @author   :图腾实验室→图腾
 * @details  :4个正方体旋转效果
*******************************************************************************/
void Box_Change(int8_t number, uint8_t red, uint8_t green, uint8_t blue, int8_t Up_Down)
{
	int8_t i = 0, x = 0, y = 0, t = 0;
	static int8_t datA[4];
	number %= 108;
	clearAll();																			//清除所有缓存
	if (number < 6)
	{
		Box(0, 6, 6, 1, 7, 7, red, green, blue, 1, !Up_Down);
		Box(number, 6, 6 - number, number + 1, 7, 7 - number, red, green, blue, 1, !Up_Down);
		Box(number, 6, 6, number + 1, 7, 7, red, green, blue, 1, !Up_Down);
		Box(0, 6, 6 - number, 1, 7, 7 - number, red, green, blue, 1, !Up_Down);
		Box(0, 6 - number, 6, 1, 7 - number, 7, red, green, blue, 1, !Up_Down);
		Box(number, 6 - number, 6 - number, number + 1, 7 - number, 7 - number, red, green, blue, 1, !Up_Down);
		Box(number, 6 - number, 6, number + 1, 7 - number, 7, red, green, blue, 1, !Up_Down);
		Box(0, 6 - number, 6 - number, 1, 7 - number, 7 - number, red, green, blue, 1, !Up_Down);
	}
	else if (number < 30)
	{
		if (6 == number)
			for (i = 0; i < 4; i++)
				datA[i] = 6 * i;

		for (i = 0; i < 4; i++)
		{
			t = datA[i] % 24;
			x = box1[t] >> 4;
			y = box1[t] & 0x0f;
			Box(x, y, 0, x + 1, y + 1, 1, red, green, blue, 1, Up_Down);
			Box(x, y, 6, x + 1, y + 1, 7, red, green, blue, 1, Up_Down);
		}
		for (i = 0; i < 4; i++)
			datA[i]++;
	}
	else if (number < 54)
	{
		for (i = 0; i < 4; i++)
		{
			t = datA[i] % 24;
			x = box1[t] >> 4;
			y = box1[t] & 0x0f;
			Box(x, y, 0, x + 1, y + 1, 1, red, green, blue, 1, Up_Down);
			Box(x, y, 6, x + 1, y + 1, 7, red, green, blue, 1, Up_Down);
		}
		for (i = 0; i < 4; i++)
			datA[i]--;
	}
	else if (number < 78)
	{
		for (i = 0; i < 4; i++)
		{
			t = datA[i] % 24;
			x = box1[t] >> 4;
			y = box1[t] & 0x0f;
			Box(x, 0, y, x + 1, 1, y + 1, red, green, blue, 1, Up_Down);
			Box(x, 6, y, x + 1, 7, y + 1, red, green, blue, 1, Up_Down);
		}
		for (i = 0; i < 4; i++)
			datA[i]++;
	}
	else if (number < 102)
	{
		for (i = 0; i < 4; i++)
		{
			t = datA[i] % 24;
			x = box1[t] >> 4;
			y = box1[t] & 0x0f;
			Box(x, 0, y, x + 1, 1, y + 1, red, green, blue, 1, Up_Down);
			Box(x, 6, y, x + 1, 7, y + 1, red, green, blue, 1, Up_Down);
		}
		for (i = 0; i < 4; i++)
			datA[i]--;
	}
	else if (number < 108)
	{
		number = 108 - number;
		Box(0, 6, 6, 1, 7, 7, red, green, blue, 1, Up_Down);
		Box(number, 6, 6 - number, number + 1, 7, 7 - number, red, green, blue, 1, Up_Down);
		Box(number, 6, 6, number + 1, 7, 7, red, green, blue, 1, Up_Down);
		Box(0, 6, 6 - number, 1, 7, 7 - number, red, green, blue, 1, Up_Down);
		Box(0, 6 - number, 6, 1, 7 - number, 7, red, green, blue, 1, Up_Down);
		Box(number, 6 - number, 6 - number, number + 1, 7 - number, 7 - number, red, green, blue, 1, Up_Down);
		Box(number, 6 - number, 6, number + 1, 7 - number, 7, red, green, blue, 1, Up_Down);
		Box(0, 6 - number, 6 - number, 1, 7 - number, 7 - number, red, green, blue, 1, Up_Down);
	}
}

const uint8_t DNASum[28] =
{
0x00,0x20,0x40,0x60,0x80,0xa0,0xc0,0xe0,0xe4,0xe8,0xec,0xf0,0xf4,0xf8,
0xfc,0xdc,0xbc,0x9c,0x7c,0x5c,0x3c,0x1c,0x18,0x14,0x10,0x0c,0x08,0x04
};

/*******************************************************************************
 * @name     :void DNA_Change(int8_t number,int8_t red,int8_t green,int8_t blue)
 * @param    :number→显示的效果顺序
 * @param    :red→红色的大小(范围0--255)
 * @param    :green→绿色的大小(范围0--255)
 * @param    :blue→蓝色的大小(范围0--255)
 * @author   :图腾实验室→图腾
 * @details  :DNA旋转效果
*******************************************************************************/
void DNA_Change(int16_t number, uint8_t red, uint8_t green, uint8_t blue)
{
	int8_t i = 0;
	int8_t x = 0, y = 0, x1 = 0, y1 = 0, t = 0, j = 0;
	static int8_t datD[8];
	number %= 255;
	if (0 == number)
		for (i = 0; i < 8; i++)
			datD[i] = 14;

	if (number < 85)
	{
		clearAll();																		//清除所有缓存               
		for (j = 0; j < 8; j++)
		{
			t = datD[j] % 28;
			x = DNASum[t] >> 5;
			y = (DNASum[t] >> 2) & 0x07;

			t = (datD[j] - 14) % 28;
			x1 = DNASum[t] >> 5;
			y1 = (DNASum[t] >> 2) & 0x07;
			line(x, y, j, x1, y1, j, red, green, blue);
		}
		for (j = 0; j < 8; j++)
			if ((number > j)&(j > number - 71))
				datD[j]++;
	}
	else if (number < 170)
	{
		clearAll();																		//清除所有缓存               
		for (j = 0; j < 8; j++)
		{
			t = datD[j] % 28;
			x = DNASum[t] >> 5;
			y = (DNASum[t] >> 2) & 0x07;
			t = (datD[j] - 14) % 28;
			x1 = DNASum[t] >> 5;
			y1 = (DNASum[t] >> 2) & 0x07;
			line(x, y, j, x1, y1, j, red, green, blue);
		}
		for (j = 0; j < 8; j++)
			if (((number - 85) > j) & (j > (number - 85) - 71))
				datD[j]--;
	}
	else if (number < 199)
	{
		clearAll();																		//清除所有缓存
		t = datD[0] % 28;
		x = DNASum[t] >> 5;
		y = (DNASum[t] >> 2) & 0x07;
		t = (datD[0] - 14) % 28;
		x1 = DNASum[t] >> 5;
		y1 = (DNASum[t] >> 2) & 0x07;
		PlaneXY(x, y, 0, x1, y1, 7, red, green, blue, 0);
		PlaneXY(x, y, 1, x1, y1, 6, red, green, blue, 0);
		datD[0]++;
	}
	else if (number < 215)
	{
		clearAll();																		//清除所有缓存
		t = datD[0] % 28;
		x = DNASum[t] >> 5;
		y = (DNASum[t] >> 2) & 0x07;
		t = (datD[0] - 14) % 28;
		x1 = DNASum[t] >> 5;
		y1 = (DNASum[t] >> 2) & 0x07;
		PlaneXY(x, y, 0, x1, y1, 7, red, green, blue, 1);
		datD[0]--;
	}
	else if (number < 223)
	{
		i = number - 215;
		line(i, i, 0, 0, 0, i, BLACK);
	}
	else if (number < 229)
	{
		i = number - 222;
		line(i, i, 7, 7, 7, i, BLACK);
	}
	else if (number < 236)
	{
		clearAll();																		//清除所有缓存
		i = number - 228;
		Box(7, 7, 7, 7 - i, 7 - i, 7 - i, red, green, blue, 0, 0);
	}
	else if (number < 242)
	{
		clearAll();																		//清除所有缓存
		i = number - 235;
		Box(0, 0, 0, 7 - i, 7 - i, 7 - i, red, green, blue, 0, 0);
	}
	else if (number < 249)
	{
		clearAll();																		//清除所有缓存
		i = number - 241;
		Box(0, 0, 0, i, i, i, red, green, blue, 0, 0);
	}
	else if (number < 255)
	{
		clearAll();																		//清除所有缓存
		i = number - 248;
		Box(7, 0, 0, i, 7 - i, 7 - i, red, green, blue, 0, 0);
	}
}

const uint8_t waveline[13] = { 0,1,2,0x23,5,6,7,6,5,0x23,2,1,0 };
const uint8_t wave[24] =
{
0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x16,0x26,0x36,0x46,0x56,
0x66,0x65,0x64,0x63,0x62,0x61,0x60,0x50,0x40,0x30,0x20,0x10
};
const uint8_t place[63] =
{
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,0,2,4,6,8,10,12,14,
16,18,20,22,0,3,6,9,12,15,18,21,0,4,8,12,16,20,0,5,10,15,20,0,6,12,18,0,7,14,21
};

/*******************************************************************************
 * @name     :void Waveform(int16_t number,int8_t red,int8_t green,int8_t blue)
 * @param    :number→显示的效果顺序
 * @param    :red→红色的大小(范围0--255)
 * @param    :green→绿色的大小(范围0--255)
 * @param    :blue→蓝色的大小(范围0--255)
 * @author   :图腾实验室→图腾
 * @details  :波浪的变化效果
*******************************************************************************/
void Waveform(int16_t number, uint8_t red, uint8_t green, uint8_t blue)
{
	char t, x, y;

	number %= 204;
	if (number < 78)
	{
		number %= 13;
		if (waveline[number] >> 4)
		{
			t = waveline[number] & 0x0f;
			line(0, 0, t + 1, 0, 7, t + 1, red, green, blue);
		}
		else
			t = waveline[number];
		line(0, 0, t, 0, 7, t, red, green, blue);
		Trans();
	}
	else if (number < 141)
	{
		t = number - 78;
		x = wave[place[t]] >> 4;
		y = wave[place[t]] & 0x0f;
		PlaneXY(0, x, y, 0, x + 1, y + 1, red, green, blue, 1);
		Trans();
	}
	else if (number < 204)
	{
		t = number - 141;
		x = wave[place[t]] >> 4;
		y = wave[place[t]] & 0x0f;
		set(0, x, y, red, green, blue);
		Trans();
	}
}

const uint8_t Dat_print[] = {					//打印函数使用
	//取模方式：阴码，顺向，列行式
0X00,0X00,0X81,0XFF,0XFF,0X81,0X00,0X00,	//I
0X1C,0X3E,0X7E,0XFC,0XFC,0X7E,0X3E,0X1C,	//心
0X3F,0X7F,0X80,0X80,0X80,0X80,0X7F,0X3F,	//U
0X3C,0X42,0X14,0XA1,0XA1,0X14,0X42,0X3C,	//笑脸
0X00,0X73,0XE9,0X89,0X89,0X8F,0X4F,0X00,	//5
0X00,0XC6,0X86,0X89,0X99,0XB1,0XE7,0XC6,	//2
0X3C,0X7E,0X81,0X81,0X81,0X7E,0X3C,0X00,	//0
0X00,0X00,0X3C,0X3C,0X3C,0X3C,0X00,0X00,	//正方形
0X20,0X30,0X38,0X3C,0X3C,0X38,0X30,0X20,	//三角形
0X08,0X14,0X22,0X77,0X14,0X14,0X14,0X1C,	//箭头
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//全亮
0X00,0X00,0X80,0XFF,0XFF,0X82,0X00,0X00,	//1
0X00,0X76,0XFF,0X89,0X89,0X81,0XC2,0X00,	//3
0X00,0X00,0X80,0XFF,0XFF,0X82,0X00,0X00,	//1
0X20,0XA0,0XFF,0XFF,0XA3,0X22,0X3C,0X30		//4
};

/*******************************************************************************
 * @name     :void Face(const uint8_t *Data,int8_t layerA,int8_t red,int8_t green,int8_t blue,int8_t direction)
 * @param    :Data	→一帧编码起始地址
 * @param    :row   →第几面
 * @param    :red	→红色的大小(范围0--255)
 * @param    :green	→绿色的大小(范围0--255)
 * @param    :blue	→蓝色的大小(范围0--255)
 * @param    :direction	→方向：0为向前打印，1为向下打印
 * @author   :图腾实验室→图腾
 * @details  :一面的数据
*******************************************************************************/
void Face(const uint8_t *Data, int8_t row, uint8_t red, uint8_t green, uint8_t blue, int8_t direction)
{
	uint8_t i = 0, k = 0;
	int j = 0;
	row %= 8;
	for (i = 0; i < 64; i++)
	{
		if (direction)
		{
			k = (7 - (i & 0x07)) * 24 + (i >> 3) * 3;
			j = (7 - row) * 192;
		}
		else
		{
			k = (7 - row) * 24 + (i >> 3) * 3;
			j = (7 - (i & 0x07)) * 192;
		}
		if (Data[i / 8] & (0x80 >> (i % 8)))
		{
			rgbled[setLED][rgb_order[k + 1] + j] = red;												//将前面的数据复制到后面		
			rgbled[setLED][rgb_order[k + 0] + j] = green;											//将前面的数据复制到后面
			rgbled[setLED][rgb_order[k + 2] + j] = blue;											//将前面的数据复制到后面
		}
		else
		{
			rgbled[setLED][rgb_order[k + 1] + j] = 0;												//将前面的数据复制到后面		
			rgbled[setLED][rgb_order[k + 0] + j] = 0;												//将前面的数据复制到后面
			rgbled[setLED][rgb_order[k + 2] + j] = 0;												//将前面的数据复制到后面
		}
	}
}
/*******************************************************************************
 * @name     :void Frame(const uint8_t *Data,int8_t red,int8_t green,int8_t blue)
 * @param    :Data	→一帧编码起始地址
 * @param    :layerA→第几层
 * @param    :red	→红色的大小(范围0--255)
 * @param    :green	→绿色的大小(范围0--255)
 * @param    :blue	→蓝色的大小(范围0--255)
 * @param    :direction	→方向：0为向前打印，1为向下打印
 * @author   :图腾实验室→图腾
 * @details  :一面的数据
*******************************************************************************/
void Frame(const uint8_t *Data, uint8_t red, uint8_t green, uint8_t blue, int8_t direction)
{
	uint8_t i = 0;
	for (i = 0; i < 8; i++)
		Face(Data + i * 8, i, red, green, blue, direction);
}

/*******************************************************************************
 * @name     :void print(int number,const uint8_t *Data,int8_t red,int8_t green,int8_t blue,char m,int8_t direction)
 * @param    :number	→显示的顺序
 * @param    :Data		→一帧编码起始地址
 * @param    :red		→红色的大小(范围0--255)
 * @param    :green		→绿色的大小(范围0--255)
 * @param    :blue		→蓝色的大小(范围0--255)
 * @param    :m			→m=0中空显示,m=1实心显示
 * @param    :direction	→方向：0为向前打印，1为向下打印
 * @author   :图腾实验室→图腾
 * @details  :打印图案
*******************************************************************************/
void print(int number, const uint8_t *Data, uint8_t red, uint8_t green, uint8_t blue, char m, int8_t direction)
{
	uint8_t p;
	char i, j, k;
	static uint8_t Dat_temp[64];
	number %= 77;
	if (0 == number)
		for (i = 0; i < 8; i++)
			Dat_temp[7 * 8 + i] = 0xff;

	if (number < 64)
	{
		i = number / 8;									//行切换
		j = number % 8;									//点移动

		p = Data[i] & (0x01 << j);
		if (p)
		{
			for (k = 6; k; k--)
			{
				if (m == 1 && k == 6)
				{
				}
				else
					Dat_temp[(k + 1) * 8 + 7 - i] &= (p ^ 0xff);
				Dat_temp[k * 8 + 7 - i] |= (0x01 << j);
				Frame(Dat_temp, red, green, blue, direction);
			}
			Dat_temp[1 * 8 + 7 - i] = 0;
			Dat_temp[7 - i] |= p;
			Frame(Dat_temp, red, green, blue, direction);
		}
		//		Dat_temp[7-i]|=p;
	}
	else if (number < 68)
		Frame(Dat_temp, red, green, blue, direction);
	else if (68 == number)
		Dat_temp[0] = 0;
	else if (number < 76)
	{
		for (i = 7; i; i--)
			Dat_temp[i] = Dat_temp[i - 1];
		Frame(Dat_temp, red, green, blue, direction);
	}
	else if (76 == number)
	{
		for (i = 0; i < 8; i++)
			Dat_temp[i] = 0;
	}
}


/*******************************************************************************
 * @name     :void Move(uint8_t *Data_Move,uint8_t d,uint8_t b,uint8_t c,uint8_t e)
 * @author   :图腾实验室→图腾
 * @details  :滚动字幕数据处理
*******************************************************************************/
void Move(uint8_t *Data_Move, uint8_t d, uint8_t b, uint8_t c, uint8_t e)
{
	char i;
	for (i = 0; i < 8; i++)
	{
		Data_Move[i] = e & 0x01;
		e >>= 1;
	}
	Data_Move[7] |= (c << 1);
	Data_Move[6] |= (c & 0x80);
	for (i = 0; i < 6; i++)
		Data_Move[5 - i] |= ((b << (7 - i)) & 0x80);
	d = Word_Swap(d);
	Data_Move[0] |= ((d >> 1) & 0x7e);
}

void sphere(int x0, int y0, int z0, int r, uint8_t R, uint8_t G, uint8_t B)
{
	int x, y, z, xa, ya, za, xb, yb, zb, xr, yr, zr, xx, yy, zz, rr = r*r;
	// bounding box
	xa = x0 - r; if (xa < 0) xa = 0; xb = x0 + r; if (xb > SIZE) xb = SIZE;
	ya = y0 - r; if (ya < 0) ya = 0; yb = y0 + r; if (yb > SIZE) yb = SIZE;
	za = z0 - r; if (za < 0) za = 0; zb = z0 + r; if (zb > SIZE) zb = SIZE;
	// project xy plane
	for (x = xa, xr = x - x0, xx = xr*xr; x < xb; x++, xr++, xx = xr*xr)
	{
		for (y = ya, yr = y - y0, yy = yr*yr; y < yb; y++, yr++, yy = yr*yr)
		{
			zz = rr - xx - yy; if (zz < 0) continue; zr = sqrt(zz);
			z = z0 - zr; if ((z > 0) && (z < SIZE)) set(x, y, z, R, G, B);
			z = z0 + zr; if ((z > 0) && (z < SIZE)) set(x, y, z, R, G, B);
		}
	}
	// project xz plane
	for (x = xa, xr = x - x0, xx = xr*xr; x < xb; x++, xr++, xx = xr*xr)
	{
		for (z = za, zr = z - z0, zz = zr*zr; z < zb; z++, zr++, zz = zr*zr)
		{
			yy = rr - xx - zz; if (yy < 0) continue; yr = sqrt(yy);
			y = y0 - yr; if ((y > 0) && (y < SIZE)) set(x, y, z, R, G, B);
			y = y0 + yr; if ((y > 0) && (y < SIZE)) set(x, y, z, R, G, B);
		}
	}
	// project yz plane
	for (y = ya, yr = y - y0, yy = yr*yr; y < yb; y++, yr++, yy = yr*yr)
	{
		for (z = za, zr = z - z0, zz = zr*zr; z < zb; z++, zr++, zz = zr*zr)
		{
			xx = rr - zz - yy; if (xx < 0) continue; xr = sqrt(xx);
			x = x0 - xr; if ((x > 0) && (x < SIZE)) set(x, y, z, R, G, B);
			x = x0 + xr; if ((x > 0) && (x < SIZE)) set(x, y, z, R, G, B);
		}
	}
}






