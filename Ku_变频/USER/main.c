#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "UCRF.h"
#include "spi.h"
#include "stm32f10x_spi.h"

unsigned char spi_over=0;
/*
//Ku波段射频收发_变频模块
//Company:XJKJ
//Author:LocoBin
//Version:V1.2
//Description:
*/
 int main(void)
 {	
	 delay_init();	    	 //延时函数初始化	
	 NVIC_Configuration();	 
	 delay_ms(100);
	 SPI1_Init();
	  SPI1_SetSpeed(SPI_BaudRatePrescaler_256);
	 ucrf_init();
	 while(1)
	 {
		 
			if(spi_over == 1)
			{
				mode_hand();
				ATT_hand();
				spi_over = 0;
			}
	}

}



