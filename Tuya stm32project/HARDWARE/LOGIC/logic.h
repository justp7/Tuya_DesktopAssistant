#ifndef __LOGIC_H__
#define __LOGIC_H__

#include "adc.h"

void LED_config();//�����ƿ���
void Lock_config();//��������
void Light_config();//���ȿ���
void Key_ID_Execute(u16 Add,u16 Key_ID);//��ֵ�ص�����
void Notes_Data(u8 ID,u8 *Data,u8 len);//��������
void BAT_Show(void);//������ʾ
void Wifi_Ble_Show(void);//wifi����
void wifi_weather(u8 tem,u8 hum,int pm25,u8 weather);//WIFI�������ú���
void auto_light(void);//�Զ����ȵ��ں���
u8 filter(u8 new_value);//һ���ͺ��˲�
#endif /*__LOGIC_H__*/

