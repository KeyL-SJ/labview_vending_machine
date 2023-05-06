#include <iic.h>

sbit k1 = P3 ^ 1;
sbit k2 = P3 ^ 0;
sbit k3 = P3 ^ 2;
sbit k4 = P3 ^ 3;

void main()
{
	speech_init();
	
  while (1)
  {
    if (k1 == 0)
    {
      SetVolume(10);
      SetReader(Reader_XiaoPing);
      speech_text("һ�������ѿ�����ȡ����Ʒ�غ�����лл", GB2312);
      while (GetChipStatus() != ChipStatus_Idle) //�ȴ�оƬ����
      {
        delay(10);
      }
    }
    else if (k2 == 0)
    {
      SetVolume(10);
      SetReader(Reader_XuDuo);
      speech_text("���������ѿ�����ȡ����Ʒ�غ�����лл", GB2312);
      while (GetChipStatus() != ChipStatus_Idle) //�ȴ�оƬ����
      {
        delay(10);
      }
    }
  }
}
