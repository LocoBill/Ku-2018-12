#ifndef __UCRF_H
#define __UCRF_H
#include "sys.h" 

#define ATT1_0_5 				PBout(7)
#define ATT1_1 					PBout(8)
#define ATT1_2 					PBout(9)
#define ATT1_4 					PCout(13)
#define ATT1_8 					PCout(14)
#define ATT1_16 				PCout(15)

#define ATT2_0_5				PCout(10)
#define ATT2_1					PCout(11)
#define ATT2_2					PBout(6)
#define ATT2_4					PCout(12)
#define ATT2_8					PBout(5)
#define ATT2_16					PDout(2)

#define ATT3_0_5				PAout(12)
#define ATT3_1					PAout(11)
#define ATT3_2					PAout(10)
#define ATT3_4					PAout(9)
#define ATT3_8					PAout(8)
#define ATT3_16					PCout(9)

#define ATT1119_0_5			PBout(13)
#define ATT1119_1				PBout(14)
#define ATT1119_2				PBout(15)
#define ATT1119_4				PCout(6)
#define ATT1119_8				PCout(7)
#define ATT1119_16			PCout(8)

#define ATT4_0_5				PBout(12)
#define ATT4_1					PBout(11)
#define ATT4_2					PBout(10)
#define ATT4_4					PBout(1)
#define ATT4_8					PBout(0)
#define ATT4_16					PCout(5)


#define S_12 			PAout(0)
#define S_3 			PAout(1)
#define S_4 			PAout(2)
#define S_5 			PAout(3)

extern u8 SPI_Res[200];
void ucrf_init(void);
void ATT_hand(void);
void mode_hand(void);
#endif
