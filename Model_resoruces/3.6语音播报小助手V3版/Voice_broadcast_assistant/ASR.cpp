#include "ASR.h"


/****************************
      寄存器设置函数  
*****************************/
bool I2CWrite(unsigned char reg_addr,unsigned char date)
{
    Wire.beginTransmission(ASR_I2C_ADDR);  //发送Device地址
    Wire.write(reg_addr);              //发送要操作的寄存器地址 
    Wire.write(date);                  //发送要设置的值
    if(Wire.endTransmission()!=0)            //发送结束信号
      {
          delay(10);
          return false;
      }
      delay(10);
      return true;  
}

/****************************
      检测值读取函数  
*****************************/
bool WireReadData(unsigned char reg_addr,unsigned char *value,int num)
{   
    Wire.beginTransmission(ASR_I2C_ADDR);  //发送Device地址
    Wire.write(reg_addr);              //发送要操作的寄存器地址  
    delay(10);
    if(Wire.endTransmission()!=0)            //发送结束信号
     {
          delay(10);
          return false;
     }
      delay(10);


    Wire.requestFrom(ASR_I2C_ADDR, num);

    while(Wire.available())
    {
        char ff = Wire.read();    // receive a byte as character
        *value = ff;
        value++;
        delay(10);
    } 
        
     return true; 
 }


/*****************************
       RGB设置函数
******************************/
bool RGB_Set(unsigned char R,unsigned char G,unsigned char B)
{
      Wire.beginTransmission(ASR_I2C_ADDR);  //发送Device地址
      Wire.write(ASR_RGB_ADDR); 
      Wire.write(R);
      Wire.write(G);      
      Wire.write(B);
      if(Wire.endTransmission()!=0)            //发送结束信号
      {
          delay(10);
          return false;
      }
      delay(10);
      return true;
}

/*****************************
       单字节读取函数
******************************/
bool I2CWrite_byte(unsigned char date)
{
    Wire.beginTransmission(ASR_I2C_ADDR);  //发送Device地址
    Wire.write(date);                  //发送要设置的值
    if(Wire.endTransmission()!=0)            //发送结束信号
      {
          delay(10);
          return false;
      }
      delay(10);
      return true;  
}

/*****************************
       忙闲等待取函数
******************************/
void BusyWait(void)
{
  
  unsigned char busy_flag = 0xff;
  while(busy_flag != 0)
  {
      WireReadData(ASR_BUSY,&busy_flag,1);
      Serial.println(busy_flag);
      delay(100);
    } 
  
  }

/*****************************
       添加词条函数
******************************/
void AsrAddWords(unsigned char idNum,unsigned char * words)
{     
     unsigned char date_num =strlen(words)+2;
     unsigned char str_num =strlen(words); 
     I2CWrite_byte(ASR_ADD_WORD_ADDR);     //发送词组寄存器地址
     I2CWrite_byte(date_num);      //发送本次发送的数据长度，计算方式:词组号+字符串长度+0作为字符串结束符
     Serial.println(str_num);
     I2CWrite_byte(idNum);                //发送词组号
     for(int i = 0; i<str_num;i++)
     {
       I2CWrite_byte(words[i]);           //发送词字符
      }
      I2CWrite_byte(0);               //发送0作为结束符
  
}
