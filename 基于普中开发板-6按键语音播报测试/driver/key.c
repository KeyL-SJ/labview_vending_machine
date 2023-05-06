#include <key.h>

#define GPIO_DIG P0
#define GPIO_KEY P1

/*******************************************************************************
* 函 数 名         : Key_Read_KBD
* 函数功能		   : 检测矩阵按键按下情况
* 输    入         : 无
* 输    出         : 按下的按键的键值
*******************************************************************************/
unsigned char Key_Read_KBD(void)
{
	unsigned char Key_Value = 1;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//有按键按下
	{
		GPIO_KEY=0X0F;
		switch(GPIO_KEY)
		{
			case(0X07):	Key_Value=1;break;
			case(0X0b):	Key_Value=2;break;
			case(0X0d): Key_Value=3;break;
			case(0X0e):	Key_Value=4;break;
		}
		GPIO_KEY=0XF0;
		switch(GPIO_KEY)
		{
			case(0X70):	Key_Value=Key_Value;break;
			case(0Xb0):	Key_Value=Key_Value+4;break;
			case(0Xd0): Key_Value=Key_Value+8;break;
			case(0Xe0):	Key_Value=Key_Value+12;break;
		}
		while((GPIO_KEY!=0xf0)&&(GPIO_KEY != 0X0F));
	}
	else
	{
		Key_Value=0xff;  //无按键按下
	}
	return Key_Value;  //返回KeyValue
}