#include <Timer.h>

//void Timer1Init(void)		//1毫秒@12.000MHz
//{
//	TMOD &= 0x0F;		//设置定时器模式
//	TL1 = 0x18;		//设置定时初始值
//	TH1 = 0xFC;		//设置定时初始值
//	TF1 = 0;		//清除TF1标志
//	TR1 = 1;		//定时器1开始计时
//	
//	EA = 1;
//	ET1 = 1;
//}
void Timer0Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初始值
	TH0 = 0xD4;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
	EA = 1;
	ET0 = 1;
}
