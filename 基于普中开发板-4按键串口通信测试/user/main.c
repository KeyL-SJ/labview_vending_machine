#include <reg52.h>
#include <Uart.h>
#include <key.h>
#include <iic.h>
#include <Timer.h>

void Key_Pros(void);
void Uart_Pros(void);
unsigned int Key_Slow_Down;

unsigned char Key_Value,Key_Down,Key_Old;

unsigned char buf;
unsigned char Uart_Buf[] = "hello world\n";
unsigned char Uart_Buf_Index;
unsigned char seg_string[];

void n_delay(unsigned int n)
{
	while (n--);
}

void main(void)
{
	Uart_init();
	Timer0Init();
	while (1)
	{
		Key_Pros();
	}
}

//串行中断服务函数

void Uart() interrupt 4
{
	if(RI)
	{
		RI = 0;
		buf = SBUF; //把收到的信息从SBUF放到buf中。
		ES = 0; //暂时关闭串口中断

		switch (buf)
		{
		case 0x31:
			P2 = 0xfe;
			break; //二进制 0011 0001  十进制 49 控制字符 1  16进制 0X31
		case 0x32:
			P2 = 0xfd;
			break; // 1111 1101
		case 0x33:
			P2 = 0xfb;
			break;
		case 0x34:
			P2 = 0xf7;
			break;
		case 0x35:
			P2 = 0xef;
			break;
		case 0x36:
			P2 = 0xdf;
			break;
		}
		ES = 1; //重新开启串口中断
		SBUF = buf;
		while (!TI)
			;
		TI = 0;
	}
}


void Key_Pros(void)
{
	if(Key_Slow_Down) return;
	Key_Slow_Down = 1;
	
	Key_Value = Key_Read_BTN();
	Key_Down = Key_Value & (Key_Old ^ Key_Value);
	Key_Old = Key_Value;
	sprintf(Uart_Buf,"%d",(unsigned int)Uart_Buf_Index);
	switch (Key_Value)
	{
	case 1:
		P2 = 0xfe;
		Uart_Buf_Index = 1;
		Uart_Pros();
		break;
	case 2:
		P2 = 0xfd;
		Uart_Buf_Index = 2;
		Uart_Pros();
		break;
	case 3:
		P2 = 0xfb;
		Uart_Buf_Index = 3;
		Uart_Pros();
		break;
	case 4:
		P2 = 0xf7;
		Uart_Buf_Index = 4;
		Uart_Pros();
		break;
	}
}

void Uart_Pros()
{
	UART_send_string(Uart_Buf);
}

void Timer0_Handler(void) interrupt 1
{
	if(++Key_Slow_Down == 10) Key_Slow_Down = 0;
}