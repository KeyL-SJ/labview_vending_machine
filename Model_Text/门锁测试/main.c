#include <reg52.h>
#include <intrins.h>
#include <key.h>

//控制线黑线接5V，红线接步进电机驱动的控制引脚

sbit lock1 = P1^0;

void Key_Pros();
unsigned char Key_Value,Key_Old,Key_Down;
unsigned int Key_Slow_Down;

//void Timer0Init(void)		//1毫秒@11.0592MHz
//{
//	TMOD &= 0xF0;		//设置定时器模式
//	TL0 = 0xCD;		//设置定时初始值
//	TH0 = 0xD4;		//设置定时初始值
//	TF0 = 0;		//清除TF0标志
//	TR0 = 1;		//定时器0开始计时
//	
//	EA = 1;
//	ET0 = 1;
//}


void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 23;
	j = 205;
	k = 120;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main(void)
{
	lock1 = 1;
//	Timer0Init();
	while (1)
	{
		Key_Pros();
	}
}

void Key_Pros(void)
{
//	if(Key_Slow_Down) return;
//	Key_Slow_Down = 1;
	
	Key_Value = Key_Read_BTN();
	Key_Down = Key_Value & (Key_Old ^ Key_Value);
	Key_Old = Key_Value;
	
	if(Key_Down == 1)
	{
		lock1 = 1;Delay500ms();
	}
	else
	{
		lock1 = 0;
	}
}

//void Timer0_Handler(void) interrupt 1
//{
//	if(++Key_Slow_Down == 10) Key_Slow_Down = 0;
//}
