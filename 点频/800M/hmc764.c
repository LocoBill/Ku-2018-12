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

    write_HMC833_24_resister(0x0, 0xA7975);   //ID�Ĵ���     (����)
	write_HMC833_24_resister(0x1, 0x2);      //��λ�Ĵ���    �����ģ�
	write_HMC833_24_resister(0x2, 0x1);     //��Ƶ�Ĵ���      (����)
	write_HMC833_24_resister(0x5, 0x0f88); 	 //  
	write_HMC833_24_resister(0x5, 0xe110);   //	 Rf��Ƶ 2��Ƶ	     
	write_HMC833_24_resister(0x5, 0x0A18);   //	1500-3000Mд0x0898 ��Ƶ(<1500M)д0x0A18     
	write_HMC833_24_resister(0x5, 0x1628);   //
	write_HMC833_24_resister(0x5, 0x60a0);   //
	write_HMC833_24_resister(0x5, 0x00);     // Ĭ�� �����ģ�

	write_HMC833_24_resister(0x6, 0X2003CA);  //SD CFG Register  ����ģʽ 0X200B4A   	����ģʽ 0X2003CA
	write_HMC833_24_resister(0x7, 0x1ca);	   //????:16.64ns, REG07[11:10]=[1:1] ,REG07[9:7]=[0:1:1] (����)
                                            //Lock Detect Register	
	write_HMC833_24_resister(0x8, 0xc1beff);		// Analog EN Register Ĭ�ϲ���
	write_HMC833_24_resister(0x9, 0x547FFF);	//Charge Pump UP/DN Gain current 200mA	  Charge Pump Offset current 200uA
	                                           //Charge Pump Register ����
	write_HMC833_24_resister(0xa, 0x2046);	   //VCO AutoCal Configuration Register
	write_HMC833_24_resister(0xb, 0x7C021);   //PD Register
	write_HMC833_24_resister(0xc, 0x0);         //Exact Frequency Mode Register  ����
	write_HMC833_24_resister(0xd, 0x0);        //����
	write_HMC833_24_resister(0xe, 0x0);        //����

	write_HMC833_24_resister(0xf, 0x81);				  //????????  GPO_SPI_RDIV Register����
	                                                //GPO_SPI_RDIV Register
	write_HMC833_24_resister(0x3, 0x10);				    //�����Ĵ��� N=20   ���ģ�
//	write_HMC833_24_resister(0x4, 0x333334);	  //�����Ĵ���

//	write_HMC833_24_resister(0x5, 0xe090);      // VCO SPI Register   Ƶ��>3000M ,<1500M ���δ˾�
					   
}

void PORT_Init_833(void)
{
   P0MDOUT   = 0x0E;
   XBR1     = 0x40;    //���濪��ʹ��
}




void main()
{
	PCA0MD &= ~0x40;   //�ؿ��Ź�
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



	
	

