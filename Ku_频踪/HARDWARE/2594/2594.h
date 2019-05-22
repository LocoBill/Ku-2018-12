#ifndef __2594_H
#define __2594_H	 
#include "sys.h"

#define SCK_2594 PBout(13)
#define CSB_2594 PBout(10)
#define SDI_2594 PBout(12)

extern unsigned long int tab1[113];
void delay_a(unsigned int z);
void init_2594(void);
void delay_2594(unsigned int z);
void lmx2594_senddata(unsigned char add,unsigned int dat);
void lmx2594_senddata1(unsigned long int dat);
void lmx2594_handle(void);

#endif
