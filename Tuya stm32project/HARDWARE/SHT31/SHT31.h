#ifndef __SHT31_H
#define __SHT31_H
#include "sys.h" 
#define SHT30_ADDR 0x88  //ADDR (pin 2)connected to VDD

void Read_sht31(void);
void Cmd_Write_sht31(uint8_t msb,uint8_t lsb);
void Convert_sht31(void);
void Sht31_Init(void);
void Sht31_Updata(void);//SHT31�����ϴ�
#endif

