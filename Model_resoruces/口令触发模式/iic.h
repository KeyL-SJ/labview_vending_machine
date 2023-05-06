#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include <string.h>

#define I2C_ADDR_Recognition 0x1e //语音识别模块地址，模块地址为0x0f由于最右端为读写位，所以需要左移以为为0x1e

#define ASR_ADD_WORD_ADDR 0x01 //词条添加地址

#define ASR_MODE_ADDR 0x02 //识别模式设置地址，值为0-2，0:循环识别模式 1:口令模式 ,2:按键模式，默认为循环检测

#define ASR_RGB_ADDR 0x03 // RGB灯设置地址,需要发两位，第一个直接为灯号1：蓝 2:红 3：绿 ,
                          //第二个字节为亮度0-255，数值越大亮度越高

#define ASR_REC_GAIN 0x04 //识别灵敏度设置地址，灵敏度可设置为0x00-0x7f,值越高越容易检测但是越容易误判，
                          //建议设置值为0x40-0x55,默认值为0x40

#define ASR_CLEAR_ADDR 0x05 //清除掉电缓存操作地址，录入信息前均要清除下缓存区信息

#define ASR_KEY_FLAG 0x06 //用于按键模式下，设置启动识别模式

#define ASR_VOICE_FLAG 0x07 //用于设置是否开启识别结果提示音

#define ASR_RESULT 0x08 //识别结果存放地址

#define ASR_BUZZER 0x09 //蜂鸣器控制写1开启，写0关闭

#define ASR_NUM_CLECK 0x0a //录入词条数目校验

#define FIRMWARE_VERSION 0x0b //读取固件版本

#define ASR_BUSY 0x0c //忙闲标志

sbit scl = P2 ^ 1; // I2C  时钟
sbit sda = P2 ^ 0; // I2C  数据

sbit led1 = P2 ^ 4;
sbit led2 = P2 ^ 5;
sbit led3 = P2 ^ 6;
sbit led4 = P2 ^ 7;
sbit led5 = P2 ^ 3;

sbit anjian1 = P3 ^ 1;
sbit anjian2 = P3 ^ 0;

void delay(int i);
void Start_I2c();
void Stop_I2c();
void I2C_SendByte(unsigned char c);
unsigned char I2C_RcvByte();
void Ack_I2c(bit a);
bit I2C_ByteWrite_alone(unsigned char date);
void I2C_ByteWrite(unsigned char reg_addr, unsigned char dat);
unsigned char I2C_BufferRead(unsigned char date);
void AsrAddWords(unsigned char idNum, unsigned char *words);
void RGB_Set(unsigned char R, unsigned char G, unsigned char B);
void BusyWait(void);

void Recognition_Init(void);
