/*********************************************************************************************
��Ŀ˵����  Ϳѻ������ʪ������ϵͳ����˳���
��������	�������������
��д�ˣ�	����	
��дʱ�䣺	2021��2��5��
Ӳ��֧�֣�	STM32F103CB   �ⲿ����8MHz RCC����������Ƶ72MHz��  

�޸���־������
1-	
	
							
˵����
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
	delay_ms(500);//�ȴ�ϵͳ�ȶ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	RCC_Configuration();
	NVIC_Configuartion();//����NVIC�ȼ�
	USART1_Init(9600);	 //����ģ�� 9600
	USART2_Init(9600);	 //ͿѻWIFIģ�� ����9600
  USART3_Init(115200);//������ͨ�� ����115200
  RTC_Config();  //RTC��ʼ�� RTC��WIFI�Զ�����

	Sht31_Init();//��ʼ��SHT31

  TIM3_Init(7200-1,10000-1);//��ʱ��3��ʼ�� 1s �������
  TIM4_Init(7200-1,55000-1);//wifi���� RTC����

	ADC_Configuration();//ADC��ʼ��
	wifi_protocol_init();//Ϳѻ����WIFIģ���ʼ��
  first_show();//��һ����ʾ
 	while(1)
	{
		wifi_uart_service();
		delay_ms(1);
		flag ++;
		if(flag > 60000)
		{
			Read_sht31();//��ȡSHT30����
			Sht31_Updata();//�ϴ�SHT11����
			flag = 0;
		}
	}	 
}
