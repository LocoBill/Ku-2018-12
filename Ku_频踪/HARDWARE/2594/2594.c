#include "2594.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "led.h"


unsigned long int tab1[113]=
{
0x700000,
0x6F0000,
0x6E0000,						 
0x6D0000,
0x6C0000,
0x6B0000,
0x6A0000,
0x690021,
0x680000,
0x670000,
0x663F80,
0x650011,
0x640000,
0x630000,
0x620200,
0x610888,
0x600000,
0x5F0000,
0x5E0000,
0x5D0000,
0x5C0000,
0x5B0000,
0x5A0000,
0x590000,
0x580000,
0x570000,
0x560000,
0x55D300,
0x540001,
0x530000,
0x521E00,
0x510000,
0x506666,
0x4F0026,
0x4E0003,	 //VCO??(??)
0x4D0000,
0x4C000C,
0x4B0800,
0x4A0000,
0x49003F,
0x480001,
0x470081,
0x46C350,
0x450000,
0x4403E8,
0x430000,
0x4201F4,
0x410000,
0x401388,
0x3F0000,
0x3E0322,
0x3D00A8,
0x3C0018,
0x3B0001,
0x3A8001,
0x390020,
0x380000,
0x370000,
0x360000,
0x350000,
0x340820,
0x330080,
0x320000,
0x314180,
0x300300,
0x2F0300,
0x2E07FC,
0x2DC8DF,
//0x2C10A3,    //2594功率最大：2C10A3
0x2C00A3,
0x2B0000,	 //????  500(?)
0x2A0000,
0x290000,
0x280000,
0x2703E8,
0x260000,
0x250404,
0x240041,	  //N ???   67	  (?)
0x230004,
0x220000,
0x211E21,
0x200393,
0x1F03EC,
0x1E318C,
0x1D318C,
0x1C0488,
0x1B0002,
0x1A0DB0,
0x190624,
0x18071A,
0x17007C,
0x160001,
0x150401,
0x14F048,
0x1327B7,
0x120064,
0x1100C3,	//195 PLL-R	     (?)
0x100080,
0x0F064F,
0x0E1E70,
0x0D4000,
0x0C5001,
0x0B0018,
0x0A10D8,
0x091604,
0x082000,
0x0740B2,
0x06C802,
0x0500C8,
0x040A43,
0x030642,
0x020500,
0x010808,
0x002494
}; 

void init_2594(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA,PD端口时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_13;				 //LED0-->PA.8 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
}

void delay_2594(unsigned int z)
{
	unsigned int x;
	while(z--)
	{
		for(x=10;x>0;x--);
	}
}


void delay_a(unsigned int z)
{
	while(z)
	{
		z--;
	}
}

void lmx2594_senddata(unsigned char add,unsigned int dat)
{
	unsigned char i=0;
	unsigned int dat_val = 0;
	unsigned char add_t;
	unsigned int dat_t;
	dat_val = dat;
	SCK_2594 = 0;
	CSB_2594 = 1;
	delay_2594(2);
	CSB_2594 = 0;
	delay_2594(2);
	for(i=0;i<8;i++)//??
	{
		add_t = add&0x80; 
		add_t = (add_t>>7)&0x01;
		SDI_2594 = add_t;
		delay_2594(1);
		SCK_2594 = 1;
		delay_2594(1);
		SCK_2594 = 0;
		add=add<<1;
		delay_2594(1);
	}
	for(i=0;i<16;i++)//??
	{
		dat_t = dat_val&0x8000; 
		dat_t = (dat_t>>15)&0x0001;
		SDI_2594 = dat_t;
		delay_2594(1);
		SCK_2594 = 1;
		delay_2594(1);
		SCK_2594 = 0;
		dat_val=dat_val<<1;
		delay_2594(1);
	}
	delay_2594(2);
	CSB_2594 = 1;
	delay_2594(2);
}


void lmx2594_senddata1(unsigned long int dat)
{

	unsigned char i=0;
	unsigned char add_t = 0,ADD = 0;
	unsigned int dat_v = 0,dat_t=0;
	ADD = (dat>>16)&0x000000ff;
	dat_v = dat&0x0000ffff;
	SCK_2594 = 0;
	CSB_2594 = 1;
	delay_2594(2);
	CSB_2594 = 0;
	delay_2594(2);
	for(i=0;i<8;i++)//??
	{
		add_t = ADD&0x80; 
		add_t = (add_t>>7)&0x01;
		SDI_2594 = add_t;
		delay_2594(1);
		SCK_2594 = 1;
		delay_2594(1);
		SCK_2594 = 0;
		ADD=ADD<<1;
		delay_2594(1);
	}
	for(i=0;i<16;i++)//??
	{
		dat_t = dat_v&0x8000; 
		dat_t = (dat_t>>15)&0x0001;
		SDI_2594 = dat_t;
		delay_2594(1);
		SCK_2594 = 1;
		delay_2594(1);
		SCK_2594 = 0;
		dat_v=dat_v<<1;
		delay_2594(1);
	}
	delay_2594(2);
	CSB_2594 = 1;
	delay_2594(2);
}


void lmx2594_handle(void)
{
	signed char i=0;
	lmx2594_senddata1(0x002496);	 //??
	lmx2594_senddata1(0x002494);	 //????
	for(i=0;i<113;i++)
	{
		lmx2594_senddata1(tab1[112-i]);		
	}
	lmx2594_senddata1(0x00249c);
	lmx2594_senddata1(0x00249c);     //????
}
