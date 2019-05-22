#include "c8051f330.h"
#include "lmx2594.h"

sbit LD_2594 = P0^4;		 //Ëø¶¨Ö¸Ê¾

void PCA_Init()
{
    PCA0MD    &= ~0x40;
}

void Port_IO_Init()
{
    P0MDOUT   = 0x07;
    XBR1      = 0x40;
}

void Oscillator_Init()
{

	OSCICN    = 0x82;
}

void Init_Device(void)
{
    PCA_Init();
    Port_IO_Init();
    Oscillator_Init();
}


void delay_a(unsigned int z)
{
	while(z)
	{
		z--;
	}
}

void main()
{
	Init_Device();
	delay_a(1000);		
	lmx_2549();
	lmx_2549();
	delay_a(5000);
	delay_a(5000);
	delay_a(5000);
	while(1)
	{
		if(LD_2594 == 0)
		{
			delay_a(1000);
			if(LD_2594 == 0)
			{
				lmx_2549();	
			}			
		}		
		delay_a(5000);
		delay_a(5000);
		delay_a(5000);	
	}
}