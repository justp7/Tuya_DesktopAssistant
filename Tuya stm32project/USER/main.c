/*********************************************************************************************
项目说明：  涂鸦智能温湿度桌面系统桌面端程序
程序名：	天气助手桌面端
编写人：	刘畅	
编写时间：	2021年2月5日
硬件支持：	STM32F103CB   外部晶振8MHz RCC函数设置主频72MHz　  

修改日志：　　
1-	
	
							
说明：
 # 
 # 
*********************************************************************************************/#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "tim.h"
#include "usart.h"
#include "adc.h"

#include "rtc.h"
#include "03WTC.h"
#include "sht31.h"

#include "mcu_api.h"
#include "protocol.h"
#include "system.h"
#include "wifi.h"

u16 flag = 60001;

void first_show()
{
	All.Light_State = 0;
	All.Lock_State = 0;
	Sht31_Updata();
}

int main(void)
{
	delay_ms(500);//等待系统稳定
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	RCC_Configuration();
	NVIC_Configuartion();//配置NVIC等级
	USART1_Init(9600);	 //蓝牙模组 9600
	USART2_Init(9600);	 //涂鸦WIFI模组 串口9600
  USART3_Init(115200);//串口屏通信 串口115200
  RTC_Config();  //RTC初始化 RTC由WIFI自动设置

	Sht31_Init();//初始化SHT31

  TIM3_Init(7200-1,10000-1);//定时器3初始化 1s 监测锁屏
  TIM4_Init(7200-1,55000-1);//wifi蓝牙 RTC更新

	ADC_Configuration();//ADC初始化
	wifi_protocol_init();//涂鸦智能WIFI模块初始化
  first_show();//第一次显示
 	while(1)
	{
		wifi_uart_service();
		delay_ms(1);
		flag ++;
		if(flag > 60000)
		{
			Read_sht31();//读取SHT30数据
			Sht31_Updata();//上传SHT11数据
			flag = 0;
		}
	}	 
}
