#include "c8051f330.h"
#define SYSCLK     24000000        // SYSCLK frequency in Hz

sbit HMC833_Sen = P0^1;
sbit HMC833_Sck = P0^3;
sbit HMC833_Sdi = P0^2;
sbit HMC833_Ld = P0^4;

void SYSCLK_Init (void)
{
   OSCICN = 0x82;
  // RSTSRC = 0x04;          
}

void delay_us(int t)
{
	unsigned int x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}


void write_HMC833_24_resister(unsigned char Addr, unsigned long int Register_data)
{
	unsigned char i;
	HMC833_Sen = 0;
	HMC833_Sck = 0;
	Addr = Addr<<1;
	HMC833_Sen = 1;
	delay_us(10);
	for(i=0;i<7;i++) 			
	{
		if((0x80 & Addr) == 0x80)
		{
			HMC833_Sdi = 1;				
		}
		else
		{
			HMC833_Sdi = 0;
		}
		HMC833_Sck = 1;
		delay_us(10);
		HMC833_Sck = 0;
		delay_us(10);
		Addr = Addr<<1;
	}
	for(i=0;i<25;i++)
	{
		if((0x800000 & Register_data) == 0x800000)
		{
			HMC833_Sdi = 1;				
		}
		else
		{
			HMC833_Sdi = 0;
		}
		HMC833_Sck = 1;
		delay_us(10);
		HMC833_Sck = 0;
		delay_us(10);
		Register_data = Register_data<<1;
	}
	delay_us(10);
	HMC833_Sen = 0; 
	delay_us(10);  
	
}


void write_Hmc833()
{

	unsigned long int freq_turn_word = 0x000000;
//	freq_turn_word = freq_word /100;

    write_HMC833_24_resister(0x0, 0xA7975);   //ID寄存器     (不改)
	write_HMC833_24_resister(0x1, 0x2);      //复位寄存器    （不改）
	write_HMC833_24_resister(0x2, 0x1);     //分频寄存器      (不改)
	write_HMC833_24_resister(0x5, 0x0f88); 	 //  
	write_HMC833_24_resister(0x5, 0xe110);   //	 Rf分频 2分频	     
	write_HMC833_24_resister(0x5, 0x0A18);   //	1500-3000M写0x0898 分频(<1500M)写0x0A18     
	write_HMC833_24_resister(0x5, 0x1628);   //
	write_HMC833_24_resister(0x5, 0x60a0);   //
	write_HMC833_24_resister(0x5, 0x00);     // 默认 （不改）

	write_HMC833_24_resister(0x6, 0X2003CA);  //SD CFG Register  分数模式 0X200B4A   	整数模式 0X2003CA
	write_HMC833_24_resister(0x7, 0x1ca);	   //????:16.64ns, REG07[11:10]=[1:1] ,REG07[9:7]=[0:1:1] (不懂)
                                            //Lock Detect Register	
	write_HMC833_24_resister(0x8, 0xc1beff);		// Analog EN Register 默认不改
	write_HMC833_24_resister(0x9, 0x547FFF);	//Charge Pump UP/DN Gain current 200mA	  Charge Pump Offset current 200uA
	                                           //Charge Pump Register 不懂
	write_HMC833_24_resister(0xa, 0x2046);	   //VCO AutoCal Configuration Register
	write_HMC833_24_resister(0xb, 0x7C021);   //PD Register
	write_HMC833_24_resister(0xc, 0x0);         //Exact Frequency Mode Register  不改
	write_HMC833_24_resister(0xd, 0x0);        //不改
	write_HMC833_24_resister(0xe, 0x0);        //不改

	write_HMC833_24_resister(0xf, 0x81);				  //????????  GPO_SPI_RDIV Register不改
	                                                //GPO_SPI_RDIV Register
	write_HMC833_24_resister(0x3, 0x10);				    //整数寄存器 N=20   （改）
//	write_HMC833_24_resister(0x4, 0x333334);	  //分数寄存器

//	write_HMC833_24_resister(0x5, 0xe090);      // VCO SPI Register   频率>3000M ,<1500M 屏蔽此句
					   
}

void PORT_Init_833(void)
{
   P0MDOUT   = 0x0E;
   XBR1     = 0x40;    //交叉开关使能
}




void main()
{
	PCA0MD &= ~0x40;   //关看门狗
 	//PCA0MD = 0x00;
	SYSCLK_Init();
	PORT_Init_833();
	delay_us(3000);
	write_Hmc833();
	write_Hmc833();
	while(1)
	{	 
		if(HMC833_Ld ==0)
		{
		  delay_us(300);
		  if(HMC833_Ld ==0)
		  	 {
			 	write_Hmc833();
			    delay_us(3000);
			 }
		}
	}
}



	
	

