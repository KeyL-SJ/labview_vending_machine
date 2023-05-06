#include <usart.h>
#include <Timer.h>
#include <key.h>
#include <iic.h>
#include <stdio.h>

sbit led_light = P1 ^ 6;
sbit door_feedback = P1 ^ 7;

void Key_Pros(void);
void Timer_Pros(void);
void Usart_Pros(void);
void feedback_Pros(void);
void opendoor_Pros(void);
void Recognition_Pros(void);

unsigned char Key_Value, Key_Old, Key_Down;

unsigned char useTime[3] = {0, 0, 0};

unsigned char buf;
unsigned char Uart_Buf[] = " ";
unsigned char Uart_Buf_Index;

bit lock_open_close = 0;

unsigned char recognition_result = 0xff;

void Delay500ms() //@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k)
				;
		} while (--j);
	} while (--i);
}

void main(void)
{
//	speech_init(); //语音播报初始化
	usart_init();  //串口通信初始化
	Timer0Init();
	Recognition_Init();
	while (1)
	{
		Key_Pros();
		opendoor_Pros();
		feedback_Pros();
		Recognition_Pros();
	}
}

void Usart(void) interrupt 4
{
	if (RI)
	{
		RI = 0;
		buf = SBUF; //把收到的信息从SBUF放到buf中。
		ES = 0;		//暂时关闭串口中断

		switch (buf)
		{
		case 0x37:
			led_light = 0;
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

void Usart_Pros(void)
{
	UART_send_string(Uart_Buf);
}

//按键检测，按下对应按键，语音提示，并打开对应门锁
void Key_Pros(void)
{
	Key_Value = Key_Read_BTN();
	Key_Down = Key_Value & (Key_Old ^ Key_Value);
	Key_Old = Key_Value;

	switch (Key_Down)
	{
	case 1:
		//点亮指示灯
		P1 = 0xfe;
		//串口通信
		Uart_Buf_Index = 1;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//语音播报
		User_Speech_Text("您选择了一号商品");
		break;
	case 2:
		//点亮指示灯
		P1 = 0xfd;
		//串口通信
		Uart_Buf_Index = 2;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//语音播报
		User_Speech_Text("您选择了二号商品");
		break;
	case 3:
		//点亮指示灯
		P1 = 0xfb;
		//串口通信
		Uart_Buf_Index = 3;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//语音播报
		User_Speech_Text("您选择了叁号商品");
		break;
	case 4:
		//点亮指示灯
		P1 = 0xf7;
		//串口通信
		Uart_Buf_Index = 4;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//语音播报
		User_Speech_Text("您选择了四号商品");
		break;
	case 5:
		//点亮指示灯
		P1 = 0xef;
		//串口通信
		Uart_Buf_Index = 5;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//语音播报
		User_Speech_Text("您选择了五号商品");
		break;
	case 6:
		//点亮指示灯
		P1 = 0xdf;
		//串口通信
		Uart_Buf_Index = 6;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//语音播报
		User_Speech_Text("您选择了六号商品");
		break;
	default:
		lock1 = lock2 = lock3 = lock4 = lock5 = lock6 = 0;
	}
}
void opendoor_Pros(void)
{
	if (lock_open_close == 1)
	{
		switch (Uart_Buf_Index)
		{
		case 1:
			//打开门锁
			lock1 = 1;
			while (!door_feedback)
				;
			//语音播报
			User_Speech_Text("一号门锁已打开，请取走商品");
			Delay500ms();
			feedback_Pros();
			break;
		case 2:
			//打开门锁
			lock2 = 1;
			while (!door_feedback)
				;
			//语音播报
			User_Speech_Text("二号门锁已打开，请取走商品");
			Delay500ms();
			feedback_Pros();
			break;
		case 3:
			//打开门锁
			lock3 = 1;
			while (!door_feedback)
				;
			//语音播报
			User_Speech_Text("叁号门锁已打开，请取走商品");
			feedback_Pros();
			break;
		case 4:
			//打开门锁
			lock4 = 1;
			while (!door_feedback)
				;
			//语音播报
			User_Speech_Text("四号门锁已打开，请取走商品");
			Delay500ms();
			feedback_Pros();
			break;
		case 5:
			//打开门锁
			lock5 = 1;
			while (!door_feedback)
				;
			//语音播报
			User_Speech_Text("五号门锁已打开，请取走商品");
			Delay500ms();
			feedback_Pros();
			break;
		case 6:
			//打开门锁
			lock6 = 1;
			while (!door_feedback)
				;
			//语音播报
			User_Speech_Text("六号门锁已打开，请取走商品");
			Delay500ms();
			feedback_Pros();
			break;
		}
		lock_open_close = 0;
	}
}

void feedback_Pros(void)
{
	if (door_feedback == 1)
	{
		switch (Uart_Buf_Index)
		{
		case 1:
			User_Speech_Text("一号门未关闭");
			break;
		case 2:
			User_Speech_Text("二号门未关闭");
			break;
		case 3:
			User_Speech_Text("三号门未关闭");
			break;
		case 4:
			User_Speech_Text("四号门未关闭");
			break;
		case 5:
			User_Speech_Text("五号门未关闭");
			break;
		case 6:
			User_Speech_Text("六号门未关闭");
			break;
		default:
			break;
		}
		Delay500ms();
	}
	else
		P1 = 0xff;
}

void Recognition_Pros(void)
{
	recognition_result = I2C_BufferRead(ASR_RESULT);
	switch (recognition_result)
	{
	case 0: //小亚
		User_Speech_Text("有什么可以帮您");
		break;
	case 1: //一号门
		P1 = 0xfe;
		//串口通信
		Uart_Buf_Index = 1;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//语音播报
		User_Speech_Text("您选择了一号商品");
		break;
	case 2:
		P1 = 0xfd;
		//串口通信
		Uart_Buf_Index = 2;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//语音播报
		User_Speech_Text("您选择了二号商品");
		break;
	case 3:
		P1 = 0xfb;
		//串口通信
		Uart_Buf_Index = 3;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//语音播报
		User_Speech_Text("您选择了叁号商品");
		break;
	case 4:
		P1 = 0xf7;
		//串口通信
		Uart_Buf_Index = 4;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//语音播报
		User_Speech_Text("您选择了四号商品");
		break;
	case 5:
		P1 = 0xef;
		//串口通信
		Uart_Buf_Index = 5;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//语音播报
		User_Speech_Text("您选择了五号商品");
		break;
	case 6:
		P1 = 0xdf;
		//串口通信
		Uart_Buf_Index = 6;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//语音播报
		User_Speech_Text("您选择了六号商品");
		break;
	}
}

//早上7点灭灯，晚上18点开灯
void Timer_Pros(void)
{
	if (useTime[0] == 7 && useTime[1] == 0 && useTime[2] == 0)
	{
		led_light = 0; //灭灯
	}
	if (useTime[0] == 18 && useTime[1] == 0 && useTime[2] == 0)
	{
		led_light = 1; //开灯
	}
}
