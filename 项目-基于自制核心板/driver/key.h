#include <reg52.h>

sbit k1 = P0^0;
sbit k2 = P0^1;
sbit k3 = P0^2;
sbit k4 = P0^3;
sbit k5 = P0^4;
sbit k6 = P0^5;

sbit lock1 = P2^2;
sbit lock2 = P2^3;
sbit lock3 = P2^4;
sbit lock4 = P2^5;
sbit lock5 = P2^6;
sbit lock6 = P2^7;




unsigned char Key_Read_BTN(void);
