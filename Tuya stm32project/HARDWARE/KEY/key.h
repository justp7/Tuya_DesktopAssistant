#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY_Config_Port   GPIOA
#define KEY_Config_Pin    GPIO_Pin_6
#define KEY_Config_Read() GPIO_ReadInputDataBit(KEY_Config_Port,KEY_Config_Pin)

void KEY_Init(void);//IO≥ı ºªØ

#endif

