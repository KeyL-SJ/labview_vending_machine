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
//	speech_init(); //����������ʼ��
	usart_init();  //����ͨ�ų�ʼ��
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
		buf = SBUF; //���յ�����Ϣ��SBUF�ŵ�buf�С�
		ES = 0;		//��ʱ�رմ����ж�

		switch (buf)
		{
		case 0x37:
			led_light = 0;
			lock_open_close = 1;
			break;
		}
		ES = 1; //���¿��������ж�
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

//������⣬���¶�Ӧ������������ʾ�����򿪶�Ӧ����
void Key_Pros(void)
{
	Key_Value = Key_Read_BTN();
	Key_Down = Key_Value & (Key_Old ^ Key_Value);
	Key_Old = Key_Value;

	switch (Key_Down)
	{
	case 1:
		//����ָʾ��
		P1 = 0xfe;
		//����ͨ��
		Uart_Buf_Index = 1;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//��������
		User_Speech_Text("��ѡ����һ����Ʒ");
		break;
	case 2:
		//����ָʾ��
		P1 = 0xfd;
		//����ͨ��
		Uart_Buf_Index = 2;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//��������
		User_Speech_Text("��ѡ���˶�����Ʒ");
		break;
	case 3:
		//����ָʾ��
		P1 = 0xfb;
		//����ͨ��
		Uart_Buf_Index = 3;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//��������
		User_Speech_Text("��ѡ����������Ʒ");
		break;
	case 4:
		//����ָʾ��
		P1 = 0xf7;
		//����ͨ��
		Uart_Buf_Index = 4;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//��������
		User_Speech_Text("��ѡ�����ĺ���Ʒ");
		break;
	case 5:
		//����ָʾ��
		P1 = 0xef;
		//����ͨ��
		Uart_Buf_Index = 5;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//��������
		User_Speech_Text("��ѡ���������Ʒ");
		break;
	case 6:
		//����ָʾ��
		P1 = 0xdf;
		//����ͨ��
		Uart_Buf_Index = 6;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//��������
		User_Speech_Text("��ѡ����������Ʒ");
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
			//������
			lock1 = 1;
			while (!door_feedback)
				;
			//��������
			User_Speech_Text("һ�������Ѵ򿪣���ȡ����Ʒ");
			Delay500ms();
			feedback_Pros();
			break;
		case 2:
			//������
			lock2 = 1;
			while (!door_feedback)
				;
			//��������
			User_Speech_Text("���������Ѵ򿪣���ȡ����Ʒ");
			Delay500ms();
			feedback_Pros();
			break;
		case 3:
			//������
			lock3 = 1;
			while (!door_feedback)
				;
			//��������
			User_Speech_Text("���������Ѵ򿪣���ȡ����Ʒ");
			feedback_Pros();
			break;
		case 4:
			//������
			lock4 = 1;
			while (!door_feedback)
				;
			//��������
			User_Speech_Text("�ĺ������Ѵ򿪣���ȡ����Ʒ");
			Delay500ms();
			feedback_Pros();
			break;
		case 5:
			//������
			lock5 = 1;
			while (!door_feedback)
				;
			//��������
			User_Speech_Text("��������Ѵ򿪣���ȡ����Ʒ");
			Delay500ms();
			feedback_Pros();
			break;
		case 6:
			//������
			lock6 = 1;
			while (!door_feedback)
				;
			//��������
			User_Speech_Text("���������Ѵ򿪣���ȡ����Ʒ");
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
			User_Speech_Text("һ����δ�ر�");
			break;
		case 2:
			User_Speech_Text("������δ�ر�");
			break;
		case 3:
			User_Speech_Text("������δ�ر�");
			break;
		case 4:
			User_Speech_Text("�ĺ���δ�ر�");
			break;
		case 5:
			User_Speech_Text("�����δ�ر�");
			break;
		case 6:
			User_Speech_Text("������δ�ر�");
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
	case 0: //С��
		User_Speech_Text("��ʲô���԰���");
		break;
	case 1: //һ����
		P1 = 0xfe;
		//����ͨ��
		Uart_Buf_Index = 1;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//��������
		User_Speech_Text("��ѡ����һ����Ʒ");
		break;
	case 2:
		P1 = 0xfd;
		//����ͨ��
		Uart_Buf_Index = 2;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//��������
		User_Speech_Text("��ѡ���˶�����Ʒ");
		break;
	case 3:
		P1 = 0xfb;
		//����ͨ��
		Uart_Buf_Index = 3;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//��������
		User_Speech_Text("��ѡ����������Ʒ");
		break;
	case 4:
		P1 = 0xf7;
		//����ͨ��
		Uart_Buf_Index = 4;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//��������
		User_Speech_Text("��ѡ�����ĺ���Ʒ");
		break;
	case 5:
		P1 = 0xef;
		//����ͨ��
		Uart_Buf_Index = 5;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//��������
		User_Speech_Text("��ѡ���������Ʒ");
		break;
	case 6:
		P1 = 0xdf;
		//����ͨ��
		Uart_Buf_Index = 6;
		sprintf(Uart_Buf, "%d", (unsigned int)Uart_Buf_Index);
		Usart_Pros();
		//��������
		User_Speech_Text("��ѡ����������Ʒ");
		break;
	}
}

//����7����ƣ�����18�㿪��
void Timer_Pros(void)
{
	if (useTime[0] == 7 && useTime[1] == 0 && useTime[2] == 0)
	{
		led_light = 0; //���
	}
	if (useTime[0] == 18 && useTime[1] == 0 && useTime[2] == 0)
	{
		led_light = 1; //����
	}
}
