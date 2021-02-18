#include "03WTC.h"
#include "usart.h"
#include "stdbool.h"
#include "stdio.h"

#include "wifi.h"

struct Status_config All;
/*******************������*******************/
/** 
* @brief  ͼ����ת
* @param  
* @ref Add ������ַ
* @ref Angle ��ת�ĽǶ�
* @return none
* - 
* @details  
* @see  
*/ 
void Icon_Rotate(u16 Add,u16 Angle)
{
	u8 data[2];
	//�л���ͼ��ID
	data[0] = (Angle & 0xff00)>> 8;//ͼ��ID
	data[1] = Angle & 0x00ff;
	
	Write_register(Add,2,data);//���ݴ������
}

/** 
* @brief  �����ı���ʾ
* @param  
* @ref Add ������ַ
* @ref Text �ı�����
* @ref len �ı�����
* @return none
* - 
* @details  
* @see  
*/ 
void Chinese_Text(u16 Add,char *Text,u8 len)
{
	u8 data[50] = {0x20};
	u8 i = 0;
	//�ı��������
	for(i= 0;i < len;i++)
		data[i] = (u8)Text[i];
		
	Write_register(Add,len,data);//���ݴ������
}
/** 
* @brief  ʵʱ����
* @param  
* @ref Data ����
* @return none
* - 
* @details  
* @see  
*/ 
void Curve_set(u16 num)
{
	u8 data[10];
	//��������
	data[0] = 0x03;
	data[1] = 0x10;
	data[2] = 0x5A;
	data[3] = 0xA5;
	//ͨ����
	data[4] = 0x01;
  data[5] = 0x00;
	//ѡ��ͨ��
	data[6] = 0x00;
	//�����ֳ���
	data[7] = 0x01;
	//�������
	data[8] = (num & 0xff00)>>8;
	data[9] = num & 0x00ff;
	
	data_pack(10,Write,data);//���ݴ������
}
/** 
* @brief  �ı���ʾ
* @param  
* @ref Add ������ַ
* @ref Text �ı�����
* @ref len �ı�����
* @return none
* - 
* @details  
* @see  
*/ 
void Text_set(u16 Add,char *Text,u8 len)
{
	u8 data[10];
	u8 i = 0;
	//�ı��������
	for(i= 0;i < len;i++)
		data[i] = (u8)Text[i];
		
	Write_register(Add,len,data);//���ݴ������
}
/** 
* @brief  ���ݱ���
* @param  
* @ref Add ������ַ
* @ref Data �������ݣ�-32768 - 32767��
* @return none
* - 
* @details  
* @see  
*/ 
void Data_set(u16 Add,u16 Data)
{
	u8 data[2];
	//�л���ͼ��ID
	data[0] = (Data & 0xff00)>> 8;//ͼ��ID
	data[1] = Data & 0x00ff;
	Write_register(Add,2,data);//���ݴ������
}
/** 
* @brief  ����ͼ��
* @param  
* @ref Add ͼ���ַ
* @ref ID ͼ��ID
* @return none
* - 
* @details  
* @see  
*/ 
void Icon_set(u16 Add,u16 ID)
{
	u8 data[2];
	//�л���ͼ��ID
	data[0] = (ID & 0xff00)>> 8;//ͼ��ID
	data[1] = ID & 0x00ff;
	Write_register(Add,2,data);//���ݴ������
}
/** 
* @brief  �������ȵ���
* @param  
* @ref on_light ��������
* @ref off_light �ر�����
* @ref time ����ʱ��/10mS
* @return none
* - 
* @details  
* @see  
*/ 
void LED_Config(u8 on_light,u8 off_light,u16 time)
{
	u8 data[4];
	
	data[0] = on_light;//��������
	data[1] = off_light;//�ر�����
	
	//����ʱ��/10mS
	data[2] = (time & 0xff00)>> 8;
	data[3] = time & 0x00ff;
	
	//0x0082 �������ȼĴ���
	Write_register(0x0082,4,data);//���ݴ������
}
/** 
* @brief  ����ͼƬ�л�
* @param  
* @ref ID Ҫ�л�����ͼƬID
* @return none
* - 
* @details  
* @see  
*/ 
void PIC_Set(u16 ID)
{
	u8 data[4];
	
	data[0] = 0x5A;//����һ��ҳ�洦��
	data[1] = 0x01;//ҳ���л�
	data[2] = (ID & 0xff00)>> 8;
	data[3] = ID & 0x00ff;
	
	//0x0084 ����ͼƬ��ַ
	Write_register(0x0084,4,data);//���ݴ������
}
/** 
* @brief  дRTC�Ĵ���
* @param  
* @ref year ��
* @ref week �ܼ�
* @return none
* - 
* @details  
* @see  
*/ 
void RTC_SET(u8 year, u8 month, u8 day, u8 week, u8 hour, u8 min, u8 sec)
{
	u8 data[8];
	
	data[0] = year; //�Ĵ�������
	data[1] = month;
	data[2] = day;
	data[3] = week;
	data[4] = hour;
	data[5] = min;
	data[6] = sec;
	data[7] = 0;
	
	//0x0010 RTC�Ĵ�����ַ
	Write_register(0x0010,8,data);//���ݴ������
}
/** 
* @brief  �������ݽ���
* @param  
* @ref Data ��������
* @return none
* - 1 �����ɹ�
* - 0 ����ʧ��
* @details  
* @see  
*/ 
void Recieve_Data(u8 *Data){
	u8 Len = 0;//���ݳ���
	u8 Data_len = 0;
	u16 Key_ID;
	u16 Add; 
	if(Data[0] == 0x5A && Data[1] == 0xA5)//֡ͷ���ճɹ�
	{
		Len = Data[2];
		if(Data[3] == 0x83 && Len != 0)//����ָ�� ���Ȳ�Ϊ0
		{
			Add = Data[4]<<8 | Data[5];//��ַ
			Data_len = Data[6];//�� ����
			if(Data_len != 0)
				Key_ID = Data[7]<<8 | Data[8];//���µļ�ֵ
			Key_ID_Execute(Add,Key_ID);//��ֵ������
		}
	}
}
/** 
* @brief  ���Ĵ���
* @param  
* @ref add ������ַ�������ֽڣ�
* @ref data ����(�����ֽ�)
* @return 
* - 
* @details  
* @see  
*/ 
void Read_register(u16 Add,u8 data)
{
	u8 pack_data[4];
	
	pack_data[0] = (Add & 0xff00)>> 8;//��ַ
	pack_data[1] = Add & 0x00ff;
	
	
	data_pack(5,Write,pack_data);
}

/** 
* @brief  д�Ĵ���
* @param  
* @ref add ������ַ�������ֽڣ�
* @ref len ���ݳ���
* @return 
* - 
* @details  
* @see  
*/ 
void Write_register(u16 add,u8 len,u8 *data)
{
	u8 pack_data[100];
	u8 i;
	//���ֽڵ�ַ
	pack_data[0] = (add & 0xff00)>> 8;
	pack_data[1] = add & 0x00ff;
	
	//ָ���������
	for(i = 0;i < len; i++)
	{
		pack_data[i+2] = data[i];
	}
	
	data_pack(len + 2,Write,pack_data);//���ݳ��� + ��ַ
}

/** 
* @brief  ���ݴ��
* @param  
* @ref len ���ݳ��� ��ָ��+����+У����ֽ�����
* @ref order ��/дָ��
* @ref data ����
* @return none
* - 
* @details  
* @see  
*/ 
void data_pack(u8 len,u8 order,u8 *data)
{
	u8 send_data[300];
	u8 i = 0;
	//֡ͷ ���� ���
	send_data[0] = 0x5A;
	send_data[1] = 0xA5;
	send_data[2] = len + 1;
	//�ж϶�д
	if(order == Write)
		send_data[3] = 0x82;
	else if(order == Read)
		send_data[3] = 0x83;
	//�������
	for(i = 0;i < len;i++)
		send_data[4+i] = data[i];
	
	send_pack(len + 4,send_data);//���ݷ���
	
}
/** 
* @brief  �������ݷ���
* @param  
* @ref len ���ݳ��� 
* @ref buffer Ҫ���͵�����
* @return 
* - 
* @details  
* @see  
*/ 
void send_pack(u8 len,u8 *buffer)
{
	u8 i = 0;
	
	while (i < len){
		USART_SendData(USART_SEND_n, (u8) buffer[i++]);
		while (USART_GetFlagStatus(USART_SEND_n, USART_FLAG_TXE) == RESET); //������ɱ�־λ
	}
}

