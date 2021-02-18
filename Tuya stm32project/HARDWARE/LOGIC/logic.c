#include "logic.h"
#include "03wtc.h"
#include "delay.h"
#include "wifi.h"
#include "HZK.h"
#define V_Standard 3.7 //��׼��ѹ
#define a 0.2 //0 �� 1
u8 value = 0;
/*******************Ӧ�ò�*******************/
/** 
* @brief  �豸���� �ƿ���
* @param  
* @ref 
* @return 
* - 
* @details  
* @see  
*/ 
void LED_config()
{
	if(All.Led_State == 0)//�������
	{
		All.Led_State = 1;
		Icon_set(LED_Set,1);
		mcu_dp_bool_update(DPID_SWITCH,1);
	}
	else//��������
	{
		All.Led_State = 0;
		Icon_set(LED_Set,0);
		mcu_dp_bool_update(DPID_SWITCH,0);
	}
	
}
/** 
* @brief  �������ؿ��ƺ���
* @param  
* @ref 
* @return 
* - 
* @details  
* @see  
*/ 
void Lock_config()
{
	if(All.Lock_State == 0)
	{
		All.Lock_State = 1;
		Icon_set(Lock_Set,1);
		mcu_dp_bool_update(DPID_SCREEN,1);
	}
	else
	{
		All.Lock_State = 0;
		Icon_set(Lock_Set,0);
		mcu_dp_bool_update(DPID_SCREEN,0);
	}
}
/** 
* @brief  ���ȿ��ƿ��غ���
* @param  
* @ref 
* @return 
* - 
* @details  
* @see  
*/ 
void Light_config()
{
	if(All.Light_State == 0)
	{
		All.Light_State = 1;
		Icon_set(Light_Set,1);
	}
	else
	{
		All.Light_State = 0;
		Icon_set(Light_Set,0);
	}
}
/** 
* @brief  ��������1
* @param  
* @ref 
* @return 
* - 
* @details  
* @see  
*/ 
void Notes1_config()
{
	static bool status = 0;
	if(status == 0)
	{
		status = 1;
		Icon_set(Notes1_Icon,1);
	}
	else
	{
		status = 0;
		Icon_set(Notes1_Icon,0);
	}
}

void Notes2_config()
{
	static bool status = 0;
	if(status == 0)
	{
		status = 1;
		Icon_set(Notes2_Icon,1);
	}
	else
	{
		status = 0;
		Icon_set(Notes2_Icon,0);
	}
}

void Notes3_config()
{
	static bool status = 0;
	if(status == 0)
	{
		status = 1;
		Icon_set(Notes3_Icon,1);
	}
	else
	{
		status = 0;
		Icon_set(Notes3_Icon,0);
	}
}

void Notes4_config()
{
	static bool status = 0;
	if(status == 0)
	{
		status = 1;
		Icon_set(Notes4_Icon,1);
	}
	else
	{
		status = 0;
		Icon_set(Notes4_Icon,0);
	}
}
/** 
* @brief  ��ȡ����ͼ��
* @param  
* @ref 
* @return 
* - 
* @details  
* @see  
*/ 
void Weather_ICON(u8 Weather_ID)
{
	u8 weather_icon = 0;//NAͼ���λ��
	switch(Weather_ID)
	{
		case 0 ... 1://0 ��ѩ ͼ��
			weather_icon = 0;
			break;
		
		case 2 ... 8://1 ���� 
			weather_icon = 1;
			break;
		
		case 9://4 ����
			weather_icon = 4;
			break;
		
		case 10 ... 11://6 ����
			weather_icon = 6;
			break;
		
		case 12://7 ������
			weather_icon = 7;
		break;
		
		case 13 ... 14://8 ��
			weather_icon = 8;
		break;
		
		case 15 ... 16://9 ����
			weather_icon = 9;
		break;
		
		case 17://10 ����
			weather_icon = 10;
		break;
		
		case 18 ... 19://12 �ش���ɳ
			weather_icon = 12;
		break;
		
		case 20 ... 21://17 ��
			weather_icon = 17;
		break;
		
		case 22 ... 25://18 С��
			weather_icon = 18; 
		break;
		
		case 26 ... 27://19 ��ɳ
			weather_icon = 19;
		break;
		
		case 28://20 ��
			weather_icon = 20;
		break;
		
		case 29://21 ���ѩ
			weather_icon = 21;
		break;
		
		case 30 ... 32://22 ����
			weather_icon = 22;
		break;
		
		case 33 ... 38://23 ��ѩ
			weather_icon = 23;
		break;
		
		default://���� NAͼ��
			weather_icon = 22;
		break;
	}
	Icon_set(wea_icon,weather_icon);//��ʾͼ��
}
/** 
* @brief  ���������������
* @param  
* @ref 
* @return 
* - 
* @details  
* @see  
*/ 
void Weather_show(u8 Weather_ID)
{
	Weather_ICON(Weather_ID);
	Chinese_Text(CZK_text,weather_HZK_sheet[Weather_ID],8);
}
/** 
* @brief  ��ֵ�ص�����
* @param  
* @ref Add ������ַ
* @ref Key_ID ����ID
* @return none
* - 
* @details  
* @see  
*/ 
void Key_ID_Execute(u16 Add,u16 Key_ID)
{
	switch(Add)
	{
		case LED_ADD://�豸����-��
			LED_config();break;
		case Lock_ADD://����
			Lock_config();break;
		case Light_ADD://�Զ�����
			Light_config();break;
		case Notes1_ADD://����1
			Notes1_config();break;
		case Notes2_ADD://����2
			Notes2_config();break;
		case Notes3_ADD://����3
			Notes3_config();break;
		case Notes4_ADD://����4
			Notes4_config();break;
		case WIFI_IN_ADD://����SMART����
			mcu_set_wifi_mode(SMART_CONFIG);break;
		case WIFI_OUT_ADD://����WIFI�˳�����
			mcu_reset_wifi();break;
		case Lock_Pic_ADD://�������水��
			break;
	}
	All.Lock_time = 0;//��������ۼ�ʱ��
}
/** 
* @brief  ��������
* @param  
* @ref 
* @return 
* - 
* @details  
* @see  
*/ 
void Notes_Data(u8 ID,u8 *Data,u8 len)
{
	u8 i = 0;
	u8 Notes[50] = {0};
	for(i=0;i < len;i++)
	{
		Notes[i] = Data[i];
	}
	switch(ID)
	{
		case 1:
			Chinese_Text(Notes1_ADD,(char*)Notes,50);
		break;
		case 2:
			Chinese_Text(Notes2_ADD,(char*)Notes,50);
		break;
		case 3:
			Chinese_Text(Notes3_ADD,(char*)Notes,50);
		break;
		case 4:
			Chinese_Text(Notes4_ADD,(char*)Notes,50);
		break;
	}
	
}
/** 
* @brief  ��ص�����ʾ
* @param  
* @ref 
* @return 
* - 
* @details  2.7 - 4.2
* @see  
*/ 
void BAT_Show(void)
{
	float Bat_V = ADC_DMA_IN[1] / 4096.0 *3.3*2;
	u8 icon = 0;
	//Bat_V = filter(Bat_V);
	if(Bat_V < V_Standard)
		icon = 0;
	else if(Bat_V >= V_Standard && Bat_V < V_Standard+0.1)
		icon = 1;
	else if(Bat_V >= V_Standard+0.1 && Bat_V < V_Standard+0.2)
		icon = 2;
	else if(Bat_V >= V_Standard+0.2 && Bat_V < V_Standard+0.3)
		icon = 3;
	else if(Bat_V >= V_Standard+0.3 && Bat_V < V_Standard+0.4)
		icon = 4;
	else 
		icon = 5;
	
	Icon_set(bat_icon,icon);
}
/** 
* @brief  �Զ�����
* @param  �Զ����Ⱥ���
* @ref 
* @return 
* - 
* @details 0x08a7 -- 0xc4d -- 0xfd9  2215 -- 3149 -- 4057
* @see  
*/ 
void auto_light()
{
	float lx = (ADC_DMA_IN[0] - 2000) / 25.0;//���� 2uA ��Ӧ 1lx
	
	if(lx != 0)
	{
		value = filter(lx);
		LED_Config(value,value-5,100);
	}
}
void Wifi_Ble_Show()
{
	//WIFI�������
	switch (mcu_get_wifi_work_state())
  {
    case SMART_CONFIG_STATE:  //0x00
			Icon_set(wifi_icon,1);
      break;
    case AP_STATE:  //0x01
			Icon_set(wifi_icon,1);
      break;

    case WIFI_NOT_CONNECTED:  // 0x02
			Icon_set(wifi_icon,1);
      break;

    default:Icon_set(wifi_icon,0);
  }
	
}

/** 
* @brief  һ���ͺ��˲���
* @param  
* @ref 
* @return 
* - 
* @details  
* @see  
*/ 
u8 filter(u8 new_value)
{
	
	return (1-a)*value + a*new_value;
}


	