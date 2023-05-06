#include <iic.h>

sbit scl = P2 ^ 1; // I2C  时钟
sbit sda = P2 ^ 0; // I2C  数据
bit ack;           /*应答标志位*/

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

bit I2C_ByteWrite(unsigned char dat)
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



void I2C_Writes_Bytes(unsigned char *buff, int number)
{
  int i;
  for (i = 0; i < number; i++)
  {
    I2C_ByteWrite(buff[i]);
  }
}

unsigned char GetChipStatus()
{
  unsigned char dat = 0xff;
  unsigned char *pBuffer = 0xff;
  unsigned char AskState[4] = {0xFD, 0x00, 0x01, 0x21};

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

void speech_init(void)
{
  SetVolume(10);
  SetReader(Reader_XiaoPing);
  speech_text("欢迎来到桂林电子科技大学信息科技学院", GB2312);
  while (GetChipStatus() != ChipStatus_Idle) //等待芯片空闲
  {
    delay(10);
  }
	
	SetVolume(10);
  SetReader(Reader_XuDuo);
  speech_text("请问您需要点什么呢", GB2312);
  while (GetChipStatus() != ChipStatus_Idle) //等待芯片空闲
  {
    delay(10);
  }
}

void User_Speech_Text(unsigned char *text)
{
  SetVolume(10);
  SetReader(Reader_XuDuo);
  speech_text(text, GB2312);
  while (GetChipStatus() != ChipStatus_Idle) //等待芯片空闲
  {
    delay(10);
  }
}

bit I2C_ByteWrite_alone(unsigned char date)
{

  Start_I2c();            //启动总线
  I2C_SendByte(I2C_ADDR_Recognition); //发送器件地址
  if (ack == 0)
    return (0);
  I2C_SendByte(date); //发送数据
  if (ack == 0)
    return (0);

  Stop_I2c(); //结束总线

  return (1);
}

void I2C_ByteWrite_Recognition(unsigned char reg_addr, unsigned char dat)
{
  I2C_ByteWrite_alone(reg_addr);
  I2C_ByteWrite_alone(dat);
}

unsigned char I2C_BufferRead(unsigned char date)
{
  unsigned char dat;
  Start_I2c();            //启动总线
  I2C_SendByte(I2C_ADDR_Recognition); //发送器件地址
  if (ack == 0)
    return (0);
  I2C_SendByte(date); //发送器件地址
  if (ack == 0)
    return (0);
  Stop_I2c();
  delay(50);

  Start_I2c();                //启动总线
  I2C_SendByte(I2C_ADDR_Recognition + 1); //发送器件地址
  if (ack == 0)
    return (0);
  delay(1);
  dat = I2C_RcvByte(); //读取数据

  Ack_I2c(1); //发送非应答信号
  Stop_I2c(); //结束总线

  return (dat);
}

void AsrAddWords(unsigned char idNum, unsigned char *words)
{
  int i = 0;
  unsigned char date_length = strlen(words) + 2;
  unsigned char str_length = strlen(words);
  I2C_ByteWrite_alone(ASR_ADD_WORD_ADDR); //发送寄存器地址
  I2C_ByteWrite_alone(date_length);       //发送数据长度
  I2C_ByteWrite_alone(idNum);
  for (i = 0; i < str_length; i++)
  {
    I2C_ByteWrite_alone(words[i]);
  }
  I2C_ByteWrite_alone(0);
}

void RGB_Set(unsigned char R, unsigned char G, unsigned char B)
{

  I2C_ByteWrite_alone(ASR_RGB_ADDR);
  I2C_ByteWrite_alone(R);
  I2C_ByteWrite_alone(G);
  I2C_ByteWrite_alone(B);
}

/*****************************
       忙闲等待取函数
******************************/
void BusyWait(void)
{

  unsigned char busy_flag = 0xff;
  while (busy_flag != 0)
  {
    busy_flag = I2C_BufferRead(ASR_BUSY);
    delay(500);
  }
}
//语音识别初始化函数
void Recognition_Init(void)
{
  unsigned char cleck = 0xff;
#if 0
  I2C_ByteWrite_Recognition(ASR_CLEAR_ADDR, 0x40); //清除掉电保存区,录入前需要清除掉电保存区
  BusyWait();
  I2C_ByteWrite_Recognition(ASR_MODE_ADDR, 1); //设置模式为口令模式
  BusyWait();
  AsrAddWords(0, "xiao ya");
  BusyWait();
  AsrAddWords(1, "yi hao men");
  BusyWait();
  AsrAddWords(2, "er hao men");
  BusyWait();
  AsrAddWords(3, "sang hao men");
  BusyWait();
  AsrAddWords(4, "si hao men");
  BusyWait();
  AsrAddWords(5, "wu hao men");
  BusyWait();
  AsrAddWords(6, "liu hao men");
  BusyWait();

  while (cleck != 10)
  {
    cleck = I2C_BufferRead(ASR_NUM_CLECK);
    delay(500);
  }
#endif
  I2C_ByteWrite_Recognition(ASR_REC_GAIN, 0x40); //设置灵敏度

}