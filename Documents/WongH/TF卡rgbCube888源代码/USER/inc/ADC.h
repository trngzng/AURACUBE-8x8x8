#ifndef _ADC_H
#define _ADC_H

#include "stm32f10x.h"

void fft_ADC_Init(void);							//对fft采集的数据进行ADC的初始化
uint16_t Get_ADC(uint8_t ch); 						//获取ADC的数据  

#endif

