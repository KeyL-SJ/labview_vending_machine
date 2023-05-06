#include <key.h>
#define GPIO_DIG P0
#define GPIO_KEY P1


void key_delay(unsigned int i)
{
	while(i--);	
}

/*******************************************************************************
* �� �� ��         : Key_Read_KBD
* ��������		   : �����󰴼��������
* ��    ��         : ��
* ��    ��         : ���µİ����ļ�ֵ
*******************************************************************************/
unsigned char Key_Read_KBD(void)
{
	unsigned char Key_Value;
	char a=0;
	GPIO_KEY=0x0f;
		if(GPIO_KEY!=0x0f)//�ٴμ������Ƿ���
		{	
			//������
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	Key_Value=1;break;
				case(0X0b):	Key_Value=2;break;
				case(0X0d): Key_Value=3;break;
				case(0X0e):	Key_Value=4;break;
			}
			//������
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	Key_Value=Key_Value;break;
				case(0Xb0):	Key_Value=Key_Value+4;break;
				case(0Xd0): Key_Value=Key_Value+8;break;
				case(0Xe0):	Key_Value=Key_Value+12;break;
			}
	}

	return Key_Value;
}

unsigned char Key_Read_BTN(void)
{
	unsigned char Key_Value;
	if(Key1 == 0) Key_Value = 1;
	else if(Key2 == 0) Key_Value = 2;
	else if(Key3 == 0) Key_Value = 3;
	else if(Key4 == 0) Key_Value = 4;
	else Key_Value = 0;
	
	return Key_Value;
}