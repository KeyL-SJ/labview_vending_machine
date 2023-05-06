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
		//点亮指示灯
		P1 = 0xfe;
		//语音播报
		User_Speech_Text("您选择了一号商品");
		break;
	case 2:
		//点亮指示灯
		P1 = 0xfd;
		//语音播报
		User_Speech_Text("您选择了二号商品");
		break;
	case 3:
		//点亮指示灯
		P1 = 0xfb;
		//语音播报
		User_Speech_Text("您选择了叁号商品");
		break;
	case 4:
		//点亮指示灯
		P1 = 0xf7;
		//语音播报
		User_Speech_Text("您选择了四号商品");
		break;
	case 5:
		//点亮指示灯
		P1 = 0xef;
		//语音播报
		User_Speech_Text("您选择了五号商品");
		break;
	case 6:
		//点亮指示灯
		P1 = 0xdf;
		//语音播报
		User_Speech_Text("您选择了六号商品");
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
			//打开门锁
			lock1 = 1;
			Delay500ms();
			//语音播报
			User_Speech_Text("一号门锁已打开，请取走商品");
			door_feedback = 1;
			break;
		case 2:
			//打开门锁
			lock2 = 1;
			Delay500ms();
			//语音播报
			User_Speech_Text("二号门锁已打开，请取走商品");
		feedback_Pros();
			break;
		case 3:
			//打开门锁
			lock3 = 1;
			Delay500ms();
			//语音播报
			User_Speech_Text("叁号门锁已打开，请取走商品");
			break;
		case 4:
			//打开门锁
			lock4 = 1;
			Delay500ms();
			//语音播报
			User_Speech_Text("四号门锁已打开，请取走商品");
			break;
		case 5:
			//打开门锁
			lock5 = 1;
			Delay500ms();
			//语音播报
			User_Speech_Text("五号门锁已打开，请取走商品");
			break;
		case 6:
			//打开门锁
			lock6 = 1;
			Delay500ms();
			//语音播报
			User_Speech_Text("六号门锁已打开，请取走商品");
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
		// 	User_Speech_Text("一号门未关闭");
		// 	break;
		// case 2:
		// 	User_Speech_Text("二号门未关闭");
		// 	break;
		// case 3:
		// 	User_Speech_Text("三号门未关闭");
		// 	break;
		// case 4:
		// 	User_Speech_Text("四号门未关闭");
		// 	break;
		// case 5:
		// 	User_Speech_Text("五号门未关闭");
		// 	break;
		// case 6:
		// 	User_Speech_Text("六号门未关闭");
		// 	break;
		// default:
		// 	break;
		// }
		User_Speech_Text("取走商品后请关好门锁");
		Delay500ms();
	}
	else P1 = 0xff;
}


