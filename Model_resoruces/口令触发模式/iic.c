#include <iic.h>

bit ack; /*Ӧ���־λ*/

/*------------------------------------------------
                  ��ʱ����
------------------------------------------------*/
void delay(int i)
{
  int j, k;
  for (j = i; j > 0; j--)
    for (k = 150; k > 0; k--)
      ;
}

/*******************************************************************
                     �����ߺ���
����ԭ��: void  Start_I2c();
����:     ����I2C����,������I2C��ʼ����.
********************************************************************/
void Start_I2c()
{
  sda = 1; /*������ʼ�����������ź�*/
  _nop_();
  scl = 1;
  _nop_(); /*��ʼ��������ʱ�����4.7us,��ʱ*/
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  sda = 0; /*������ʼ�ź�*/
  _nop_(); /* ��ʼ��������ʱ�����4��s*/
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  scl = 0; /*ǯסI2C���ߣ�׼�����ͻ�������� */
  _nop_();
  _nop_();
}

/*******************************************************************
                      �������ߺ���
����ԭ��: void  Stop_I2c();
����:     ����I2C����,������I2C��������.
********************************************************************/
void Stop_I2c()
{
  sda = 0; /*���ͽ��������������ź�*/
  _nop_(); /*���ͽ���������ʱ���ź�*/
  scl = 1; /*������������ʱ�����4��s*/
  while (scl == 0)
  {
    scl = 1;
  }
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  sda = 1; /*����I2C���߽����ź�*/
  while (sda == 0)
  {
    sda = 1;
  }
  _nop_();
  _nop_();
  _nop_();
  _nop_();
}

/*******************************************************************
                 �ֽ����ݷ��ͺ���
����ԭ��: void  I2C_SendByte(UCHAR c);
����:     ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
          ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0)
           ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
********************************************************************/
void I2C_SendByte(unsigned char c)
{
  unsigned char i;

  for (i = 0; i < 8; i++) /*Ҫ���͵����ݳ���Ϊ8λ*/
  {
    if ((c << i) & 0x80)
      sda = 1; /*�жϷ���λ*/
    else
      sda = 0;
    _nop_();
    scl = 1; /*��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ*/
    while (scl == 0)
    {
      scl = 1;
    }

    _nop_();
    _nop_(); /*��֤ʱ�Ӹߵ�ƽ���ڴ���4��s*/
    _nop_();
    _nop_();
    _nop_();
    scl = 0;
  }
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  sda = 1; /*8λ��������ͷ������ߣ�׼������Ӧ��λ*/
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  scl = 1;
  while (scl == 0)
  {
    scl = 1;
  }
  _nop_();
  _nop_();
  _nop_();
  if (sda == 1)
    ack = 0;
  else
    ack = 1; /*�ж��Ƿ���յ�Ӧ���ź�*/
  scl = 0;
  _nop_();
  _nop_();
}

/*******************************************************************
                 �ֽ����ݽ��պ���
����ԭ��: UCHAR  I2C_RcvByte();
����:        �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
          ���������Ӧ����Ӧ��ӻ���
********************************************************************/
unsigned char I2C_RcvByte()
{
  unsigned char retc = 0, i = 0;
  sda = 1; /*��������Ϊ���뷽ʽ*/
  for (i = 0; i < 8; i++)
  {
    _nop_();
    scl = 0; /*��ʱ����Ϊ�ͣ�׼����������λ*/
    while (scl == 1)
    {
      scl = 0;
    }
    _nop_();
    _nop_(); /*ʱ�ӵ͵�ƽ���ڴ���4.7��s*/
    _nop_();
    _nop_();
    _nop_();
    scl = 1; /*��ʱ����Ϊ��ʹ��������������Ч*/
    while (scl == 0)
    {
      scl = 1;
    }
    _nop_();
    _nop_();
    retc = retc << 1;
    if (sda == 1)
      retc = retc + 1; /*������λ,���յ�����λ����retc�� */
    _nop_();
    _nop_();
  }
  scl = 0;
  _nop_();
  _nop_();
  return (retc);
}

/********************************************************************
                     Ӧ���Ӻ���
����ԭ��:  void Ack_I2c(bit a);
����:      ����������Ӧ���ź�(������Ӧ����Ӧ���źţ���λ����a����)
********************************************************************/
void Ack_I2c(bit a)
{
  if (a == 0)
    sda = 0; /*�ڴ˷���Ӧ����Ӧ���ź� */
  else
    sda = 1; /*0Ϊ����Ӧ��1Ϊ��Ӧ���ź� */
  _nop_();
  _nop_();
  _nop_();
  scl = 1;
  _nop_();
  _nop_(); /*ʱ�ӵ͵�ƽ���ڴ���4��s*/
  _nop_();
  _nop_();
  _nop_();
  scl = 0; /*��ʱ���ߣ�סI2C�����Ա��������*/
  _nop_();
  _nop_();
}

bit I2C_ByteWrite_alone(unsigned char date)
{

  Start_I2c();            //��������
  I2C_SendByte(I2C_ADDR_Recognition); //����������ַ
  if (ack == 0)
    return (0);
  I2C_SendByte(date); //��������
  if (ack == 0)
    return (0);

  Stop_I2c(); //��������

  return (1);
}

void I2C_ByteWrite(unsigned char reg_addr, unsigned char dat)
{
  I2C_ByteWrite_alone(reg_addr);
  I2C_ByteWrite_alone(dat);
}

unsigned char I2C_BufferRead(unsigned char date)
{
  unsigned char dat;
  Start_I2c();            //��������
  I2C_SendByte(I2C_ADDR_Recognition); //����������ַ
  if (ack == 0)
    return (0);
  I2C_SendByte(date); //����������ַ
  if (ack == 0)
    return (0);
  Stop_I2c();
  delay(50);

  Start_I2c();                //��������
  I2C_SendByte(I2C_ADDR_Recognition + 1); //����������ַ
  if (ack == 0)
    return (0);
  delay(1);
  dat = I2C_RcvByte(); //��ȡ����

  Ack_I2c(1); //���ͷ�Ӧ���ź�
  Stop_I2c(); //��������

  return (dat);
}

void AsrAddWords(unsigned char idNum, unsigned char *words)
{
  int i = 0;
  unsigned char date_length = strlen(words) + 2;
  unsigned char str_length = strlen(words);
  I2C_ByteWrite_alone(ASR_ADD_WORD_ADDR); //���ͼĴ�����ַ
  I2C_ByteWrite_alone(date_length);       //�������ݳ���
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
       æ�еȴ�ȡ����
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
//����ʶ���ʼ������
void Recognition_Init(void)
{

  unsigned char cleck = 0xff;
#if 1
  I2C_ByteWrite(ASR_CLEAR_ADDR, 0x40); //������籣����,¼��ǰ��Ҫ������籣����
  BusyWait();
  I2C_ByteWrite(ASR_MODE_ADDR, 1); //����ģʽΪ����ģʽ
  BusyWait();
  AsrAddWords(0, "xiao ya");
  BusyWait();
  AsrAddWords(1, "yi hao men");
  BusyWait();
  AsrAddWords(2, "er hao men");
  BusyWait();
  AsrAddWords(3, "san hao men");
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
  I2C_ByteWrite(ASR_REC_GAIN, 0x55); //����������

  RGB_Set(255, 255, 255);
  I2C_ByteWrite(ASR_BUZZER, 0x01); //����������
  delay(1000);
  I2C_ByteWrite(ASR_BUZZER, 0x00); //����������
  RGB_Set(0, 0, 0);
}