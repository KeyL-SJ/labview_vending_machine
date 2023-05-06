#include <reg52.h>
//这里门锁对应普中开发板上的Led，开门 = 对应的Led点亮
sbit door1 = P2^0;
sbit door2 = P2^1;
sbit door3 = P2^2;
sbit door4 = P2^3;
sbit door5 = P2^4;
sbit door6 = P2^5;

//门锁反馈

//矩阵键盘按键检测
unsigned char Key_Read_KBD(void);
