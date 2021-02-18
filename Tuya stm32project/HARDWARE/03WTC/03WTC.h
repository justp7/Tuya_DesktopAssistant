#ifndef __03WTC_H
#define __03WTC_H

#include "sys.h"
#include <stdbool.h>
struct  Status_config
{
	bool Lock_State;//锁屏标志
	bool Light_State;//自动亮度
	bool Led_State;//联动灯
	u8 Lock_time;
	u8 Ble_time;
};

extern struct Status_config All;
//定义串口屏发送端口
#define USART_SEND_n		USART3
//宏定义
#define Write 0x82
#define Read  0x83
//地址定义
#define wea_icon 0x5000   //天气图标
#define ble_icon 0x5001   //蓝牙图标
#define wifi_icon 0x5002   //无线图标
#define bat_icon 0x5003   //电池图标
#define spin_icon 0x5018   //指针图标

#define tem_data 0x5004   //温度数据
#define hum_data 0x5006   //湿度数据
#define wea_tem 0x5008   //天气温度
#define wea_hum 0x500A   //天气湿度
#define wea_pm25 0x500C   //天气pm2.5
#define up_data 0x5010   //上传数据
#define down_data 0x5014   //下载数据

#define up_text 0x5020   //上传文字
#define down_text 0x5024   //下载文字
#define CZK_text 0x5030   //天气中文

#define CPU_data 0x5042 //CPU数据
/*按键回调地址*/
#define LED_ADD 0x5020 //键值
#define WIFI_IN_ADD 0x5050 //进入配网
#define WIFI_OUT_ADD 0x5051//退出配网
#define Lock_ADD 0x5044		 //锁屏地址
#define Light_ADD 0x5045	 //亮度自动调节
#define Lock_Pic_ADD 0x5043 //屏保

/*按键操作图标地址*/
#define LED_Set  0x5019 //智能灯图标
#define Lock_Set 0x5040 //锁屏开关图标
#define Light_Set 0x5041 //自动亮度开关

/*备忘页面*/
#define Notes1_Icon 0x5100 //备忘1图标
#define Notes1_ADD  0x5101
#define Notes1_Text 0x5102

#define Notes2_Icon 0x5200
#define Notes2_ADD  0x5201
#define Notes2_Text 0x5202

#define Notes3_Icon 0x5300
#define Notes3_ADD  0x5301
#define Notes3_Text 0x5302

#define Notes4_Icon 0x5400
#define Notes4_ADD  0x5401
#define Notes4_Text 0x5402

#define Lock_time_Set 20 // 锁屏计时
#define Ble_time_Set 10 // 蓝牙连接计时

void Weather_ICON(u8 Weather_ID);
void Weather_show(u8 Weather_ID);
//上层
void Icon_Rotate(u16 Add,u16 Angle);//图标旋转显示
void Key_ID_Execute(u16 Add,u16 Key_ID);//键值处理函数
void Curve_set(u16 num);//实时曲线
void Text_set(u16 Add,char *Text,u8 len);//文本显示
void Chinese_Text(u16 Add,char *Text,u8 len);//中文文本显示
void Data_set(u16 Add,u16 Data);//数据变量
void Icon_set(u16 Add,u16 ID);//变量图标
void LED_Config(u8 on_light,u8 off_light,u16 time);//背景亮度调节
void PIC_Set(u16 ID);//背景图片切换
void RTC_SET(u8 year, u8 month, u8 day, u8 week, u8 hour, u8 min, u8 sec);//写RTC寄存器

//下层
void Recieve_Data(u8 *Data);//数据解析
void Write_register(u16 Add,u8 len,u8 *data);//写寄存器
void data_pack(u8 len,u8 order,u8 *data);//数据打包
void send_pack(u8 len,u8 *buffer);//发送数据

#endif

