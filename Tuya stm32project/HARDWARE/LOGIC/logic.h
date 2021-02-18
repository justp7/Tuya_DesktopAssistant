#ifndef __LOGIC_H__
#define __LOGIC_H__

#include "adc.h"

void LED_config();//联动灯控制
void Lock_config();//屏保控制
void Light_config();//亮度控制
void Key_ID_Execute(u16 Add,u16 Key_ID);//键值回调函数
void Notes_Data(u8 ID,u8 *Data,u8 len);//备忘设置
void BAT_Show(void);//电量显示
void Wifi_Ble_Show(void);//wifi蓝牙
void wifi_weather(u8 tem,u8 hum,int pm25,u8 weather);//WIFI天气设置函数
void auto_light(void);//自动亮度调节函数
u8 filter(u8 new_value);//一阶滞后滤波
#endif /*__LOGIC_H__*/

