#ifndef __IIC_H
#define __IIC_H
#include "sys.h"
#include "delay.h" 		   

//IO方向设置
//0得是第二位，然后移动2*4（0-7一组CRL） 8-16一组CLH
// *SDA  PA2*SCL  PA3
#define SDA_IN()  {GPIOA->CRL&=0XFFF0FFFF;GPIOA->CRL|=8<<4*4;}
#define SDA_OUT() {GPIOA->CRL&=0XFFF0FFFF;GPIOA->CRL|=3<<4*4;}

//IO操作函数	 
#define IIC_SCL    PAout(5)                                                   //SCL
#define IIC_SDA    PAout(4)                                                   //SDA	 
#define READ_SDA   PAin(4)                                                    //输入SDA 

//IIC所有操作函数
void IIC_Init(void);                                                           //初始化IIC的IO口				 
void IIC_Start(void);				                                           //发送IIC开始信号
void IIC_Stop(void);	  			                                           //发送IIC停止信号
void IIC_Send_Byte(u8 txd);			                                           //IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);                                           //IIC读取一个字节
u8 IIC_Wait_Ack(void); 				                                           //IIC等待ACK信号
void IIC_Ack(void);					                                           //IIC发送ACK信号
void IIC_NAck(void);				                                           //IIC不发送ACK信号

#endif

