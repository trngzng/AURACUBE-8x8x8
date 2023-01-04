#include "IR_NEC.h"

void IR_ENC_Init(uint16_t psc)							//红外线解码初始化
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);		//使能时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;					//上拉输入模式
	GPIO_Init(GPIOB, &GPIO_InitStructure);							//初始化GPIO的模式

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);          	//时钟使能

	TIM_DeInit(TIM1);
	TIM_TimeBaseStructure.TIM_Period = Step;                 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = (psc - 1);              	//设置用来作为TIMx时钟频率除数的预分频值   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);              	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;        		//TIM1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    	//先占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            	//从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               	//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                              	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM1, ENABLE);                                       	//使能TIMx外设
}
unsigned char	IR_BT;		         								//解码效果返回：0无效，1有效
unsigned char	NEC[4];		         								//解码存放：16位用户码、操作码正反码
unsigned int	cntStep;											//步数计
unsigned char	IRa, IRb;			 								//电位状态保存
unsigned char	IRsync;				 								//同步标志
unsigned char	BitN;                								//位码装载数

/*┈┈┈┈┈┈┈┈┈┈ 基准 ┈┈┈┈┈┈┈┈┈┈┈*/
#define    Boot_Limit	    (((9000+4500) +2000)/Step)	  			//引导码周期上限    
#define    Boot_Lower	    (((9000+4500) -2000)/Step)	  			//引导码周期下限    
#define    Bit1_Limit       ((2250 +800)/Step)	          			//“1”周期上限
#define    Bit0_Limit       ((1125 +400)/Step)			  			//“0”周期上限

/*┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈
函数：红外线NEC周期采样解码法（定时中断，下降沿查询周期时间）
全局变量：IR_BT = 0无效
				 1有效，短按
┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈*/
void IR_NEC(void)
{
	cntStep++;		   												//步数采样

	IRb = IRa;		   												//上次电位状态
	IRa = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);					//当前电位状态

	if (IRb && !IRa)				  	  													//是否下降沿（上次高，当前低）
	{
		if (cntStep > Boot_Limit)      								//超过同步时间？
			IRsync = 0;				  								//同步位清0
		else if (cntStep > Boot_Lower)								//解码开始
		{
			IRsync = 1;
			BitN = 32;
		}															//同步位置1，装载位码数			  
		else if (IRsync)																	//如果已同步
		{
			if (cntStep > Bit1_Limit)								//再次判断是否误判
				IRsync = 0;
			else
			{
				NEC[3] >>= 1;
				if (cntStep > Bit0_Limit)
					NEC[3] |= 0x80;    								//“0”与“1”
				if (--BitN == 0)
				{
					IRsync = 0;										//同步位清0
					IR_BT = 1; 										//解码成功，成功标志置1
				}
				else if ((BitN & 0x07) == 0)												//NEC[3]每装满8位，移动保存一次（即 BitN%8 == 0）
				{
					NEC[0] = NEC[1];
					NEC[1] = NEC[2];
					NEC[2] = NEC[3];
				}
			}
		}
		cntStep = 0;   												//步数计清0
	}
}

/*******************************************************************************
 * @name     :void TIM1_IRQHandler(void)
 * @author   :图腾实验室→图腾
 * @details  :TIM1中断服务函数，对红外是按键进行解码
*******************************************************************************/

void TIM1_UP_IRQHandler(void)   									//TIM1中断
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) 				//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  				//清除TIMx的中断待处理位:TIM 中断源 

		IR_NEC();													//红外线NEC周期采样解码法（定时中断，下降沿查询周期时间）
		if (1 == IR_BT)												//遥控检测
		{
			KeyHandle();      										//遥控的按键处理		  
			IR_BT = 0;		        								//清有效标志
		}
	}
}


/*******************************************************************************
 * @name     :void KeyHandle(void)
 * @author   :图腾实验室→图腾
 * @details  :遥控的按键处理
*******************************************************************************/
void KeyHandle(void)
{
	float fade = 0;
	switch (NEC[2])
	{
		case 0x0c:
			Cube_MODE = 1;											//启动频谱模式
			clearAll();												//清除所有缓存
			break;													//按键1
		case 0x18:
			Cube_MODE = 2;											//启动动画模式
			NVIC_SystemReset();
//			mode = 0;
//			gCounter = 0;
//			modeNext = 0;
//			showLED = 0;
//			setLED = 0;
//			eNum = 0;
//			modeWait = 0;
//			modeWaitUp = 0;
//			rgb_dir = 0;
//			eCounter = 0;
//			eCounter2 = 0;
//			eInterval1 = 0;
//			eInterval2 = 0;
//			eFadeout = 0;
//			eFadeoutDone = 0;
//			counter = 0;
//	
//			SpeedSum = 0;
//			NumCount = 0;
//			pictrue_order = 0;										//动画显示的顺序
//			clearAll();												//清除所有缓存
			break;													//按键2
		case 0x5e:
			Cube_MODE = 3;											//启动夜灯模式
//			clearAll();												//清除所有缓存
			light_red = 20;
			light_green = 0;
			light_blue = 0;											//夜灯颜色变量
			break;													//按键3
		case 0x08:
			if(3 == Cube_MODE)
			{
				if(light_red <= 240)
					light_red += 10;
			}
			break;													//按键4
		case 0x1c:
			if(3 == Cube_MODE)
			{
				if(light_green <= 240)
					light_green += 10;
			}
			else if(4 == Cube_MODE)
			{
				Add_X = 0;
				Add_Y = 0;
				Add_Z = 1;            								//位移偏移量
			}
			break;													//按键5
		case 0x5a:
			if(3 == Cube_MODE)
			{
				if(light_blue <= 240)
					light_blue += 10;
			}
			break;													//按键6
		case 0x42:
			if(3 == Cube_MODE)
			{
				if(light_red >= 10)
					light_red -= 10;
			}
			break;													//按键7
		case 0x52:
			if(3 == Cube_MODE)
			{
				if(light_green >= 10)
					light_green -= 10;
			}
			else if(4 == Cube_MODE)
			{
				Add_X = 0;
				Add_Y = 0;
				Add_Z = -1;            								//位移偏移量
			}
			break;													//按键8
		case 0x4a:
			if(3 == Cube_MODE)
			{
				if(light_blue >= 10)
					light_blue -= 10;
			}
			break;													//按键9
		case 0x16:
			Cube_MODE = 0;											//启动上位机模式
			clearAll();												//清除所有缓存
			break;													//按键0
		case 0x19:
			// -key
			if(4 == Cube_MODE)
			{
				Add_X = 0;
				Add_Y = -1;
				Add_Z = 0;            								//位移偏移量
			}
			else
			{
				fade = fadeMax;    // don't change directly as other IRQ may need fadeMax
				if (fade < 20) 
					fade -= 3;
				else 
					fade -= 10;
				
				if (fade > 50) 
					fade -= 10;
				
				if (fade < 3) 
					fade = 3;
				fadeMax = fade;
			}
			break;													//-键
		case 0x0d:
			Cube_MODE = 4;											//启动贪吃蛇模式
			SpeedSum = 0;
			NumCount = 0;
			clearAll();												//清除所有缓存
			Snake_Start();											//蛇身初始化
			Snake_Above();											//给食物并且判断食物是否在蛇身上面
			Snake_Show(10, 1, 0, 0, 10, 0);							//贪吃蛇的显示函数
			break;													//OK键/C键
		case 0x07:
			// rew key
			if(0 == Cube_MODE)
			{
				if(tf_readRead < 16)
					tf_readRead += 2;
			}
			else if(4 == Cube_MODE)
			{
				Add_X = -1;
				Add_Y = 0;
				Add_Z = 0;            								//位移偏移量
			}
			else
				prevGraphic();
			break;													//快退键
		case 0x15:
			// pause key
			if(0 == Cube_MODE)
			{
				tf_readStop = !tf_readStop;
			}
			else
			{
				if (power == 2)
					power = 1;
				else if (power == 1)
					power = 2;
			}
			break;													//暂停键
		case 0x09:
			// ff key
			if(0 == Cube_MODE)
			{
				if(tf_readRead > 4)
					tf_readRead -= 2;
			}
			else if(4 == Cube_MODE)
			{
				Add_X = 1;
				Add_Y = 0;
				Add_Z = 0;            								//位移偏移量
			}
			else
				nextGraphic();
			break;													//快进键
		case 0x44:
			break;													//MODE键/TEST键
		case 0x40:
			// + key
			if(4 == Cube_MODE)
			{
				Add_X = 0;
				Add_Y = 1;
				Add_Z = 0;            								//位移偏移量
			}
			else
			{
				fade = fadeMax;   // don't change directly as other IRQ may need fadeMax
				if (fade < 20) 
					fade += 3;
				else 
					fade += 10;
				
				if (fade > 50)
					fade += 10;
				if (fade > 100) 
					fade = 100;
				fadeMax = fade;
			}
			break;													//+键
		case 0x43:
			break;													//返回键
		case 0x45:
			// power key
			if (power == 0)
			{
				power = 1;
				setAll(BLACK);
			}
			else
			{
				setAll(BLACK);
				delay(10);
				power = 0;
			}
			break;													//Power
		case 0x47:
			break;													//MENU键
		default:
			break;
	}
}



