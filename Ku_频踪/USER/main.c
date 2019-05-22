#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "control.h"
#include "2594.h"
#include "spi.h"
#include "stm32f10x_spi.h"

/*
//Ku波段射频收发_频踪模块
//Company:XJKJ
//Author:LocoBin
//Version:V1.2
//Description:
*/

unsigned long int att = 0x00,att_old=0x00,fc = 0x00,fc_old=0x00,mode = 0x00,mode_old=0x00,max=0x00;
u8 buff[5] = {0xAA,0x00,0x00,0x00,0x55};
void read_att()
{
		 if(att_c0 == 1)	att |= 0x01;	else att &= 0xfe;
		 if(att_c1 == 1)	att |= 0x02;  else att &= 0xfd;
		 if(att_c2 == 1)	att |= 0x04;	else att &= 0xfb;
		 if(att_c3 == 1)	att |= 0x08;  else att &= 0xf7;
		 if(att_c4 == 1)	att |= 0x10;	else att &= 0xef;
		 if(att_c5 == 1)	att |= 0x20;  else att &= 0xdf;
		 if(att_c6 == 1)	att |= 0x40;  else att &= 0xbf;
		 buff[1] = att;
}

void read_fc()
{
	if(fc_0 == 1)		fc |= 0x01; 	else fc &= 0xfe; 
	if(fc_1 == 1)		fc |= 0x02;		else fc &= 0xfd;
	if(fc_2 == 1)		fc |= 0x04;		else fc &= 0xfb;
	if(fc_3 == 1)		fc |= 0x08;		else fc &= 0xf7;
	if(fc_4 == 1)		fc |= 0x10;		else fc &= 0xef;
}



void set_mode()
{
	if(work_m1 == 1)
	{	
		mode = 0x01;
		
	}
	else if(work_m2 == 1)	
	{
		mode = 0x02;
		s_mode = 0;					//硬件原理图接反 此处为0
	}
	else if(work_m3 == 1)
	{
		mode = 0x04;
		s_mode = 1;						//原理图接反 此处为1 
	}
	buff[2] = mode;
}

 int main(void)
 {	
	 			 
	 signed char i=0;
	 delay_init();	    	 //延时函数初始化	
	 NVIC_Configuration();	 
	 delay_ms(100);
	 LED_Init();
	 control_init();
	 init_2594();
	 SPI1_Init();
	 lmx2594_handle();
	 delay_a(5000);
	 SPI1_SetSpeed(SPI_BaudRatePrescaler_256);
	 
	 while(1)
	 {
		 
		 if(LD_1315 != 1)   //锁定检测
		 {
			 delay_ms(10);
			 if(LD_1315 != 1)
			 {
					lmx2594_handle();
					delay_ms(500);	
			 }
		 }
			 
		 read_att();
		 read_fc();
		 set_mode();
		 
		 if(fc != fc_old)
		 {
			 if(fc > 20)
				 fc =20;
			 tab1[112-36] =0x240000+(65 + fc/2);  //整数部分
			 if((fc%2) == 0x01)  									//分数部分
				 tab1[112-43] = 0x2B01f4;
			 else
				 tab1[112-43] = 0x2b0000;
	
//			lmx2594_senddata1(0x002496);	 //??
//			lmx2594_senddata1(0x002494);	 //????
			lmx2594_senddata1(tab1[112-36]);
			lmx2594_senddata1(tab1[112-43]);
					
			lmx2594_senddata1(0x00249c);
			lmx2594_senddata1(0x00249c);     //????
			
			 for(i=0;i<4;i++)
			 {
					FM =0 ;
				 delay_ms(100);
				  FM = 1;
				 delay_ms(100);
			 }
			FM =1;		 
//			 lmx2594_handle();
		   delay_a(20000);
			 fc_old = fc;
		 }
		 
		 if((att != att_old)|(mode != mode_old))
		 {
			  spi_send();
			  for(i=0;i<4;i++)
			 {
					COMMU =0 ;
				 delay_ms(100);
				  COMMU = 1;
				 delay_ms(100);
			 }
			COMMU =1;
			  att_old = att;
			  mode_old = mode;
		 }
		 
		 if(LD_16_06==1&&LD_15_42==1&&LD_2020m==1&&LD_1920m==1&&LD_1315==1&&LD_800m==1) //本振锁定检测
		 {
			 lo_lock = 1;
			 OSC_LOCK = 1;
		 }
		 else 
		 {
			 lo_lock = 0;
			 OSC_LOCK = 0;
		 }
		 
	 }
	
	 

}



