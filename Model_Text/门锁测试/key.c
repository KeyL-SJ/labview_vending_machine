#include <key.h>

unsigned char Key_Read_BTN(void)
{
	unsigned char Key_Value;
	if(key1 == 0) Key_Value = 1;
	else if(key2 == 0) Key_Value = 2;
	else if(key3 == 0) Key_Value = 3;
	else if(key4 == 0) Key_Value = 4;
	else Key_Value = 0;
	
	return Key_Value;  //·µ»ØKeyValue
}
