#include <key.h>
#include <usart.h>
#include <intrins.h>
#include <stdio.h>
sbit lock1 = P2^2;
void Key_Pros(void);
void Uart_Pros(void);

unsigned int Key_Slow_Down;
unsigned char Key_Value,Key_Down,Key_Old;

unsigned char buf;
unsigned char Uart_Buf[] = " ";
unsigned char Uart_Buf_Index;

bit lock_open_close = 0;


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



void main(void)
{
	uart_init();
	while(1)
	{
		Key_Pros();
	}
}

void Uart(void) interrupt 4
{
	if (RI)
	{
		RI = 0;
		buf = SBUF; //把收到的信息从SBUF放到buf中。
		ES = 0;		//暂时关闭串口中断

		switch (buf)
		{
		case 0x31:
			P1 = 0xfe;
			break; //二进制 0011 0001  十进制 49 控制字符 1  16进制 0X31
		case 0x32:
			P1 = 0xfd;
			break; // 1111 1101
		case 0x33:
			P1 = 0xfb;
			break;
		case 0x34:
			P1 = 0xf7;
			break;
		case 0x35:
			P1 = 0xef;
			break;
		case 0x36:
			P1 = 0xdf;
			break;
		case 0x37:
			P1 = 0xbf;
			lock_open_close = 1;
			break;
		}
		ES = 1; //重新开启串口中断
		SBUF = buf;
		while (!TI)
			;
		TI = 0;
	}
}

void Uart_Pros(void)
{
	UART_send_string(Uart_Buf);
}

void Key_Pros(void)
{
	if (Key_Slow_Down)
		return;
	Key_Value = Key_Read_BTN();
	Key_Down = Key_Value & (Key_Old ^ Key_Value);
	Key_Old = Key_Value;
	
	switch(Key_Down)
	{
		case 1:
			P1 = 0xfe;
			Uart_Buf_Index = 1;
			sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
			Uart_Pros();
			break;
		case 2:
			P1 = 0xfd;
			Uart_Buf_Index = 2;
			sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
			Uart_Pros();
			break;
		case 3:
			P1 = 0xfb;
			Uart_Buf_Index = 3;
			sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
			Uart_Pros();
			break;
		case 4:
			P1 = 0xf7;
			Uart_Buf_Index = 4;
			sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
			Uart_Pros();
			break;
		case 5:
			P1 = 0xef;
			Uart_Buf_Index = 5;
			sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
			Uart_Pros();
			break;
		case 6:
			P1 = 0xdf;
			Uart_Buf_Index = 6;
			sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
			Uart_Pros();
			break;
		default: lock1 = 0;break;
	}
	if(lock_open_close == 1)
	{
		switch(Uart_Buf_Index)
		{
			case 1:
				lock1 = 1;
				Delay500ms();
				break;
		}
		lock_open_close = 0;
	}
}

void Timer0_Handler(void) interrupt 1
{
	if (++Key_Slow_Down == 10)
		Key_Slow_Down = 0;
}
