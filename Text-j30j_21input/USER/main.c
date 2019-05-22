#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "io.h"
//ALIENTEK战舰STM32开发板实验4
//串口实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
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
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
	io_init();
	 
	 while(1)
	{
		
			if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
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
//				printf("\r\n战舰STM32开发板 串口实验\r\n");
//				printf("正点原子@ALIENTEK\r\n\r\n");
//			}
//			if(times%200==0)printf("请输入数据,以回车键结束\n");  
//			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
//			delay_ms(10);  
//
//		}
	}	 
 }

