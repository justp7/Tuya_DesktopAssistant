#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = LED_WIFI_Pin;				 //LED0-->PB.5 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(LED_WIFI_Port, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
	GPIO_SetBits(LED_WIFI_Port,LED_WIFI_Pin);						 //PB.5 �����
}
 
