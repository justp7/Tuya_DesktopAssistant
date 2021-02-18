

/*
//杜洋工作室出品
//洋桃系列开发板应用程序
//关注微信公众号：洋桃电子
//洋桃开发板资料下载 www.DoYoung.net/YT 
//即可免费看所有教学视频，下载技术资料，技术疑难提问
//更多内容尽在 杜洋工作室主页 www.doyoung.net
*/

/*
《修改日志》
1- 创建。


*/

#include "tim.h"
#include "logic.h"
#include "ble.h"
#include "03wtc.h"
#include "wifi.h"
//定时器时间计算公式Tout = ((重装载值+1)*(预分频系数+1))/时钟频率;
//例如：1秒定时，重装载值=9999，预分频系数=7199

void TIM3_Init(u16 arr,u16 psc){  //TIM3 初始化 arr重装载值 psc预分频系数
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM3时钟
  
    TIM_TimeBaseInitStrue.TIM_Period=arr; //设置自动重装载值
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //预分频系数
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //计数器向上溢出
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //时钟的分频因子，起到了一点点的延时作用，一般设为TIM_CKD_DIV1
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue); //TIM3初始化设置
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//使能TIM3中断    
    TIM_Cmd(TIM3,ENABLE); //使能TIM3
}

void TIM4_Init(u16 arr,u16 psc){  //TIM4 初始化 arr重装载值 psc预分频系数
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//使能TIM4时钟
  
    TIM_TimeBaseInitStrue.TIM_Period=arr; //设置自动重装载值
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //预分频系数
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //计数器向上溢出
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //时钟的分频因子，起到了一点点的延时作用，一般设为TIM_CKD_DIV1
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStrue); //TIM4初始化设置
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//使能TIM4中断    
    TIM_Cmd(TIM4,ENABLE); //使能TIM4
}
void TIM3_IRQHandler(void){ //TIM3中断处理函数
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){	//判断是否是TIM3中断
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			if(All.Lock_State == 1)//屏保打开
			{
				All.Lock_time ++;
				if(All.Lock_time >= Lock_time_Set)
				{
					All.Lock_time = Lock_time_Set;
					PIC_Set(8);//设置为锁屏
				}
			}
			
			All.Ble_time ++;
			if(All.Ble_time >= Ble_time_Set)
			{
				All.Ble_time = Ble_time_Set;
				Icon_set(ble_icon,1);//蓝牙断开
			}
			else
				Icon_set(ble_icon,0);//蓝牙链接
    }
}
void TIM4_IRQHandler(void){ //TIM4中断处理函数
	static u8 rtc_time = 0;
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){	//判断是否是TIM3中断
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
			Wifi_Ble_Show();//更新wifi和蓝牙设备情况
			if(rtc_time >= 100)
			{
				rtc_time = 100;//若未联网则一直监测
				if(mcu_get_wifi_work_state() == WIFI_CONNECTED)//网络正常连接
				{
					mcu_get_system_time();//发起一次时间请求
					rtc_time = 0;//获取成功 计时清零
				}
			}
			rtc_time++;//计时累加
    }
}

