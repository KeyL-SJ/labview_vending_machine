#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#include "i2c.h"

sbit scl = P2 ^ 1; // I2C  时钟
sbit sda = P2 ^ 0; // I2C  数据
bit ack;           /*应答标志位*/
sbit k1 = P3 ^ 1;
sbit k2 = P3 ^ 0;
sbit k3 = P3 ^ 2;
sbit k4 = P3 ^ 3;

void main()
{

  SetVolume(10);
  SetReader(Reader_XiaoPing);
  speech_text("欢迎来到桂林电子科技大学信息科技学院", GB2312);
  while (GetChipStatus() != ChipStatus_Idle) //等待芯片空闲
  {
    delay(10);
  }

  SetReader(Reader_XuDuo);
  speech_text("我尊贵的顾客请问您需要点什么呢", GB2312);
  while (GetChipStatus() != ChipStatus_Idle) //等待芯片空闲
  {
    delay(10);
  }

  while (1)
  {
    if (k1 == 0)
    {
      SetVolume(10);
      SetReader(Reader_XiaoPing);
      speech_text("一号箱门已开启请取完物品关好箱门谢谢", GB2312);
      while (GetChipStatus() != ChipStatus_Idle) //等待芯片空闲
      {
        delay(10);
      }
    }
    else if (k2 == 0)
    {
      SetVolume(10);
      SetReader(Reader_XuDuo);
      speech_text("二号箱门已开启请取完物品关好箱门谢谢", GB2312);
      while (GetChipStatus() != ChipStatus_Idle) //等待芯片空闲
      {
        delay(10);
      }
    }
  }
}

/*------------------------------------------------
                  延时函数
------------------------------------------------*/
void delay(int i)
{
  int j, k;
  for (j = i; j > 0; j--)
    for (k = 150; k > 0; k--)
      ;
}

/*******************************************************************
                     起动总线函数
函数原型: void  Start_I2c();
功能:     启动I2C总线,即发送I2C起始条件.
********************************************************************/
void Start_I2c()
{
  sda = 1; /*发送起始条件的数据信号*/
  _nop_();
  scl = 1;
  _nop_(); /*起始条件建立时间大于4.7us,延时*/
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  sda = 0; /*发送起始信号*/
  _nop_(); /* 起始条件锁定时间大于4μs*/
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  scl = 0; /*钳住I2C总线，准备发送或接收数据 */
  _nop_();
  _nop_();
}

/*******************************************************************
                      结束总线函数
函数原型: void  Stop_I2c();
功能:     结束I2C总线,即发送I2C结束条件.
********************************************************************/
void Stop_I2c()
{
  sda = 0; /*发送结束条件的数据信号*/
  _nop_(); /*发送结束条件的时钟信号*/
  scl = 1; /*结束条件建立时间大于4μs*/
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  sda = 1; /*发送I2C总线结束信号*/
  _nop_();
  _nop_();
  _nop_();
  _nop_();
}

/*******************************************************************
                 字节数据发送函数
函数原型: void  I2C_SendByte(UCHAR c);
功能:     将数据c发送出去,可以是地址,也可以是数据,发完后等待应答,并对
          此状态位进行操作.(不应答或非应答都使ack=0)
           发送数据正常，ack=1; ack=0表示被控器无应答或损坏。
********************************************************************/
void I2C_SendByte(unsigned char c)
{
  unsigned char i;

  for (i = 0; i < 8; i++) /*要传送的数据长度为8位*/
  {
    if ((c << i) & 0x80)
      sda = 1; /*判断发送位*/
    else
      sda = 0;
    _nop_();
    scl = 1; /*置时钟线为高，通知被控器开始接收数据位*/
    _nop_();
    _nop_(); /*保证时钟高电平周期大于4μs*/
    _nop_();
    _nop_();
    _nop_();
    scl = 0;
  }
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  sda = 1; /*8位发送完后释放数据线，准备接收应答位*/
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  scl = 1;
  _nop_();
  _nop_();
  _nop_();
  if (sda == 1)
    ack = 0;
  else
    ack = 1; /*判断是否接收到应答信号*/
  scl = 0;
  _nop_();
  _nop_();
}

/*******************************************************************
                 字节数据接收函数
函数原型: UCHAR  I2C_RcvByte();
功能:        用来接收从器件传来的数据,并判断总线错误(不发应答信号)，
          发完后请用应答函数应答从机。
********************************************************************/
unsigned char I2C_RcvByte()
{
  unsigned char retc = 0, i = 0;
  sda = 1; /*置数据线为输入方式*/
  for (i = 0; i < 8; i++)
  {
    _nop_();
    scl = 0; /*置时钟线为低，准备接收数据位*/
    _nop_();
    _nop_(); /*时钟低电平周期大于4.7μs*/
    _nop_();
    _nop_();
    _nop_();
    scl = 1; /*置时钟线为高使数据线上数据有效*/
    _nop_();
    _nop_();
    retc = retc << 1;
    if (sda == 1)
      retc = retc + 1; /*读数据位,接收的数据位放入retc中 */
    _nop_();
    _nop_();
  }
  scl = 0;
  _nop_();
  _nop_();
  return (retc);
}

/********************************************************************
                     应答子函数
函数原型:  void Ack_I2c(bit a);
功能:      主控器进行应答信号(可以是应答或非应答信号，由位参数a决定)
********************************************************************/
void Ack_I2c(bit a)
{
  if (a == 0)
    sda = 0; /*在此发出应答或非应答信号 */
  else
    sda = 1; /*0为发出应答，1为非应答信号 */
  _nop_();
  _nop_();
  _nop_();
  scl = 1;
  _nop_();
  _nop_(); /*时钟低电平周期大于4μs*/
  _nop_();
  _nop_();
  _nop_();
  scl = 0; /*清时钟线，住I2C总线以便继续接收*/
  _nop_();
  _nop_();
}

bit I2C_ByteWrite(u8 dat)
{
  Start_I2c();            //启动总线
  I2C_SendByte(I2C_ADDR); //发送器件地址
  if (ack == 0)
    return (0);
  I2C_SendByte(dat); //发送数据
  if (ack == 0)
    return (0);
  Stop_I2c(); //结束总线
  delay(10);
  return (1);
}

void I2C_Writes_Bytes(u8 *buff, int number)
{
  int i;
  for (i = 0; i < number; i++)
  {
    I2C_ByteWrite(buff[i]);
  }
}

u8 GetChipStatus()
{
  u8 dat = 0xff;
  u8 *pBuffer = 0xff;
  u8 AskState[4] = {0xFD, 0x00, 0x01, 0x21};

  I2C_Writes_Bytes(AskState, 4);
  delay(100);

  Start_I2c();                //启动总线
  I2C_SendByte(I2C_ADDR + 1); //发送器件地址
  if (ack == 0)
    return (0);
  delay(5);            //必须加一点延时
  dat = I2C_RcvByte(); //读取数据

  Ack_I2c(1); //发送非应答信号
  Stop_I2c(); //结束总线
  return (dat);
}

void speech_text(u8 *str, u8 encoding_format)
{
  u16 size = strlen(str) + 2;

  XFS_Protocol_TypeDef DataPack;

  DataPack.DataHead = DATAHEAD;
  DataPack.Length_HH = size >> 8;
  DataPack.Length_LL = size;
  DataPack.Commond = 0x01;
  DataPack.EncodingFormat = encoding_format;
  DataPack.Text = str;

  I2C_ByteWrite(DataPack.DataHead);
  I2C_ByteWrite(DataPack.Length_HH);
  I2C_ByteWrite(DataPack.Length_LL);
  I2C_ByteWrite(DataPack.Commond);
  I2C_ByteWrite(DataPack.EncodingFormat);

  I2C_Writes_Bytes(DataPack.Text, strlen(DataPack.Text));
}

void SetBase(u8 *str)
{
  u16 size = strlen(str) + 2;

  XFS_Protocol_TypeDef DataPack;

  DataPack.DataHead = DATAHEAD;
  DataPack.Length_HH = size >> 8;
  DataPack.Length_LL = size;
  DataPack.Commond = 0x01;
  DataPack.EncodingFormat = 0x00;
  DataPack.Text = str;

  I2C_ByteWrite(DataPack.DataHead);
  I2C_ByteWrite(DataPack.Length_HH);
  I2C_ByteWrite(DataPack.Length_LL);
  I2C_ByteWrite(DataPack.Commond);
  I2C_ByteWrite(DataPack.EncodingFormat);

  I2C_Writes_Bytes(DataPack.Text, strlen(DataPack.Text));
}

void TextCtrl(char c, int d)
{
  char str[10];
  if (d != -1)
    sprintf(str, "[%c%d]", c, d);
  else
    sprintf(str, "[%c]", c);
  SetBase(str);
}

void SetStyle(Style_Type style)
{
  TextCtrl('f', style);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}

void SetLanguage(Language_Type language)
{
  TextCtrl('g', language);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}

void SetArticulation(Articulation_Type articulation)
{
  TextCtrl('h', articulation);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}

void SetSpell(Spell_Type spell)
{
  TextCtrl('i', spell);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}

void SetReader(Reader_Type reader)
{
  TextCtrl('m', reader);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}

void SetNumberHandle(NumberHandle_Type numberHandle)
{
  TextCtrl('n', numberHandle);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}

void SetZeroPronunciation(ZeroPronunciation_Type zeroPronunciation)
{
  TextCtrl('o', zeroPronunciation);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}

void SetNamePronunciation(NamePronunciation_Type namePronunciation)
{
  TextCtrl('r', namePronunciation);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}

void SetSpeed(int speed)
{
  TextCtrl('s', speed);
}

void SetIntonation(int intonation)
{
  TextCtrl('t', intonation);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}

void SetVolume(int volume)
{
  TextCtrl('v', volume);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}

void SetOnePronunciation(OnePronunciation_Type onePronunciation)
{
  TextCtrl('y', onePronunciation);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}

void SetRhythm(Rhythm_Type rhythm)
{
  TextCtrl('z', rhythm);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}

void SetRestoreDefault()
{
  TextCtrl('d', -1);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(10);
  }
}
