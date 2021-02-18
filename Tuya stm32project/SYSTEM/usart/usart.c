
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
1-201708271933 ����������ʱ������


*/

#include "sys.h"
#include "stdbool.h"
#include "usart.h"
#include "mcu_api.h"//Ϳѻ
#include "ble.h"//����
#include "03WTC.h"//������
#include "logic.h"
//ʹUASRT���ڿ���printf��������
//��usart.h�ļ���ɸ���ʹ��printf�����Ĵ��ں�	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE {
	int handle; 
}; 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x){ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f){
	//�����һ���ַ���ʧ
	static char flage=0;
	if(!flage)
	{
		flage=1;
		USART_ClearITPendingBit(USART_n,USART_IT_TC);//���printf��ʧ��һ���ֽڵ�����
	}	
		
	while((USART_n->SR&0X40)==0);//ѭ������,ֱ���������   
    USART_n->DR = (u8) ch;      
	return ch;
}
#endif 


/*
USART1������س���
*/
 
#if EN_USART1   //USART1ʹ��������ѡ��
u8 USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u8 buf1_size = 0;//�������ݽ����������
bool data1_change = 0;//���ڽ������/�仯��־λ

/*
USART1ר�õ�printf����
��ͬʱ����2�����ϴ���ʱ��printf����ֻ����������֮һ����������Ҫ�Դ�������printf����
���÷�����USART1_printf("123"); //��USART2�����ַ�123
*/
void USART1_printf (char *fmt, ...){ 
	char buffer[USART1_REC_LEN+1];  // ���ݳ���
	u8 i = 0;	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, USART1_REC_LEN+1, fmt, arg_ptr);
	while ((i < USART1_REC_LEN) && (i < strlen(buffer))){
        USART_SendData(USART1, (u8) buffer[i++]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); //������ɱ�־λ
	}
	va_end(arg_ptr);
}

void USART1_Init(u32 bound){ //����1��ʼ��������
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;//GPIO
	USART_InitTypeDef USART_InitStructure;//USART
	 //ʹ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
   //USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure); //GPIO��ʼ�� 
	 //USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure); //GPIO��ʼ�� 

   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure); //���ڳ�ʼ��
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//����ENABLE/�ر�DISABLE�ж�
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//�������ڿ����ж� 
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
}

void USART1_IRQHandler(void){ //����1�жϷ�����򣨹̶��ĺ����������޸ģ�	
		u8 clear = clear;
    USART_ClearFlag(USART1,USART_FLAG_TC);
    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=Bit_RESET)//�����жϷ���        
    {
        if(data1_change == 0)//���½���
        {
            memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));//���������������
            data1_change = 1;//��־λ����
        }
        
        USART1_RX_BUF[buf1_size++]=USART1->DR;
    }
         
    else if(USART_GetFlagStatus(USART1,USART_FLAG_IDLE)!=Bit_RESET)//�����жϷ���
    {                    
        clear = USART1->SR;
        clear = USART1->DR;  
			All.Ble_time = 0;///����������Ӽ�ʱ      
			switch(USART1_RX_BUF[0])
			{
				case 0x7B://{
					PC_Data(USART1_RX_BUF);//PC �������ݽ���
				break;
				case 0x31://����1
					Notes_Data(1,&USART1_RX_BUF[1],buf1_size - 2);
					break;
				case 0x32://����2
					Notes_Data(2,&USART1_RX_BUF[1],buf1_size - 2);
					break;
				case 0x33://����3
					Notes_Data(3,&USART1_RX_BUF[1],buf1_size - 2);
					break;
				case 0x34://����4
					Notes_Data(4,&USART1_RX_BUF[1],buf1_size - 2);
					break;
			}
				
        buf1_size = 0;
        data1_change = 0;//��־λ���ͣ��´����ݸı����
    }
} 
#endif	

/*
USART2������س���
*/
#if EN_USART2   //USART2ʹ��������ѡ��
u8 USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART2_RX_STA=0;       //����״̬���	  

/*
USART2ר�õ�printf����
��ͬʱ����2�����ϴ���ʱ��printf����ֻ����������֮һ����������Ҫ�Դ�������printf����
���÷�����USART2_printf("123"); //��USART2�����ַ�123
*/
void USART2_printf (char *fmt, ...){ 
	char buffer[USART2_REC_LEN+1];  // ���ݳ���
	u8 i = 0;	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, USART2_REC_LEN+1, fmt, arg_ptr);
	while ((i < USART2_REC_LEN) && (i < strlen(buffer))){
		USART_SendData(USART2, (u8) buffer[i++]);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); 
	}
	va_end(arg_ptr);
}


void USART2_Init(u32 bound){ //����1��ʼ��������
    //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
		 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); //ʹ��UART2����GPIOA��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //ʹ�ܴ��ڵ�RCCʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //����USART2��RX�ӿ���PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //����USART2��TX�ӿ���PA2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
   //USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART2, &USART_InitStructure); //��ʼ������
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//����ENABLE/�ر�DISABLE�ж�
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
}

void USART2_IRQHandler(void){ //����2�жϷ�����򣨹̶��ĺ����������޸ģ�	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //Ϳѻ���� �����жϵ�ʵ��
	{
		uart_receive_input(USART_ReceiveData(USART2));//�����ݴ��䵽Tuya�ӿ�  
		USART_ClearFlag(USART2,USART_FLAG_TC);
	}
} 
#endif	


#if EN_USART3   //���ʹ���˽���

u8 USART3_RX_BUF[USART3_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 buf3_size = 0;//�������ݽ����������
bool data3_change = 0;//���ڽ������/�仯��־λ

/*
USART3ר�õ�printf����
��ͬʱ����2�����ϴ���ʱ��printf����ֻ����������֮һ����������Ҫ�Դ�������printf����
���÷�����USART3_printf("123"); //��USART3�����ַ�123
*/
void USART3_printf (char *fmt, ...){ 
	char buffer[USART3_REC_LEN+1];  // ���ݳ���
	u8 i = 0;	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, USART3_REC_LEN+1, fmt, arg_ptr);
	while ((i < USART3_REC_LEN) && (i < strlen(buffer))){
        USART_SendData(USART3, (u8) buffer[i++]);
        while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET); 
	}
	va_end(arg_ptr);
}

void USART3_Init(u32 BaudRate){ //USART3��ʼ��������
   GPIO_InitTypeDef GPIO_InitStructure;
   USART_InitTypeDef USART_InitStructure;

   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); //ʹ��UART3����GPIOB��ʱ��
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //ʹ�ܴ��ڵ�RCCʱ��

   //����ʹ�õ�GPIO������
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//����USART3��RX�ӿ���PB11
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//�ӿ�ģʽ ��������
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//����USART3��TX�ӿ���PB10
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����ٶ�50MHz
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�ӿ�ģʽ �����������
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   //���ô���
   USART_InitStructure.USART_BaudRate = BaudRate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
   USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
   USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

   USART_Init(USART3, &USART_InitStructure);//���ô���3
   USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//����ENABLE/�ر�DISABLE���ڽ����ж�
	 USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//�������ڿ����ж� 
   //USART_ITConfig(USART3, USART_IT_TXE, ENABLE);//���ڷ����ж��ڷ�������ʱ����
   USART_Cmd(USART3, ENABLE);//ʹ�ܴ���3
}

//����3�жϷ�����򣨹̶��ĺ����������޸ģ�
//���÷�����if(USART3_RX_STA&0xC000){ �������ݴ������ }//��־λ��0xC000��ʾ�յ����ݴ���ɡ�
void USART3_IRQHandler(void){ 	
		u8 clear = clear;
    USART_ClearFlag(USART3,USART_FLAG_TC);
    if(USART_GetITStatus(USART3,USART_IT_RXNE)!=Bit_RESET)//�����жϷ���        
    {
        if(data3_change == 0)//���½���
        {
            memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));//���������������
            data3_change = 1;//��־λ����
        }
        
        USART3_RX_BUF[buf3_size++]=USART3->DR;
    }
         
    else if(USART_GetFlagStatus(USART3,USART_FLAG_IDLE)!=Bit_RESET)//�����жϷ���
    {                    
        clear = USART3->SR;
        clear = USART3->DR;
				if(USART3_RX_BUF[3] == 0x83)
					Recieve_Data(USART3_RX_BUF);//���������ݽ�������
        buf3_size = 0;
        data3_change = 0;//��־λ���ͣ��´����ݸı����
    }
} 
#endif	




/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/

/*
a���ŵ����ã�

%d ʮ�����з�������
%u ʮ�����޷�������
%f ������
%s �ַ���
%c �����ַ�
%p ָ���ֵ
%e ָ����ʽ�ĸ�����
%x, %X �޷�����ʮ�����Ʊ�ʾ������
%o �޷����԰˽��Ʊ�ʾ������
%g �Զ�ѡ����ʵı�ʾ��
%p �����ַ��

*/

