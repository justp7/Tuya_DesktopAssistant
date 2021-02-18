#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
						    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTEʱ��
	GPIO_InitStructure.GPIO_Pin  = KEY_Config_Pin;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(KEY_Config_Port, &GPIO_InitStructure);//��ʼ��GPIOE4,3
}
