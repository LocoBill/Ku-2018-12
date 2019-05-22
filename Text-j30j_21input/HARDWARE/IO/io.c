#include "io.h"
#include "delay.h"


void io_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PA.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PA.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;				 //LED0-->PA.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOG, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //LED0-->PA.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	
	att_c0 = 0;
	att_c1 = 0;
	att_c2 = 0;
	att_c3 = 0;
	att_c4 = 0;
	att_c5 = 0;
	att_c6 = 0;
	
//	lo_lock= 1;
	
	fc_0 = 0;
	fc_1 = 0;
	fc_2 = 0;
	fc_3 = 0;
	fc_4 = 0;
	
	work_m1 = 0;
	work_m2 = 0;
	work_m3 = 0;
	work_m4 = 0;
	
}

