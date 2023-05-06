#include <reg51.h>
#include <stdio.h>
typedef   unsigned char  uint8;
typedef   unsigned int   uint16;
 
uint8 Buf[] = "hello world\n";
 
void delay(uint16 n)
{
	while (n--);
}
 
/*������Ϊ9600*/
void UART_init(void)
{
    SCON = 0x50;        //���ڷ�ʽ1
 
    TMOD = 0x20;        // ��ʱ��ʹ�÷�ʽ2�Զ�����
    TH1 = 0xFD;    //9600�����ʶ�Ӧ��Ԥ��������ʱ����ʽ2�£�TH1=TL1
    TL1 = 0xFD;
 
    TR1 = 1;//������ʱ������ʼ����������
}
 
/*����һ���ַ�*/
void UART_send_byte(uint8 dat)
{
	SBUF = dat;       //�����ݷŵ�SBUF��
	while (TI == 0);//δ������Ͼ͵ȴ�
	TI = 0;    //������Ϻ�Ҫ��TI������0
}
 
/*����һ���ַ���*/
void UART_send_string(uint8 *buf)
{
	while (*buf != '\0')
	{
		UART_send_byte(*buf++);
	}
}
 
main()
{
	UART_init();
	
	while (1)
	{
		UART_send_string(Buf);
		delay(20000);
	}
 
}