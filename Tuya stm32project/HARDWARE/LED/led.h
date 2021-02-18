#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


#define LED_WIFI_Port GPIOB
#define LED_WIFI_Pin  GPIO_Pin_5

#define LED_WIFI_on() GPIO_ResetBits(LED_WIFI_Port,LED_WIFI_Pin);//LED_WIFI输出低电平
#define LED_WIFI_off() GPIO_SetBits(LED_WIFI_Port,LED_WIFI_Pin);//LED_WIFI输出低电平

void LED_Init(void);//初始化

		 				    
#endif
