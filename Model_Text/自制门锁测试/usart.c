#include <usart.h>

void Uart_init(void)
{
	SCON = 0x50; //设定串口工作方式0101 0000
	PCON = 0x00;
	TMOD = 0x20;
	EA = 1;
	ES = 1;
	TL1 = 0xfd; //波特率4800
	TH1 = 0xfd;
	TR1 = 1;
}

void UART_send_byte(unsigned char dat)
{
	SBUF = dat; //把数据放到SBUF中
	while (TI == 0)
		;	//未发送完毕就等待
	TI = 0; //发送完毕后，要把TI重新置0
}

/*发送一个字符串*/
void UART_send_string(unsigned char *buf)
{
	while (*buf != '\0')
	{
		UART_send_byte(*buf++);
	}
}
