#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "io.h"
//ALIENTEKս��STM32������ʵ��4
//����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
u8 data[200] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void readdata()
{
	if(USART_RX_BUF[6] =='1') att_c0 = 1;		else att_c0 = 0;
	if(USART_RX_BUF[5] =='1') att_c1 = 1;		else att_c1 = 0;
	if(USART_RX_BUF[4] =='1') att_c2 = 1;		else att_c2 = 0;
	if(USART_RX_BUF[3] =='1') att_c3 = 1;		else att_c3 = 0;
	if(USART_RX_BUF[2] =='1') att_c4 = 1;		else att_c4 = 0;
	if(USART_RX_BUF[1] =='1') att_c5 = 1;		else att_c5 = 0;
	if(USART_RX_BUF[0] =='1') att_c6 = 1;		else att_c6 = 0;
	
	if(USART_RX_BUF[11] =='1') fc_0 = 1;		else  fc_0 = 0;
	if(USART_RX_BUF[10] =='1') fc_1 = 1;		else  fc_1 = 0;
	if(USART_RX_BUF[9] =='1') fc_2 = 1;			else  fc_2 = 0;
	if(USART_RX_BUF[8] =='1') fc_3 = 1;			else  fc_3 = 0;	
	if(USART_RX_BUF[7] =='1') fc_4 = 1;			else  fc_4 = 0;
	
	if(USART_RX_BUF[15] =='1') work_m1 = 1;		else work_m1 = 0;
	if(USART_RX_BUF[14] =='1') work_m2 = 1;		else work_m2 = 0;
	if(USART_RX_BUF[13] =='1') work_m3 = 1;		else work_m3 = 0;
	if(USART_RX_BUF[12] =='1') work_m4 = 1;		else work_m4 = 0;
}
 int main(void)
 {		
 	u8 t,i;
	u8 len;	
	u16 times=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	io_init();
	 
	 while(1)
	{
		
			if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);//�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;	
			USART_SendData(USART1, USART_RX_BUF[3]);
				readdata();
		}
	
		
		if(lo_lock ==1)
		{
			LED0 =0;
		}
		else  LED0 = 1;
		
//	att_c0 = 0;
//	att_c1 = 1;
//	att_c2 = 1;
//	att_c3 = 1;
//	att_c4 = 1;
//	att_c5 = 1;
//	att_c6 = 1;
////	lo_lock= 1;
//	
//	fc_0 = 1;
//	fc_1 = 1;
//	fc_2 = 1;
//	fc_3 = 1;
//	fc_4 = 1;
//	
//	work_m1 = 1;
//	work_m2 = 1;
//	work_m3 = 1;
//	work_m4 = 1;
	
//		else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nս��STM32������ ����ʵ��\r\n");
//				printf("����ԭ��@ALIENTEK\r\n\r\n");
//			}
//			if(times%200==0)printf("����������,�Իس�������\n");  
//			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
//			delay_ms(10);  
//
//		}
	}	 
 }

