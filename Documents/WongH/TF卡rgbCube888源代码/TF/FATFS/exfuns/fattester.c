#include "fattester.h"	 
#include "mmc_sd.h"
#include "exfuns.h"
#include "malloc.h"		  
#include "ff.h"
#include "string.h"
#include "led.h"


//为磁盘注册工作区	 
//path:磁盘路径，比如"0:"、"1:"
//mt:0，不立即注册（稍后注册）；1，立即注册
//返回值:执行结果
u8 mf_mount(u8* path, u8 mt)
{
	return f_mount(fs[0], (const TCHAR*)path, mt);
}


//读出数据
//len:读出的长度
//返回值:执行结果
u8 mf_read(u16 len)
{
	u16 i;
	u8 res = 0;
	u16 tlen = 0;
	for (i = 0;i < len / 512;i++)
	{
		res = f_read(file, fatbuf, 512, &br);
		if (res)
			break;
		else
			tlen += br;
	}
	if (len % 512)
	{
		res = f_read(file, fatbuf, len % 512, &br);
		if (res)	//读数据出错了
		{
		}
		else
			tlen += br;
	}
	return res;
}


uint8_t strLenght(char *p)
{
	uint8_t lenght = 0;
	while(*p != '\0')
	{
		lenght++;
		p++;
	}
	return lenght;
}

uint8_t StringPath[80];

void fileDirectory(uint8_t *s1,char *s2)
{
	uint8_t strL1 = 0, strL2 = 0, i = 0;	
	strL1 = strLenght((char *)s1);
	for(i = 0; i < strL1; i++)
		StringPath[i] = s1[i];
		
	StringPath[strL1] = '\\';
	
	strL2 = strLenght(s2);
	for(i = 0; i < strL2; i++)
		StringPath[i + strL1 + 1] = s2[i];
		
	StringPath[strL1 + strL2 + 1] = '\0';
}

uint8_t Directory_str(uint8_t *s1)
{
	uint8_t strL1 = 0, i = 0;	
	strL1 = strLenght((char *)s1);
	for(i = 0; i < strL1; i++)
		StringPath[i] = s1[i];
	
	StringPath[strL1] = '\\';
	
	return (strL1+1);
}


void file_str(uint8_t num, char *s1)
{
	uint8_t strL1 = 0, i = 0;	
	strL1 = strLenght(s1);
	for(i = 0; i < strL1; i++)
		StringPath[i + num] = s1[i];
	
	StringPath[num + strL1] = '\0';
}


uint8_t ASCII_TO_HEX(char datM,char datS)
{
	uint8_t temp = 0;
	switch(datM)
	{
		case '0': temp = 0; break;
		case '1': temp = 1; break;
		case '2': temp = 2; break;
		case '3': temp = 3; break;
		case '4': temp = 4; break;
		case '5': temp = 5; break;
		case '6': temp = 6; break;
		case '7': temp = 7; break;
		case '8': temp = 8; break;
		case '9': temp = 9; break;
		case 'A': 
		case 'a': temp = 10; break;
		case 'B': 
		case 'b': temp = 11; break;
		case 'C': 
		case 'c': temp = 12; break;
		case 'D': 
		case 'd': temp = 13; break;
		case 'E': 
		case 'e': temp = 14; break;
		case 'F': 
		case 'f': temp = 15; break;
	}
	
	temp <<= 4;
	
	switch(datS)
	{
		case '0': temp += 0; break;
		case '1': temp += 1; break;
		case '2': temp += 2; break;
		case '3': temp += 3; break;
		case '4': temp += 4; break;
		case '5': temp += 5; break;
		case '6': temp += 6; break;
		case '7': temp += 7; break;
		case '8': temp += 8; break;
		case '9': temp += 9; break;
		case 'A': 
		case 'a': temp += 10; break;
		case 'B': 
		case 'b': temp += 11; break;
		case 'C': 
		case 'c': temp += 12; break;
		case 'D': 
		case 'd': temp += 13; break;
		case 'E': 
		case 'e': temp += 14; break;
		case 'F': 
		case 'f': temp += 15; break;
	}
	
	return temp;
}

//遍历文件
//path:路径
//返回值:执行结果
u8 mf_scan_files(u8 * path)
{
	uint16_t i = 0, sumN = 0, sumM = 0, temp1 = 0, temp2 = 0;
	uint8_t x = 0, y = 0, z = 0;
	uint8_t state = 0;
	uint8_t strL = 0;
	uint8_t DirstrL = 0;
	FRESULT res;
	char *fn;   /* This function is assuming non-Unicode cfg. */
#if _USE_LFN
	fileinfo.lfsize = _MAX_LFN * 2 + 1;
	fileinfo.lfname = mymalloc(fileinfo.lfsize);
#endif		  

	i = 0;
	while(SD_Initialize())			//检测SD卡
	{
		if(++i >= 100)
			break;
	}	
	
	if(i != 100)
	{
		tf_readStop = 0;
		
		res = f_opendir(&dir, (const TCHAR*)path); //打开一个目录
		DirstrL = Directory_str(path);	//保存目录文件的字符串
		if (res == FR_OK)
		{
			while (1)
			{
				res = f_readdir(&dir, &fileinfo);                   //读取目录下的一个文件
				if (res != FR_OK || fileinfo.fname[0] == 0) 
					break; 	 										//错误了/到末尾了,退出
				//if (fileinfo.fname[0] == '.') continue;             //忽略上级目录
#if _USE_LFN
				fn = *fileinfo.lfname ? fileinfo.lfname : fileinfo.fname;
#else							   
				fn = fileinfo.fname;
#endif	                                              		/* It is a file. */
				strL = strLenght(fn);							//字符串长度
				if(strL > 9)
				{
					if ('.' == fn[strL - 9] && 'r' == fn[strL - 8] && 'g' == fn[strL - 7] && 
						'b' == fn[strL - 6] && 'C' == fn[strL - 5] && 'U' == fn[strL - 4] && 
						'B' == fn[strL - 3] && 'E' == fn[strL - 2] && '8' == fn[strL - 1])
					{
						file_str(DirstrL,fn);		//整理目录文件夹与文件名的字符串
						
						state = f_open(file, (const TCHAR*)StringPath, FA_READ);	//打开文件夹
						if(state)									//打开文件失败
							continue;			

						while(1)
						{
							while(tf_readStop) 		//动画是否暂停
							{
								if(0 != Cube_MODE)
								{								
									f_close(file);					//关闭文件				
									myfree(fileinfo.lfname);
									return FR_INVALID_PARAMETER;
								}
							}
							
							if(0 == tf_readflag)
							{
								res = f_read(file, fatbuf, 3072, &br);
								if(res || br == 0)
									break;
								
								if(0 != Cube_MODE)
								{								
									f_close(file);					//关闭文件				
									myfree(fileinfo.lfname);
									return FR_INVALID_PARAMETER;
								}
								tf_readflag = 1;
							}
							
							if(2 == tf_readflag)
							{
								for(y = 0; y < 8; y++)
								{
									sumN = y * 192;
									for(z = 0; z < 8; z++)
									{
										sumM = z * 384;
										for(x = 0; x < 8; x++)
										{
											temp1 = 3 * (x + (z << 3));
											temp2 = 6 * (7 - x + (y << 3)) + sumM;
											rgbled[setLED][rgb_order[temp1 + 1] + sumN] = ASCII_TO_HEX(fatbuf[temp2 + 0],fatbuf[temp2 + 1]);
											rgbled[setLED][rgb_order[temp1 + 0] + sumN] = ASCII_TO_HEX(fatbuf[temp2 + 2],fatbuf[temp2 + 3]);
											rgbled[setLED][rgb_order[temp1 + 2] + sumN] = ASCII_TO_HEX(fatbuf[temp2 + 4],fatbuf[temp2 + 5]);
									
										}
									}
								}
								tf_readflag = 0;
							}
							
							if(0 != Cube_MODE)
							{								
								f_close(file);					//关闭文件				
								myfree(fileinfo.lfname);
								return FR_INVALID_PARAMETER;
							}
						}				
						f_close(file);								//关闭文件		
					}					
				}
			}
		}
	}
	myfree(fileinfo.lfname);
	return res;
}

//文件读写指针偏移
//offset:相对首地址的偏移量
//返回值:执行结果.
u8 mf_lseek(u32 offset)
{
	return f_lseek(file, offset);
}

//读取文件当前读写指针的位置.
//返回值:位置
u32 mf_tell(void)
{
	return f_tell(file);
}

//读取文件大小
//返回值:文件大小
u32 mf_size(void)
{
	return f_size(file);
}

//创建目录
//pname:目录路径+名字
//返回值:执行结果
u8 mf_mkdir(u8*pname)
{
	return f_mkdir((const TCHAR *)pname);
}

//格式化
//path:磁盘路径，比如"0:"、"1:"
//mode:模式
//au:簇大小
//返回值:执行结果
u8 mf_fmkfs(u8* path, u8 mode, u16 au)
{
	return f_mkfs((const TCHAR*)path, mode, au);//格式化,drv:盘符;mode:模式;au:簇大小
}

//删除文件/目录
//pname:文件/目录路径+名字
//返回值:执行结果
u8 mf_unlink(u8 *pname)
{
	return  f_unlink((const TCHAR *)pname);
}

//修改文件/目录名字(如果目录不同,还可以移动文件哦!)
//oldname:之前的名字
//newname:新名字
//返回值:执行结果
u8 mf_rename(u8 *oldname, u8* newname)
{
	return  f_rename((const TCHAR *)oldname, (const TCHAR *)newname);
}

//获取盘符（磁盘名字）
//path:磁盘路径，比如"0:"、"1:"  
void mf_getlabel(u8 *path)
{
	u8 buf[20];
	u32 sn = 0;
	u8 res;
	res = f_getlabel((const TCHAR *)path, (TCHAR *)buf, (DWORD*)&sn);
	if (res == FR_OK)
	{
	}
}


//设置盘符（磁盘名字），最长11个字符！！，支持数字和大写字母组合以及汉字等
//path:磁盘号+名字，比如"0:ALIENTEK"、"1:OPENEDV"  
void mf_setlabel(u8 *path)
{
	u8 res;
	res = f_setlabel((const TCHAR *)path);
	if (res == FR_OK)
	{
	}
}

//从文件里面读取一段字符串
//size:要读取的长度
void mf_gets(u16 size)
{
	TCHAR* rbuf;
	rbuf = f_gets((TCHAR*)fatbuf, size, file);
	if (*rbuf == 0)
		return;							//没有数据读到
	else
	{
	}
}

//需要_USE_STRFUNC>=1
//写一个字符到文件
//c:要写入的字符
//返回值:执行结果
u8 mf_putc(u8 c)
{
	return f_putc((TCHAR)c, file);
}

//写字符串到文件
//c:要写入的字符串
//返回值:写入的字符串长度
u8 mf_puts(u8*c)
{
	return f_puts((TCHAR*)c, file);
}













