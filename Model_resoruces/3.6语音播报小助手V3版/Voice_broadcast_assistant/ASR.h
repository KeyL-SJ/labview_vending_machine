#ifndef ASR_H
#define ASR_H

#include "Arduino.h"
#include <Wire.h>
#define ASR_I2C_ADDR                    0x0f   //语音识别模块地址

#define ASR_ADD_WORD_ADDR           0x01   //词条添加地址

#define ASR_MODE_ADDR               0x02   //识别模式设置地址，值为0-2，0:循环识别模式 1:口令模式 ,2:按键模式，默认为循环检测

#define ASR_RGB_ADDR                0x03   //RGB灯设置地址,需要发两位，第一个直接为灯号1：蓝 2:红 3：绿 ,
                                           //第二个字节为亮度0-255，数值越大亮度越高
                                           
#define ASR_REC_GAIN                0x04   //识别灵敏度设置地址，灵敏度可设置为0x00-0x7f，值越高越容易检测但是越容易误判，
                                           //建议设置值为0x40-0x55,默认值为0x40
                                           
#define ASR_CLEAR_ADDR              0x05   //清除掉电缓存操作地址，录入信息前均要清除下缓存区信息


#define ASR_KEY_FLAG                0x06   //用于按键模式下，设置启动识别模式

#define ASR_VOICE_FLAG              0x07   //用于设置是否开启识别结果提示音

#define ASR_RESULT                  0x08  //识别结果存放地址

#define ASR_BUZZER                  0x09 //蜂鸣器控制写1开启，写0关闭

#define ASR_NUM_CLECK               0x0a //录入词条数目校验

#define FIRMWARE_VERSION            0x0b //读取固件版本

#define ASR_BUSY                    0x0c//忙闲标志

bool I2CWrite(unsigned char reg_addr,unsigned char date);
bool WireReadData(unsigned char reg_addr,unsigned char *value,int num);
bool RGB_Set(unsigned char R,unsigned char G,unsigned char B);
void AsrAddWords(unsigned char idNum,unsigned char * words);
void BusyWait(void);

#endif
