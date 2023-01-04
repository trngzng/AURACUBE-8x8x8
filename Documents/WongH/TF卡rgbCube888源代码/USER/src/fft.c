#include "fft_tab.h"
#include "fft_list.h"
#include "fft.h"

compx fftData[fft_N]; 																	//fft数据段 				  
uint16_t fftIn[fft_N];    																//fft输入数据
uint8_t fftOut[fft_N / 2];    															//fft数据输出 

/*******************************************************************************
 * @name     :uint8_t sqrt_M(uint16_t temp)
 * @author   :图腾实验室→图腾
 * @details  :fft计算出M值
*******************************************************************************/
uint8_t sqrt_M(uint16_t temp)
{
	uint8_t m = 0;
	for (m = 1; (temp = temp / 2) != 1; m++);												//求得M的值 	
	return m;
}

//m^n函数
//uint16_t mypow(uint8_t m,uint8_t n)
//{
//	uint16_t result = 1;	 
//	while(n--)
//		result *= m;    
//	return result;
//}   

/*******************************************************************************
 * @name     :void fft_Convert(compx *xin)
 * @author   :图腾实验室→图腾
 * @details  :fft计算转换处理函数
*******************************************************************************/
//xin:输入数组大小为N+1
void fft_Convert(compx *xin)
{
	uint16_t i, j, L;
	uint16_t p;
	uint16_t le, B, ip;
	compx t;
	compx ws;

	for (L = 1; L <= M; L++) 																//fft  傅里叶变换
	{
		le = (2 << L) >> 1;
		B = le / 2;
		for (j = 0; j <= B - 1; j++)
		{
			p = (((2 << M) >> L) >> 1)*j;
			ws.real = cos_tab[p];
			ws.imag = sin_tab[p];
			for (i = j; i <= fft_N - 1; i = i + le)											//遍历M级所有的碟形
			{
				ip = i + B;
				//执行复数乘法
				t.real = xin[ip].real*ws.real - xin[ip].imag*ws.imag;
				t.imag = xin[ip].real*ws.imag + xin[ip].imag*ws.real;
				xin[ip].real = xin[i].real - t.real;
				xin[ip].imag = xin[i].imag - t.imag;
				xin[i].real = xin[i].real + t.real;
				xin[i].imag = xin[i].imag + t.imag;
			}
		}
	}
}


#define FFT_SHOW_MIN	10			//显示fft最小值
#define FFT_Compact		1			//显示fft的压缩量

/*******************************************************************************
 * @name     :void fft_powerMag(void)
 * @author   :图腾实验室→图腾
 * @details  :fft计算出幅值函数，fftOut数组输出
*******************************************************************************/
void fft_powerMag(void)
{
	int i;
	int temp = 0;
	for (i = 1; i < fft_N / 2; i++)															//计算各个频点的幅度值，对称性，计算一半就好了
	{																						//求变换后结果的模值
		fftData[i].real = sqrt(fftData[i].real * fftData[i].real + fftData[i].imag * fftData[i].imag)
			/ (i == 0 ? fft_N : (fft_N / 2));


		temp = (uint8_t)(8.0f * log10(fftData[i].real));

		if(temp <= FFT_SHOW_MIN)
			temp = 1;
		else
			temp = temp - FFT_SHOW_MIN;

		if(temp >= fftOut[i])
			fftOut[i] = temp;
		else
		{
			if(fftOut[i] > 0)
				fftOut[i]--;
		}
	}
}

/*******************************************************************************
 * @name     :void fft_Data(void)
 * @author   :图腾实验室→图腾
 * @details  :进行fft的ADC的数据采集
*******************************************************************************/
void fft_Data(void)
{
	int i = 0;
	for (i = 0; i < fft_N; i++)
	{
		fftData[List[i]].real = fftIn[i];													//将数据复制到fft的计算中去，采用查表的方式提高速度 
		fftData[List[i]].imag = 0;															//虚部清0
	}
}

const uint8_t sumfft[26] ={27,35,36,28,0,8,16,24,32,40,48,56,57,58,59,60,61,62,63,55,47,39,31,23,15,7};

/*******************************************************************************
 * @name     :void fft_Display(void)
 * @author   :图腾实验室→图腾
 * @details  :fft计算处理之后的显示函数
*******************************************************************************/
void fft_Display(void)
{
	char i,j;
	int layerB;

	for(j = 0; j < 8; j++)											//判断8个点是否需要点亮
	{
		layerB = (7 - j) * 192;
		for(i = 0; i < 26; i++)										//显示64束
		{
			if(fftOut[i + 2] > j)									//需要点亮的点
			{
				if(i < 4)
				{
					rgbled[setLED][rgb_order[3 * sumfft[i] + 1] + layerB] = 220;											
					rgbled[setLED][rgb_order[3 * sumfft[i] + 0] + layerB] = 0;
					rgbled[setLED][rgb_order[3 * sumfft[i] + 2] + layerB] = 50;									
				}	
				else
				{
					rgbled[setLED][rgb_order[3 * sumfft[i] + 1] + layerB] = 220;											
					rgbled[setLED][rgb_order[3 * sumfft[i] + 0] + layerB] = 50;
					rgbled[setLED][rgb_order[3 * sumfft[i] + 2] + layerB] = 0;									
				}
			}				
			else
			{
				rgbled[setLED][rgb_order[3 * sumfft[i] + 1] + layerB] = 0;											
				rgbled[setLED][rgb_order[3 * sumfft[i] + 0] + layerB] = 0;									
				rgbled[setLED][rgb_order[3 * sumfft[i] + 2] + layerB] = 0;
			}				
		}			
	}
}






