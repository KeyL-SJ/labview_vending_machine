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
		case 0://小亚
			User_Speech_Text("有什么可以帮您");
			break;
		case 1://一号门
			User_Speech_Text("您选择了一号商品");
			break;
		case 2:
			User_Speech_Text("您选择了二号商品");
			break;
		case 3:
			User_Speech_Text("您选择了叁号商品");
			break;
		case 4:
			User_Speech_Text("您选择了四号商品");
			break;
		case 5:
			User_Speech_Text("您选择了五号商品");
			break;
		case 6:
			User_Speech_Text("您选择了六号商品");
			break;
	}
	delay(500);
}
