#include <reg52.h>
//����������Ӧ���п������ϵ�Led������ = ��Ӧ��Led����
sbit door1 = P2^0;
sbit door2 = P2^1;
sbit door3 = P2^2;
sbit door4 = P2^3;
sbit door5 = P2^4;
sbit door6 = P2^5;

//��������

//������̰������
unsigned char Key_Read_KBD(void);
