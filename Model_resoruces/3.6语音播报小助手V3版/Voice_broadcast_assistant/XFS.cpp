#include "XFS.h"
#include <Wire.h>

#define XFS_WIRE Wire

#define XFS_DataHead (uint8_t)0xFD

XFS5152CE::XFS5152CE(EncodingFormat_Type encodingFormat)
{
  DataPack.DataHead = XFS_DataHead;
  DataPack.Length_HH = 0x00;
  DataPack.Length_LL = 0x00;

  DataPack.Commond = 0x00;
  DataPack.EncodingFormat = encodingFormat;

  ChipStatus = 0x00;
}


void XFS5152CE::Begin(uint8_t addr)
{
  I2C_Addr = addr;
  XFS_WIRE.begin();
}

uint8_t XFS5152CE::GetChipStatus()
{
  uint8_t AskState[4] = {0xFD,0x00,0x01,0x21};
  XFS_WIRE.beginTransmission(I2C_Addr);
  XFS_WIRE.write(AskState,4);
  XFS_WIRE.endTransmission();
  delay(100);
  XFS_WIRE.requestFrom(I2C_Addr, 1);
  while (XFS_WIRE.available())
  {
    ChipStatus = XFS_WIRE.read();
  }
  return ChipStatus;
}


bool XFS5152CE::IIC_WriteByte(uint8_t data)
{
  Wire.beginTransmission(I2C_Addr);
  Wire.write(data);
  if(Wire.endTransmission()!=0)            //发送结束信号
   {
          delay(10);
          return false;
    }
    delay(10);
    return true;  
}

void XFS5152CE::IIC_WriteBytes(uint8_t* buff, uint32_t size)
{
  for (uint32_t i = 0; i < size; i++)
  {
    IIC_WriteByte(buff[i]);
  }
}

void XFS5152CE::StartSynthesis(const char* str)
{
  uint16_t size = strlen(str) + 2;
  DataPack.Length_HH = highByte(size);
  DataPack.Length_LL = lowByte(size);
  DataPack.Commond = CMD_StartSynthesis;
  DataPack.Text = str;

   
  IIC_WriteBytes((uint8_t*)&DataPack,5);
  IIC_WriteBytes(DataPack.Text, strlen(str));
  
}


void XFS5152CE::StartSynthesis(String str)
{
  StartSynthesis((const char*)str.c_str());
}

void XFS5152CE::SendCommond(CMD_Type cmd)
{
  DataPack.Length_HH = 0x00;
  DataPack.Length_LL = 0x01;
  DataPack.Commond = cmd;
  
  XFS_WIRE.beginTransmission(I2C_Addr);
  XFS_WIRE.write((uint8_t*)&DataPack, 4);
  XFS_WIRE.endTransmission();
}

void XFS5152CE::StopSynthesis()
{
  SendCommond(CMD_StopSynthesis);
}

void XFS5152CE::PauseSynthesis()
{
  SendCommond(CMD_PauseSynthesis);
}

void XFS5152CE::RecoverySynthesis()
{
  SendCommond(CMD_RecoverySynthesis);
}

void XFS5152CE::TextCtrl(char c, int d)
{
  char str[10];
  if (d != -1)
    sprintf(str, "[%c%d]", c, d);
  else
    sprintf(str, "[%c]", c);
  StartSynthesis(str);
}

void XFS5152CE::SetEncodingFormat(EncodingFormat_Type encodingFormat)
{
  DataPack.EncodingFormat = encodingFormat;
}

void XFS5152CE::SetStyle(Style_Type style)
{
  TextCtrl('f', style);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}

void XFS5152CE::SetLanguage(Language_Type language)
{
  TextCtrl('g', language);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}

void XFS5152CE::SetArticulation(Articulation_Type articulation)
{
  TextCtrl('h', articulation);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}

void XFS5152CE::SetSpell(Spell_Type spell)
{
  TextCtrl('i', spell);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  } 
}

void XFS5152CE::SetReader(Reader_Type reader)
{
  TextCtrl('m', reader);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}

void XFS5152CE::SetNumberHandle(NumberHandle_Type numberHandle)
{
  TextCtrl('n', numberHandle);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}

void XFS5152CE::SetZeroPronunciation(ZeroPronunciation_Type zeroPronunciation)
{
  TextCtrl('o', zeroPronunciation);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}


void XFS5152CE::SetNamePronunciation(NamePronunciation_Type namePronunciation)
{
  TextCtrl('r', namePronunciation);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}

void XFS5152CE::SetSpeed(int speed)
{
  speed = constrain(speed, 0, 10);
  TextCtrl('s', speed);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}

void XFS5152CE::SetIntonation(int intonation)
{
  intonation = constrain(intonation, 0, 10);
  TextCtrl('t', intonation);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}

void XFS5152CE::SetVolume(int volume)
{
  volume = constrain(volume, 0, 10);
  TextCtrl('v', volume);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}

void XFS5152CE::SetPromptTone(PromptTone_Type promptTone)
{
  TextCtrl('x', promptTone);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}

void XFS5152CE::SetOnePronunciation(OnePronunciation_Type onePronunciation)
{
  TextCtrl('y', onePronunciation);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}

void XFS5152CE::SetRhythm(Rhythm_Type rhythm)
{
  TextCtrl('z', rhythm);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}


void XFS5152CE::SetRestoreDefault()
{
  TextCtrl('d', -1);
  while(GetChipStatus() != ChipStatus_Idle)
  {
     delay(30);
  }
}
