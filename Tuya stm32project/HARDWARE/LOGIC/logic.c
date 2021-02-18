#include "logic.h"
#include "03wtc.h"
#include "delay.h"
#include "wifi.h"
#include "HZK.h"
#define V_Standard 3.7 //基准电压
#define a 0.2 //0 到 1
u8 value = 0;
/*******************应用层*******************/
/** 
* @brief  设备联动 灯开关
* @param  
* @ref 
* @return 
* - 
* @details  
* @see  
*/ 
void LED_config()
{
	if(All.Led_State == 0)//由灭变亮
	{
		All.Led_State = 1;
		Icon_set(LED_Set,1);
		mcu_dp_bool_update(DPID_SWITCH,1);
	}
	else//由亮变灭
	{
		All.Led_State = 0;
		Icon_set(LED_Set,0);
		mcu_dp_bool_update(DPID_SWITCH,0);
	}
	
}
/** 
* @brief  屏保开关控制函数
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
* @brief  亮度控制开关函数
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
* @brief  备忘控制1
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
* @brief  获取天气图标
* @param  
* @ref 
* @return 
* - 
* @details  
* @see  
*/ 
void Weather_ICON(u8 Weather_ID)
{
	u8 weather_icon = 0;//NA图标的位置
	switch(Weather_ID)
	{
		case 0 ... 1://0 暴雪 图标
			weather_icon = 0;
			break;
		
		case 2 ... 8://1 暴雨 
			weather_icon = 1;
			break;
		
		case 9://4 多云
			weather_icon = 4;
			break;
		
		case 10 ... 11://6 浮尘
			weather_icon = 6;
			break;
		
		case 12://7 雷阵雨
			weather_icon = 7;
		break;
		
		case 13 ... 14://8 晴
			weather_icon = 8;
		break;
		
		case 15 ... 16://9 闪电
			weather_icon = 9;
		break;
		
		case 17://10 少云
			weather_icon = 10;
		break;
		
		case 18 ... 19://12 特大扬沙
			weather_icon = 12;
		break;
		
		case 20 ... 21://17 雾
			weather_icon = 17;
		break;
		
		case 22 ... 25://18 小雨
			weather_icon = 18; 
		break;
		
		case 26 ... 27://19 扬沙
			weather_icon = 19;
		break;
		
		case 28://20 阴
			weather_icon = 20;
		break;
		
		case 29://21 雨夹雪
			weather_icon = 21;
		break;
		
		case 30 ... 32://22 阵雨
			weather_icon = 22;
		break;
		
		case 33 ... 38://23 中雪
			weather_icon = 23;
		break;
		
		default://其他 NA图标
			weather_icon = 22;
		break;
	}
	Icon_set(wea_icon,weather_icon);//显示图标
}
/** 
* @brief  天气部分整体更新
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
* @brief  键值回调函数
* @param  
* @ref Add 变量地址
* @ref Key_ID 按键ID
* @return none
* - 
* @details  
* @see  
*/ 
void Key_ID_Execute(u16 Add,u16 Key_ID)
{
	switch(Add)
	{
		case LED_ADD://设备联动-灯
			LED_config();break;
		case Lock_ADD://屏保
			Lock_config();break;
		case Light_ADD://自动亮度
			Light_config();break;
		case Notes1_ADD://备忘1
			Notes1_config();break;
		case Notes2_ADD://备忘2
			Notes2_config();break;
		case Notes3_ADD://备忘3
			Notes3_config();break;
		case Notes4_ADD://备忘4
			Notes4_config();break;
		case WIFI_IN_ADD://进入SMART配网
			mcu_set_wifi_mode(SMART_CONFIG);break;
		case WIFI_OUT_ADD://重置WIFI退出配网
			mcu_reset_wifi();break;
		case Lock_Pic_ADD://屏保界面按键
			break;
	}
	All.Lock_time = 0;//清除锁屏累计时间
}
/** 
* @brief  备忘设置
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
* @brief  电池电量显示
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
* @brief  自动亮度
* @param  自动亮度函数
* @ref 
* @return 
* - 
* @details 0x08a7 -- 0xc4d -- 0xfd9  2215 -- 3149 -- 4057
* @see  
*/ 
void auto_light()
{
	float lx = (ADC_DMA_IN[0] - 2000) / 25.0;//流明 2uA 对应 1lx
	
	if(lx != 0)
	{
		value = filter(lx);
		LED_Config(value,value-5,100);
	}
}
void Wifi_Ble_Show()
{
	//WIFI连接情况
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
* @brief  一阶滞后滤波法
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


	