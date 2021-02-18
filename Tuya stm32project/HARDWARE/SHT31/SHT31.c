#include "sht31.h"
#include "delay.h"
#include "iic.h"
#include "usart.h"

#include "03WTC.h"
#include "wifi.h"

u8 rxbufsht31[6];
u8 crc1=0;
u8 crc2=0;
uint8_t tem = 0;
uint8_t hum = 0;


u8 Get_Crc8(u8 *ptr,u16 len)
{
	u8 crc;
	u8 i;
	crc=0;
	while(len--)
	{
		crc^=*ptr++;
		for(i=0;i<8;i++)
		{
			if(crc&0x01)crc=(crc>>1)^0x8C;
			else crc >>= 1;
		}
	}
	return crc;
}
void Cmd_Write_sht31(uint8_t msb,uint8_t lsb)
{
  IIC_Start();                  	//起始信号
  IIC_Send_Byte(0x88+0);   				//发送设备地址+写信号
	while(IIC_Wait_Ack());					//从机应答

  IIC_Send_Byte(msb);    					//发送命令
	while(IIC_Wait_Ack());

	IIC_Send_Byte(lsb);    					//发送命令
	while(IIC_Wait_Ack());

  IIC_Stop();                   	//发送停止信号
	delay_ms(5);
}


/*传感器将首先发送温度值，然后发送相对湿度值。在收到湿度值的校验和后，就应该发送一个NACK和停止条件*/
void Read_sht31(void)
{   	
	u8 BUFt[2]={0};
	u8 BUFh[2]={0};
		u8 i;
		Cmd_Write_sht31(0x21,0x26); 	//数据采集频率1 mps，周期性数据采集模式的测量命令
		IIC_Start();   	//起始信号
    IIC_Send_Byte(0x88+1);        //发送设备地址+读信号
		while(IIC_Wait_Ack());
		delay_us(5);
		for(i=0;i<6;i++)
		{
			
			if(i==5)*(rxbufsht31+i)=IIC_Read_Byte(0);	//读取湿度校验后发送NACK
			else *(rxbufsht31+i)=IIC_Read_Byte(1);		//读取并发送ACK
		}
	
    IIC_Stop();                          				//发送停止信号
		BUFt[0]=rxbufsht31[0];  										//存入温度数据
		BUFt[1]=rxbufsht31[1];  
	
		BUFh[0]=rxbufsht31[3];  										//存入湿度数据
		BUFh[1]=rxbufsht31[4];  
		
		tem=175*(BUFt[0]*256+BUFt[1])/65535-45; //摄氏度
		hum=100*(BUFh[0]*256+BUFh[1])/65535;
		BUFt[0]=0;
		BUFt[1]=0;
		BUFh[0]=0;
		BUFh[1]=0;
}
void Sht31_Updata()
{
	Data_set(tem_data,tem);
	Data_set(hum_data,hum);
	mcu_dp_value_update(DPID_TEMP_CURRENT,(unsigned long)tem*10); //VALUE型数据上报;
  mcu_dp_value_update(DPID_HUMIDITY_VALUE,(unsigned long)hum); //VALUE型数据上报;
}

void Sht31_Init(void)
{
	IIC_Init();//初始化IIC
}

