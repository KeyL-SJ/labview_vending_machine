#include <reg52.h>
#include <Uart.h>
#include <key.h>
#include <iic.h>
sbit led3 = P2^2;
sbit led4 = P2^3;
sbit led5 = P2^4;
sbit led6 = P2^5;
void Recognition_Pros(void);

unsigned char recognition_result = 0xff;


void main(void)
{
	speech_init();
	Recognition_Init();
	
	while (1)
	{
		Recognition_Pros();
	}
}

void Recognition_Pros(void)
{
	recognition_result = I2C_BufferRead(ASR_RESULT);
	switch(recognition_result)
	{
		case 0://С��
			User_Speech_Text("��ʲô���԰���");
			break;
		case 1://һ����
			User_Speech_Text("��ѡ����һ����Ʒ");
			break;
		case 2:
			User_Speech_Text("��ѡ���˶�����Ʒ");
			break;
		case 3:
			User_Speech_Text("��ѡ����������Ʒ");
			break;
		case 4:
			User_Speech_Text("��ѡ�����ĺ���Ʒ");
			break;
		case 5:
			User_Speech_Text("��ѡ���������Ʒ");
			break;
		case 6:
			User_Speech_Text("��ѡ����������Ʒ");
			break;
	}
	delay(500);
}
