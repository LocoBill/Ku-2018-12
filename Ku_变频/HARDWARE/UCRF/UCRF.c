#include "UCRF.h"

void ucrf_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	 //使能PA,PD端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;				 //LED0-->PA.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PA.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PA.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //LED0-->PA.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	
	ATT1_0_5 = 0;
	ATT1_1 = 0;
	ATT1_2 = 0;
	ATT1_4 = 0;
	ATT1_8 = 0;
	ATT1_16 = 0;
	
	ATT2_0_5 = 0;
	ATT2_1 = 0;
	ATT2_2 = 0;
	ATT2_4 = 0;
	ATT2_8 = 0;
	ATT2_16 = 0;
	
	ATT3_0_5 = 0;
	ATT3_1 = 0;
	ATT3_2 = 0;
	ATT3_4 = 0;
	ATT3_8 = 0;
	ATT3_16 = 0;
	
	ATT4_0_5 = 0;
	ATT4_1 = 0;
	ATT4_2 = 0;
	ATT4_4 = 0;
	ATT4_8 = 0;
	ATT4_16 = 0;
	
	ATT1119_0_5 = 0;
	ATT1119_1 = 0;
	ATT1119_2 = 0;
	ATT1119_4 = 0;
	ATT1119_8 = 0;
	ATT1119_16 = 0;
	
	S_12 = 0;
	S_3 = 1;
	S_4 = 0;
	S_5 = 1;
}
extern unsigned char spi_data_num;
void ATT_hand(void)
{
	u8 att_data = 0x00;
	if((SPI_Res[spi_data_num-4]==0xAA)&&(SPI_Res[spi_data_num]==0x55))	//ATT
	{
		if(SPI_Res[spi_data_num-1]==((SPI_Res[spi_data_num-3]+SPI_Res[spi_data_num-2]) & 0x0f))
		{
			att_data = SPI_Res[spi_data_num-3];
			
			if(SPI_Res[spi_data_num-3]/32 == 0)		//ATT4
			{
				ATT3_1=0;		ATT3_2=0;		ATT3_4=0;		ATT3_8=0;		ATT3_16=0;
				ATT2_1=0;		ATT2_2=0;		ATT2_4=0;		ATT2_8=0;		ATT2_16=0;
				ATT1_1=0;		ATT1_2=0;		ATT1_4=0;		ATT1_8=0;		ATT1_16=0;
				
				ATT4_16 = (att_data%32)/16;
				ATT4_8 = (att_data%16)/8;
				ATT4_4 = (att_data%8)/4;
				ATT4_2 = (att_data%4)/2;
				ATT4_1 = att_data%2;
			}
			else if(SPI_Res[spi_data_num-3]/32 == 1)			//ATT3
			{
				ATT4_1=1;		ATT4_2=1;		ATT4_4=1;		ATT4_8=1;		ATT4_16=1;
				ATT2_1=0;		ATT2_2=0;		ATT2_4=0;		ATT2_8=0;		ATT2_16=0;
				ATT1_1=0;		ATT1_2=0;		ATT1_4=0;		ATT1_8=0;		ATT1_16=0;
				
				att_data = (att_data+1)%32;
				if(att_data == 0)
				{
					ATT3_1=1;		ATT3_2=1;		ATT3_4=1;		ATT3_8=1;		ATT3_16=1;
				}
				else
				{
					ATT3_16 = (att_data%32)/16;
					ATT3_8 = (att_data%16)/8;
					ATT3_4 = (att_data%8)/4;
					ATT3_2 = (att_data%4)/2;
					ATT3_1 = att_data%2;
				}					
			}
			
			else if(SPI_Res[spi_data_num-3]/32 == 2)			//ATT2
			{
			  ATT4_1=1;		ATT4_2=1;		ATT4_4=1;		ATT4_8=1;		ATT4_16=1;
				ATT3_1=1;		ATT3_2=1;		ATT3_4=1;		ATT3_8=1;		ATT3_16=1;
				ATT1_1=0;		ATT1_2=0;		ATT1_4=0;		ATT1_8=0;		ATT1_16=0;
				
			  att_data = (att_data+1)%32;
				if(att_data == 0)
				{
					ATT2_1=1;		ATT2_2=1;		ATT2_4=1;		ATT2_8=1;		ATT2_16=1;
				}
				else
				{
					ATT2_16 = (att_data%32)/16;
					ATT2_8 = (att_data%16)/8;
					ATT2_4 = (att_data%8)/4;
					ATT2_2 = (att_data%4)/2;
					ATT2_1 = att_data%2;
				}				
			}
			
			else if(SPI_Res[spi_data_num-3]/32 == 3)			//ATT1
			{
				ATT4_1=1;		ATT4_2=1;		ATT4_4=1;		ATT4_8=1;		ATT4_16=1;
				ATT3_1=1;		ATT3_2=1;		ATT3_4=1;		ATT3_8=1;		ATT3_16=1;
				ATT2_1=1;		ATT2_2=1;		ATT2_4=1;		ATT2_8=1;		ATT2_16=1;
				
			  att_data = (att_data+1)%32;
				if(att_data == 0)
				{
					ATT1_1=1;		ATT1_2=1;		ATT1_4=1;		ATT1_8=1;		ATT1_16=1;
				}
				else
				{
					ATT1_16 = (att_data%32)/16;
					ATT1_8 = (att_data%16)/8;
					ATT1_4 = (att_data%8)/4;
					ATT1_2 = (att_data%4)/2;
					ATT1_1 = att_data%2;
				}				
			}
						
//			if((SPI_Res[spi_data_num-3]&0x60)==0x00)			//ATT4
//			{
//				ATT3_1=0;		ATT3_2=0;		ATT3_4=0;		ATT3_8=0;		ATT3_16=0;
//				ATT2_1=0;		ATT2_2=0;		ATT2_4=0;		ATT2_8=0;		ATT2_16=0;
//				ATT1_1=0;		ATT1_2=0;		ATT1_4=0;		ATT1_8=0;		ATT1_16=0;
//				if((SPI_Res[spi_data_num-3]&0x01)==0x01)	
//					ATT4_1=1;	else	ATT4_1=0;
//				if((SPI_Res[spi_data_num-3]&0x02)==0x02)	
//					ATT4_2=1;	else	ATT4_2=0;
//				if((SPI_Res[spi_data_num-3]&0x04)==0x04)	
//					ATT4_4=1;	else	ATT4_4=0;
//				if((SPI_Res[spi_data_num-3]&0x08)==0x08)	
//					ATT4_8=1;	else	ATT4_8=0;
//				if((SPI_Res[spi_data_num-3]&0x10)==0x10)	
//					ATT4_16=1;	else	ATT4_16=0;
//			}
//			
//			if((SPI_Res[spi_data_num-3]&0x60)==0x20)			//ATT3
//			{
//				ATT4_1=1;		ATT4_2=1;		ATT4_4=1;		ATT4_8=1;		ATT4_16=1;
//				ATT2_1=0;		ATT2_2=0;		ATT2_4=0;		ATT2_8=0;		ATT2_16=0;
//				ATT1_1=0;		ATT1_2=0;		ATT1_4=0;		ATT1_8=0;		ATT1_16=0;
//				if((SPI_Res[spi_data_num-3]&0x01)==0x01)	
//					ATT3_1=1;	else	ATT3_1=0;
//				if((SPI_Res[spi_data_num-3]&0x02)==0x02)	
//					ATT3_2=1;	else	ATT3_2=0;
//				if((SPI_Res[spi_data_num-3]&0x04)==0x04)	
//					ATT3_4=1;	else	ATT3_4=0;
//				if((SPI_Res[spi_data_num-3]&0x08)==0x08)	
//					ATT3_8=1;	else	ATT3_8=0;
//				if((SPI_Res[spi_data_num-3]&0x10)==0x10)	
//					ATT3_16=1;	else	ATT3_16=0;
//			}
//			
//			if((SPI_Res[spi_data_num-3]&0x60)==0x40)			//ATT2
//			{
//				ATT4_1=1;		ATT4_2=1;		ATT4_4=1;		ATT4_8=1;		ATT4_16=1;
//				ATT3_1=1;		ATT3_2=1;		ATT3_4=1;		ATT3_8=1;		ATT3_16=1;
//				ATT1_1=0;		ATT1_2=0;		ATT1_4=0;		ATT1_8=0;		ATT1_16=0;
//				if((SPI_Res[spi_data_num-3]&0x01)==0x01)	
//					ATT2_1=1;	else	ATT2_1=0;
//				if((SPI_Res[spi_data_num-3]&0x02)==0x02)	
//					ATT2_2=1;	else	ATT2_2=0;
//				if((SPI_Res[spi_data_num-3]&0x04)==0x04)	
//					ATT2_4=1;	else	ATT2_4=0;
//				if((SPI_Res[spi_data_num-3]&0x08)==0x08)	
//					ATT2_8=1;	else	ATT2_8=0;
//				if((SPI_Res[spi_data_num-3]&0x10)==0x10)	
//					ATT2_16=1;	else	ATT2_16=0;
//			}
//			
//			if((SPI_Res[spi_data_num-3]&0x60)==0x60)			//ATT1
//			{
//				ATT4_1=1;		ATT4_2=1;		ATT4_4=1;		ATT4_8=1;		ATT4_16=1;
//				ATT3_1=1;		ATT3_2=1;		ATT3_4=1;		ATT3_8=1;		ATT3_16=1;
//				ATT2_1=1;		ATT2_2=1;		ATT2_4=1;		ATT2_8=1;		ATT2_16=1;
//				if((SPI_Res[spi_data_num-3]&0x01)==0x01)	
//					ATT1_1=1;	else	ATT1_1=0;
//				if((SPI_Res[spi_data_num-3]&0x02)==0x02)	
//					ATT1_2=1;	else	ATT1_2=0;
//				if((SPI_Res[spi_data_num-3]&0x04)==0x04)	
//					ATT1_4=1;	else	ATT1_4=0;
//				if((SPI_Res[spi_data_num-3]&0x08)==0x08)	
//					ATT1_8=1;	else	ATT1_8=0;
//				if((SPI_Res[spi_data_num-3]&0x10)==0x10)	
//					ATT1_16=1;	else	ATT1_16=0;
//			}
		}
	}
}

void mode_hand(void)
{
	if((SPI_Res[spi_data_num-4]==0xAA)&&(SPI_Res[spi_data_num]==0x55))	
	{
		if(SPI_Res[spi_data_num-1]==((SPI_Res[spi_data_num-3]+SPI_Res[spi_data_num-2]) & 0x0f))
		{
			if(SPI_Res[spi_data_num-2]==0x01)		//OFDM
			{
				S_5 = 0;
			}
			else if(SPI_Res[spi_data_num-2]==0x02)		//回波模式
			{
				S_12 = 0;
				S_3 = 1;
				S_4 = 0;
				S_5 = 1;
			}
			else if(SPI_Res[spi_data_num-2]==0x04)		//仅上行跳频
			{
				S_12 = 1;
				S_3 = 0;
				S_4 = 1;
				S_5 = 1;
			}
		}		
	}
}
