#include <reg52.h>

sbit Key1 = P0^0;
sbit Key2 = P0^1;
sbit Key3 = P0^2;
sbit Key4 = P0^3;
sbit Key5 = P0^4;


//这里门锁对应普中开发板上的Led，开门 = 对应的Led点亮
sbit door1 = P2^0;
sbit door2 = P2^1;
sbit door3 = P2^2;
sbit door4 = P2^3;
sbit door5 = P2^4;
sbit door6 = P2^5;

//门锁反馈
sbit door1_feedback = P1^0;
sbit door2_feedback = P1^1;
sbit door3_feedback = P1^2;
sbit door4_feedback = P1^3;
sbit door5_feedback = P1^4;
sbit door6_feedback = P1^5;

//矩阵键盘按键检测
unsigned char Key_Read_KBD(void);
unsigned char Key_Read_BTN(void);
