#ifndef __IIC_H
#define __IIC_H
#include "sys.h"
#include "delay.h" 		   

//IO��������
//0���ǵڶ�λ��Ȼ���ƶ�2*4��0-7һ��CRL�� 8-16һ��CLH
// *SDA  PA2*SCL  PA3
#define SDA_IN()  {GPIOA->CRL&=0XFFF0FFFF;GPIOA->CRL|=8<<4*4;}
#define SDA_OUT() {GPIOA->CRL&=0XFFF0FFFF;GPIOA->CRL|=3<<4*4;}

//IO��������	 
#define IIC_SCL    PAout(5)                                                   //SCL
#define IIC_SDA    PAout(4)                                                   //SDA	 
#define READ_SDA   PAin(4)                                                    //����SDA 

//IIC���в�������
void IIC_Init(void);                                                           //��ʼ��IIC��IO��				 
void IIC_Start(void);				                                           //����IIC��ʼ�ź�
void IIC_Stop(void);	  			                                           //����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			                                           //IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);                                           //IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				                                           //IIC�ȴ�ACK�ź�
void IIC_Ack(void);					                                           //IIC����ACK�ź�
void IIC_NAck(void);				                                           //IIC������ACK�ź�

#endif

