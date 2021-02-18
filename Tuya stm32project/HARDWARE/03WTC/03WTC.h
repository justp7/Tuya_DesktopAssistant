#ifndef __03WTC_H
#define __03WTC_H

#include "sys.h"
#include <stdbool.h>
struct  Status_config
{
	bool Lock_State;//������־
	bool Light_State;//�Զ�����
	bool Led_State;//������
	u8 Lock_time;
	u8 Ble_time;
};

extern struct Status_config All;
//���崮�������Ͷ˿�
#define USART_SEND_n		USART3
//�궨��
#define Write 0x82
#define Read  0x83
//��ַ����
#define wea_icon 0x5000   //����ͼ��
#define ble_icon 0x5001   //����ͼ��
#define wifi_icon 0x5002   //����ͼ��
#define bat_icon 0x5003   //���ͼ��
#define spin_icon 0x5018   //ָ��ͼ��

#define tem_data 0x5004   //�¶�����
#define hum_data 0x5006   //ʪ������
#define wea_tem 0x5008   //�����¶�
#define wea_hum 0x500A   //����ʪ��
#define wea_pm25 0x500C   //����pm2.5
#define up_data 0x5010   //�ϴ�����
#define down_data 0x5014   //��������

#define up_text 0x5020   //�ϴ�����
#define down_text 0x5024   //��������
#define CZK_text 0x5030   //��������

#define CPU_data 0x5042 //CPU����
/*�����ص���ַ*/
#define LED_ADD 0x5020 //��ֵ
#define WIFI_IN_ADD 0x5050 //��������
#define WIFI_OUT_ADD 0x5051//�˳�����
#define Lock_ADD 0x5044		 //������ַ
#define Light_ADD 0x5045	 //�����Զ�����
#define Lock_Pic_ADD 0x5043 //����

/*��������ͼ���ַ*/
#define LED_Set  0x5019 //���ܵ�ͼ��
#define Lock_Set 0x5040 //��������ͼ��
#define Light_Set 0x5041 //�Զ����ȿ���

/*����ҳ��*/
#define Notes1_Icon 0x5100 //����1ͼ��
#define Notes1_ADD  0x5101
#define Notes1_Text 0x5102

#define Notes2_Icon 0x5200
#define Notes2_ADD  0x5201
#define Notes2_Text 0x5202

#define Notes3_Icon 0x5300
#define Notes3_ADD  0x5301
#define Notes3_Text 0x5302

#define Notes4_Icon 0x5400
#define Notes4_ADD  0x5401
#define Notes4_Text 0x5402

#define Lock_time_Set 20 // ������ʱ
#define Ble_time_Set 10 // �������Ӽ�ʱ

void Weather_ICON(u8 Weather_ID);
void Weather_show(u8 Weather_ID);
//�ϲ�
void Icon_Rotate(u16 Add,u16 Angle);//ͼ����ת��ʾ
void Key_ID_Execute(u16 Add,u16 Key_ID);//��ֵ������
void Curve_set(u16 num);//ʵʱ����
void Text_set(u16 Add,char *Text,u8 len);//�ı���ʾ
void Chinese_Text(u16 Add,char *Text,u8 len);//�����ı���ʾ
void Data_set(u16 Add,u16 Data);//���ݱ���
void Icon_set(u16 Add,u16 ID);//����ͼ��
void LED_Config(u8 on_light,u8 off_light,u16 time);//�������ȵ���
void PIC_Set(u16 ID);//����ͼƬ�л�
void RTC_SET(u8 year, u8 month, u8 day, u8 week, u8 hour, u8 min, u8 sec);//дRTC�Ĵ���

//�²�
void Recieve_Data(u8 *Data);//���ݽ���
void Write_register(u16 Add,u8 len,u8 *data);//д�Ĵ���
void data_pack(u8 len,u8 order,u8 *data);//���ݴ��
void send_pack(u8 len,u8 *buffer);//��������

#endif

