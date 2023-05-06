#include <iic.h>

unsigned char result = 0xff;

void main()
{
	Recognition_Init();
	while (1)
	{
		result = I2C_BufferRead(ASR_RESULT);
		if (result == 1)
		{
			led1 = 0;
		}
		else if (result == 2)
		{
			led2 = 0;
		}
		else if (result == 3)
		{
			led3 = 0;
		}
		else if (result == 4)
		{
			led4 = 0;
		}
		else if (result == 5)
		{
			led5 = 0;
		}
		else if (result == 9)
		{
			led1 = 1;
		}
		delay(500);
	}
}
