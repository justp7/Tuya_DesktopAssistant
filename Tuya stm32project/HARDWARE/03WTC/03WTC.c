#include "03WTC.h"
#include "usart.h"
#include "stdbool.h"
#include "stdio.h"

#include "wifi.h"

struct Status_config All;
/*******************驱动层*******************/
/** 
* @brief  图标旋转
* @param  
* @ref Add 变量地址
* @ref Angle 旋转的角度
* @return none
* - 
* @details  
* @see  
*/ 
void Icon_Rotate(u16 Add,u16 Angle)
{
	u8 data[2];
	//切换的图标ID
	data[0] = (Angle & 0xff00)>> 8;//图标ID
	data[1] = Angle & 0x00ff;
	
	Write_register(Add,2,data);//数据打包发送
}

/** 
* @brief  中文文本显示
* @param  
* @ref Add 变量地址
* @ref Text 文本数据
* @ref len 文本长度
* @return none
* - 
* @details  
* @see  
*/ 
void Chinese_Text(u16 Add,char *Text,u8 len)
{
	u8 data[50] = {0x20};
	u8 i = 0;
	//文本数据填充
	for(i= 0;i < len;i++)
		data[i] = (u8)Text[i];
		
	Write_register(Add,len,data);//数据打包发送
}
/** 
* @brief  实时曲线
* @param  
* @ref Data 数据
* @return none
* - 
* @details  
* @see  
*/ 
void Curve_set(u16 num)
{
	u8 data[10];
	//基础设置
	data[0] = 0x03;
	data[1] = 0x10;
	data[2] = 0x5A;
	data[3] = 0xA5;
	//通道数
	data[4] = 0x01;
  data[5] = 0x00;
	//选择通道
	data[6] = 0x00;
	//数据字长度
	data[7] = 0x01;
	//数据填充
	data[8] = (num & 0xff00)>>8;
	data[9] = num & 0x00ff;
	
	data_pack(10,Write,data);//数据打包发送
}
/** 
* @brief  文本显示
* @param  
* @ref Add 变量地址
* @ref Text 文本数据
* @ref len 文本长度
* @return none
* - 
* @details  
* @see  
*/ 
void Text_set(u16 Add,char *Text,u8 len)
{
	u8 data[10];
	u8 i = 0;
	//文本数据填充
	for(i= 0;i < len;i++)
		data[i] = (u8)Text[i];
		
	Write_register(Add,len,data);//数据打包发送
}
/** 
* @brief  数据变量
* @param  
* @ref Add 变量地址
* @ref Data 变量数据（-32768 - 32767）
* @return none
* - 
* @details  
* @see  
*/ 
void Data_set(u16 Add,u16 Data)
{
	u8 data[2];
	//切换的图标ID
	data[0] = (Data & 0xff00)>> 8;//图标ID
	data[1] = Data & 0x00ff;
	Write_register(Add,2,data);//数据打包发送
}
/** 
* @brief  变量图标
* @param  
* @ref Add 图标地址
* @ref ID 图标ID
* @return none
* - 
* @details  
* @see  
*/ 
void Icon_set(u16 Add,u16 ID)
{
	u8 data[2];
	//切换的图标ID
	data[0] = (ID & 0xff00)>> 8;//图标ID
	data[1] = ID & 0x00ff;
	Write_register(Add,2,data);//数据打包发送
}
/** 
* @brief  背景亮度调节
* @param  
* @ref on_light 开启亮度
* @ref off_light 关闭亮度
* @ref time 开启时间/10mS
* @return none
* - 
* @details  
* @see  
*/ 
void LED_Config(u8 on_light,u8 off_light,u16 time)
{
	u8 data[4];
	
	data[0] = on_light;//开启亮度
	data[1] = off_light;//关闭亮度
	
	//开启时间/10mS
	data[2] = (time & 0xff00)>> 8;
	data[3] = time & 0x00ff;
	
	//0x0082 背景亮度寄存器
	Write_register(0x0082,4,data);//数据打包发送
}
/** 
* @brief  背景图片切换
* @param  
* @ref ID 要切换到的图片ID
* @return none
* - 
* @details  
* @see  
*/ 
void PIC_Set(u16 ID)
{
	u8 data[4];
	
	data[0] = 0x5A;//启动一次页面处理
	data[1] = 0x01;//页面切换
	data[2] = (ID & 0xff00)>> 8;
	data[3] = ID & 0x00ff;
	
	//0x0084 背景图片地址
	Write_register(0x0084,4,data);//数据打包发送
}
/** 
* @brief  写RTC寄存器
* @param  
* @ref year 年
* @ref week 周几
* @return none
* - 
* @details  
* @see  
*/ 
void RTC_SET(u8 year, u8 month, u8 day, u8 week, u8 hour, u8 min, u8 sec)
{
	u8 data[8];
	
	data[0] = year; //寄存器数据
	data[1] = month;
	data[2] = day;
	data[3] = week;
	data[4] = hour;
	data[5] = min;
	data[6] = sec;
	data[7] = 0;
	
	//0x0010 RTC寄存器地址
	Write_register(0x0010,8,data);//数据打包发送
}
/** 
* @brief  返回数据解析
* @param  
* @ref Data 数据数组
* @return none
* - 1 解析成功
* - 0 解析失败
* @details  
* @see  
*/ 
void Recieve_Data(u8 *Data){
	u8 Len = 0;//数据长度
	u8 Data_len = 0;
	u16 Key_ID;
	u16 Add; 
	if(Data[0] == 0x5A && Data[1] == 0xA5)//帧头接收成功
	{
		Len = Data[2];
		if(Data[3] == 0x83 && Len != 0)//返回指令 长度不为0
		{
			Add = Data[4]<<8 | Data[5];//地址
			Data_len = Data[6];//字 长度
			if(Data_len != 0)
				Key_ID = Data[7]<<8 | Data[8];//按下的键值
			Key_ID_Execute(Add,Key_ID);//键值处理函数
		}
	}
}
/** 
* @brief  读寄存器
* @param  
* @ref add 变量地址（两个字节）
* @ref data 数据(两个字节)
* @return 
* - 
* @details  
* @see  
*/ 
void Read_register(u16 Add,u8 data)
{
	u8 pack_data[4];
	
	pack_data[0] = (Add & 0xff00)>> 8;//地址
	pack_data[1] = Add & 0x00ff;
	
	
	data_pack(5,Write,pack_data);
}

/** 
* @brief  写寄存器
* @param  
* @ref add 变量地址（两个字节）
* @ref len 数据长度
* @return 
* - 
* @details  
* @see  
*/ 
void Write_register(u16 add,u8 len,u8 *data)
{
	u8 pack_data[100];
	u8 i;
	//两字节地址
	pack_data[0] = (add & 0xff00)>> 8;
	pack_data[1] = add & 0x00ff;
	
	//指令数据填充
	for(i = 0;i < len; i++)
	{
		pack_data[i+2] = data[i];
	}
	
	data_pack(len + 2,Write,pack_data);//数据长度 + 地址
}

/** 
* @brief  数据打包
* @param  
* @ref len 数据长度 （指令+数据+校验的字节数）
* @ref order 读/写指令
* @ref data 数据
* @return none
* - 
* @details  
* @see  
*/ 
void data_pack(u8 len,u8 order,u8 *data)
{
	u8 send_data[300];
	u8 i = 0;
	//帧头 长度 填充
	send_data[0] = 0x5A;
	send_data[1] = 0xA5;
	send_data[2] = len + 1;
	//判断读写
	if(order == Write)
		send_data[3] = 0x82;
	else if(order == Read)
		send_data[3] = 0x83;
	//数据填充
	for(i = 0;i < len;i++)
		send_data[4+i] = data[i];
	
	send_pack(len + 4,send_data);//数据发送
	
}
/** 
* @brief  串口数据发送
* @param  
* @ref len 数据长度 
* @ref buffer 要发送的数据
* @return 
* - 
* @details  
* @see  
*/ 
void send_pack(u8 len,u8 *buffer)
{
	u8 i = 0;
	
	while (i < len){
		USART_SendData(USART_SEND_n, (u8) buffer[i++]);
		while (USART_GetFlagStatus(USART_SEND_n, USART_FLAG_TXE) == RESET); //传输完成标志位
	}
}

