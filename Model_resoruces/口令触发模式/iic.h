#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include <string.h>

#define I2C_ADDR_Recognition 0x1e //����ʶ��ģ���ַ��ģ���ַΪ0x0f�������Ҷ�Ϊ��дλ��������Ҫ������ΪΪ0x1e

#define ASR_ADD_WORD_ADDR 0x01 //������ӵ�ַ

#define ASR_MODE_ADDR 0x02 //ʶ��ģʽ���õ�ַ��ֵΪ0-2��0:ѭ��ʶ��ģʽ 1:����ģʽ ,2:����ģʽ��Ĭ��Ϊѭ�����

#define ASR_RGB_ADDR 0x03 // RGB�����õ�ַ,��Ҫ����λ����һ��ֱ��Ϊ�ƺ�1���� 2:�� 3���� ,
                          //�ڶ����ֽ�Ϊ����0-255����ֵԽ������Խ��

#define ASR_REC_GAIN 0x04 //ʶ�����������õ�ַ�������ȿ�����Ϊ0x00-0x7f,ֵԽ��Խ���׼�⵫��Խ�������У�
                          //��������ֵΪ0x40-0x55,Ĭ��ֵΪ0x40

#define ASR_CLEAR_ADDR 0x05 //������绺�������ַ��¼����Ϣǰ��Ҫ����»�������Ϣ

#define ASR_KEY_FLAG 0x06 //���ڰ���ģʽ�£���������ʶ��ģʽ

#define ASR_VOICE_FLAG 0x07 //���������Ƿ���ʶ������ʾ��

#define ASR_RESULT 0x08 //ʶ������ŵ�ַ

#define ASR_BUZZER 0x09 //����������д1������д0�ر�

#define ASR_NUM_CLECK 0x0a //¼�������ĿУ��

#define FIRMWARE_VERSION 0x0b //��ȡ�̼��汾

#define ASR_BUSY 0x0c //æ�б�־

sbit scl = P2 ^ 1; // I2C  ʱ��
sbit sda = P2 ^ 0; // I2C  ����

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
