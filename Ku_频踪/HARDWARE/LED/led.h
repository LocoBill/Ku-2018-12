#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

#define OSC_LOCK 			PBout(14)	// PA8
#define FM       			PBout(15)
#define COMMU    			PCout(6)
#define s_mode				PCout(5)

//六个LD输入为高  OSC_LOCK为1 
#define LD_16_06 			PAin(3)
#define LD_15_42 			PBin(0)
#define LD_2020m			PBin(1)
#define LD_1920m			PCin(7)
#define LD_1315				PBin(11)
#define LD_800m				PCin(15)




void LED_Init(void);//初始化

		 				    
#endif
