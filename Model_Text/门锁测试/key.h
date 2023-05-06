#include <reg52.h>
sbit key1 = P3^1;
sbit key2 = P3^0;
sbit key3 = P3^2;
sbit key4 = P3^3;
unsigned char Key_Read_BTN(void);