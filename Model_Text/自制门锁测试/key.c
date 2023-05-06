#include <key.h>

unsigned char Key_Read_BTN(void)
{
	unsigned char Key_Value;
	if(k1 == 0) Key_Value = 1;
	else if(k2 == 0) Key_Value = 2;
	else if(k3 == 0) Key_Value = 3;
	else if(k4 == 0) Key_Value = 4;
	else if(k5 == 0) Key_Value = 5;
	else if(k6 == 0) Key_Value = 6;
	
	else Key_Value = 0;
	
	return Key_Value;
}
