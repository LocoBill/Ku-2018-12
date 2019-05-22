#ifndef __IO_H
#define __IO_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

#define att_c0 PGout(5)
#define att_c1 PGout(3) 
#define att_c2 PDout(15)
#define att_c3 PDout(13)
#define att_c4 PDout(11)
#define att_c5 PDout(9)
#define att_c6 PBout(15)

#define fc_0 PBout(13)
#define fc_1 PBout(12)
#define fc_2 PBout(14)
#define fc_3 PDout(8)
#define fc_4 PDout(10)

#define lo_lock PDin(12)

#define work_m1 PDout(14)
#define work_m2 PGout(2)
#define work_m3 PGout(4)
#define work_m4 PGout(6)










void io_init(void);//≥ı ºªØ

		 				    
#endif
