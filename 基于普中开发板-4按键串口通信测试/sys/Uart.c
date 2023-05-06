#include <Uart.h>

void Uart_init(void)
{
	SCON=0x50;//�趨���ڹ�����ʽ0101 0000
	PCON=0x00;
	TMOD=0x20; 
	EA=1;
	ES=1;
	TL1=0xfd;//������4800
	TH1=0xfd;
	TR1=1;
}

//void Uart_Send_Byte(unsigned char Byte)
//{
//	SBUF = Byte;       //�����ݷŵ�SBUF��
//	while (TI == 0);//δ������Ͼ͵ȴ�
//	TI = 0;    //������Ϻ�Ҫ��TI������0
//}

//void Uart_Send_String(unsigned char *Uart_String)
//{
//	while(*Uart_String != '\0')
//	{
//		Uart_Send_Byte(*Uart_String++);
//	}
//}

void UART_send_byte(unsigned char dat)
{
	SBUF = dat;       //�����ݷŵ�SBUF��
	while (TI == 0);//δ������Ͼ͵ȴ�
	TI = 0;    //������Ϻ�Ҫ��TI������0
}
 
/*����һ���ַ���*/
void UART_send_string(unsigned char *buf)
{
	while (*buf != '\0')
	{
		UART_send_byte(*buf++);
	}
}
