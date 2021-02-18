

/*
//�������ҳ�Ʒ
//����ϵ�п�����Ӧ�ó���
//��ע΢�Ź��ںţ����ҵ���
//���ҿ������������� www.DoYoung.net/YT 
//������ѿ����н�ѧ��Ƶ�����ؼ������ϣ�������������
//�������ݾ��� ����������ҳ www.doyoung.net
*/

/*
���޸���־��
1- ������


*/

#include "tim.h"
#include "logic.h"
#include "ble.h"
#include "03wtc.h"
#include "wifi.h"
//��ʱ��ʱ����㹫ʽTout = ((��װ��ֵ+1)*(Ԥ��Ƶϵ��+1))/ʱ��Ƶ��;
//���磺1�붨ʱ����װ��ֵ=9999��Ԥ��Ƶϵ��=7199

void TIM3_Init(u16 arr,u16 psc){  //TIM3 ��ʼ�� arr��װ��ֵ pscԤ��Ƶϵ��
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ��TIM3ʱ��
  
    TIM_TimeBaseInitStrue.TIM_Period=arr; //�����Զ���װ��ֵ
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //�������������
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�ӵķ�Ƶ���ӣ�����һ������ʱ���ã�һ����ΪTIM_CKD_DIV1
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue); //TIM3��ʼ������
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//ʹ��TIM3�ж�    
    TIM_Cmd(TIM3,ENABLE); //ʹ��TIM3
}

void TIM4_Init(u16 arr,u16 psc){  //TIM4 ��ʼ�� arr��װ��ֵ pscԤ��Ƶϵ��
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//ʹ��TIM4ʱ��
  
    TIM_TimeBaseInitStrue.TIM_Period=arr; //�����Զ���װ��ֵ
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //�������������
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�ӵķ�Ƶ���ӣ�����һ������ʱ���ã�һ����ΪTIM_CKD_DIV1
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStrue); //TIM4��ʼ������
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//ʹ��TIM4�ж�    
    TIM_Cmd(TIM4,ENABLE); //ʹ��TIM4
}
void TIM3_IRQHandler(void){ //TIM3�жϴ�����
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){	//�ж��Ƿ���TIM3�ж�
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			if(All.Lock_State == 1)//������
			{
				All.Lock_time ++;
				if(All.Lock_time >= Lock_time_Set)
				{
					All.Lock_time = Lock_time_Set;
					PIC_Set(8);//����Ϊ����
				}
			}
			
			All.Ble_time ++;
			if(All.Ble_time >= Ble_time_Set)
			{
				All.Ble_time = Ble_time_Set;
				Icon_set(ble_icon,1);//�����Ͽ�
			}
			else
				Icon_set(ble_icon,0);//��������
    }
}
void TIM4_IRQHandler(void){ //TIM4�жϴ�����
	static u8 rtc_time = 0;
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){	//�ж��Ƿ���TIM3�ж�
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
			Wifi_Ble_Show();//����wifi�������豸���
			if(rtc_time >= 100)
			{
				rtc_time = 100;//��δ������һֱ���
				if(mcu_get_wifi_work_state() == WIFI_CONNECTED)//������������
				{
					mcu_get_system_time();//����һ��ʱ������
					rtc_time = 0;//��ȡ�ɹ� ��ʱ����
				}
			}
			rtc_time++;//��ʱ�ۼ�
    }
}

