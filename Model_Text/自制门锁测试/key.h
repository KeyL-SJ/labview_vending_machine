#include <reg52.h>

sbit k1 = P0^0;
sbit k2 = P0^1;
sbit k3 = P0^2;
sbit k4 = P0^3;
sbit k5 = P0^4;
sbit k6 = P0^5;

//sbit k1 = P3^1;
//sbit k2 = P3^0;
//sbit k3 = P3^2;
//sbit k4 = P3^3;

unsigned char Key_Read_BTN(void);