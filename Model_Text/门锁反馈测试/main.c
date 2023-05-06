#include <iic.h>
#include <key.h>
sbit door_feedback = P1^7;

void Key_Pros(void);
void opendoor_Pros(void);
void feedback_Pros(void);

unsigned char Key_Value, Key_Old, Key_Down;

void main(void)
{
	while(1)
	{
		Key_Pros();
		opendoor_Pros();
		feedback_Pros();
	}
}

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
		//��������
		User_Speech_Text("��ѡ����һ����Ʒ");
		break;
	case 2:
		//����ָʾ��
		P1 = 0xfd;
		//��������
		User_Speech_Text("��ѡ���˶�����Ʒ");
		break;
	case 3:
		//����ָʾ��
		P1 = 0xfb;
		//��������
		User_Speech_Text("��ѡ����������Ʒ");
		break;
	case 4:
		//����ָʾ��
		P1 = 0xf7;
		//��������
		User_Speech_Text("��ѡ�����ĺ���Ʒ");
		break;
	case 5:
		//����ָʾ��
		P1 = 0xef;
		//��������
		User_Speech_Text("��ѡ���������Ʒ");
		break;
	case 6:
		//����ָʾ��
		P1 = 0xdf;
		//��������
		User_Speech_Text("��ѡ����������Ʒ");
		break;
	default:
		lock1 = lock2 = lock3 = lock4 = lock5 = lock6 = 0;
	}
}

void opendoor_Pros(void)
{
		switch (Key_Down)
		{
		case 1:
			//������
			lock1 = 1;
			Delay500ms();
			//��������
			User_Speech_Text("һ�������Ѵ򿪣���ȡ����Ʒ");
			door_feedback = 1;
			break;
		case 2:
			//������
			lock2 = 1;
			Delay500ms();
			//��������
			User_Speech_Text("���������Ѵ򿪣���ȡ����Ʒ");
		feedback_Pros();
			break;
		case 3:
			//������
			lock3 = 1;
			Delay500ms();
			//��������
			User_Speech_Text("���������Ѵ򿪣���ȡ����Ʒ");
			break;
		case 4:
			//������
			lock4 = 1;
			Delay500ms();
			//��������
			User_Speech_Text("�ĺ������Ѵ򿪣���ȡ����Ʒ");
			break;
		case 5:
			//������
			lock5 = 1;
			Delay500ms();
			//��������
			User_Speech_Text("��������Ѵ򿪣���ȡ����Ʒ");
			break;
		case 6:
			//������
			lock6 = 1;
			Delay500ms();
			//��������
			User_Speech_Text("���������Ѵ򿪣���ȡ����Ʒ");
			break;
		}
}

void feedback_Pros(void)
{
	if(door_feedback == 1)
	{
		// switch (Uart_Buf_Index)
		// {
		// case 1:
		// 	User_Speech_Text("һ����δ�ر�");
		// 	break;
		// case 2:
		// 	User_Speech_Text("������δ�ر�");
		// 	break;
		// case 3:
		// 	User_Speech_Text("������δ�ر�");
		// 	break;
		// case 4:
		// 	User_Speech_Text("�ĺ���δ�ر�");
		// 	break;
		// case 5:
		// 	User_Speech_Text("�����δ�ر�");
		// 	break;
		// case 6:
		// 	User_Speech_Text("������δ�ر�");
		// 	break;
		// default:
		// 	break;
		// }
		User_Speech_Text("ȡ����Ʒ����غ�����");
		Delay500ms();
	}
	else P1 = 0xff;
}


