#include "stm32f10x.h"
#include "led.h"
#include "timer.h"
#include "calculate.h"
#include "snake.h"
#include "adc.h"
#include "fft.h"
#include "ir_nec.h"
#include "Time_Show.h"
#include "graphics.h"


#include "malloc.h"  
#include "exfuns.h"
#include "MMC_SD.h" 
#include "fattester.h"	 


#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"	 



void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);			//配置GPIOx的时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}


void SystemClock(uint32_t pllMull)
{
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	
	RCC_DeInit();
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);
	do
	{
		HSEStatus = RCC->CR & RCC_CR_HSERDY;
		StartUpCounter++;  
	} while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((RCC->CR & RCC_CR_HSERDY) != RESET)
		HSEStatus = (uint32_t)0x01;
	else
		HSEStatus = (uint32_t)0x00;

	if (HSEStatus == (uint32_t)0x01)
	{
		FLASH->ACR |= FLASH_ACR_PRFTBE;
		FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
		FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

		RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
		RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | pllMull);

		RCC->CR |= RCC_CR_PLLON;

		while((RCC->CR & RCC_CR_PLLRDY) == 0) { }

		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
		RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08) { }
	}
}

void ID_ms(uint32_t ms)
{
	uint32_t i;

	for (i = 0; i < SystemCoreClock / (300 * 1000 / ms); i++)
	{
	}
}

volatile uint32_t CPUID[3];


//检测CPUID是否已经注册，没有注册直接卡住CPU不工作
void CheckCPU_ID(void)
{
	uint32_t i = 0;
	uint32_t ID_0 = 0, ID_1 = 0, ID_2 = 0, MiWen = 0;
	CPUID[0] = *(vu32*)(0x1FFFF7E8);
	CPUID[1] = *(vu32*)(0x1FFFF7EC);
	CPUID[2] = *(vu32*)(0x1FFFF7F0);
	
	ID_0 = (CPUID[0] ^ 0xffffffff) | CPUID[1];
	ID_1 = CPUID[1] | (CPUID[2] ^ 0xffffffff);
	ID_2 = (CPUID[2] ^ 0xffffffff) | (CPUID[0] ^ 0xffffffff);

	
	MiWen = (ID_0 ^ ID_1) ^ ID_2;
	
	//ID对不上，程序没有注册
	while (0XB83812EF != MiWen)							//图腾ID
	{
		SystemClock(RCC_CFGR_PLLMULL9);					//72M 要不用不了虚拟USB
		LED_Init();
		
		ID_ms(1800);
		USB_Port_Set(0); 								// USB先断开
		ID_ms(700);
		USB_Port_Set(1);								// USB再次连接
		Set_USBClock();
		USB_Interrupts_Config();
		USB_Init();
		while(1)
		{
			usb_printf("0X%8X\r\n",MiWen);
			i = 5000000;
			while(--i);
		}
	}
	//ID对上，程序已经注册
}


int main(void)
{
	uint8_t i = 0;
	
	CheckCPU_ID();						//检测CPUID是否已经注册，没有注册直接卡住CPU不工作
	
	tf_readRead = 8;
	random8();
	setup();
	GPIO_Configuration();				//初始化GPIO外设
	NVIC_Configuration();				//中断优先级的分组设置
	IR_ENC_Init(128);					//红外线解码初始化
	LED_Init();
	
	fft_ADC_Init();						//对fft采集的数据进行ADC的初始化
	Timer2_Init(ScanFosc, ScanTime);	//定时器初始化  
	Timer3_Init(12800, 60);           	//动画显示定时器初始化	
	Timer4_Init(1280, 10);				//10K的ADC采样率           						


	exfuns_init();						//为fatfs相关变量申请内存				 
	mem_init();							//初始化内存池	
	
	i = 0;
	while(SD_Initialize())				//检测SD卡
	{
		if(++i > 60)
			break;
	}								   	
 	exfuns_init();						//为fatfs相关变量申请内存				 
  	f_mount(fs[0],"0:",1); 				//挂载SD卡 

	Cube_MODE = 2;
	
	while (1)
	{
		if(1 != Cube_MODE)
			TIM_Cmd(TIM4, DISABLE); 
		else
			TIM_Cmd(TIM4, ENABLE); 
		
		
		if (0 == Cube_MODE)
		{
			mf_scan_files("0:\\rgbCUBE888");
		}
		else if (1 == Cube_MODE)
		{
			fft_Data();								//进行fft的ADC的数据采集
			fft_Convert(fftData);					//N点fft计算函数,fft计算转换处理函数
			fft_powerMag();							//fft计算出幅值函数，fftOut数组输出
			fft_Display();							//fft计算处理之后的显示函数
		}
		else if (2 == Cube_MODE)
		{
			while (2 == Cube_MODE)
			{
				loop();
			}
		}
		else if (3 == Cube_MODE)
		{
			ClearRGB(0,light_green);				//给颜色赋值
			ClearRGB(2,light_blue);					//给颜色赋值
			ClearRGB(1,light_red);					//给颜色赋值
		}			
	}
}

