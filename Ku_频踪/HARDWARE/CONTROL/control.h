#ifndef __CONTROL_H
#define __CONTROL_H	 
#include "sys.h"

#define work_m1 PAin(9)
#define work_m2 PAin(8)
#define work_m3 PCin(9)
#define work_m4 PCin(8)

#define lo_lock PAout(10)

#define fc_0 PCin(12)
#define fc_1 PCin(11)
#define fc_2 PCin(10)
#define fc_3 PAin(12)
#define fc_4 PAin(11)

#define att_c0 PCin(14)
#define att_c1 PBin(9) 
#define att_c2 PBin(8)
#define att_c3 PBin(7)
#define att_c4 PBin(6)
#define att_c5 PBin(5)
#define att_c6 PDin(2)


void control_init(void);


#endif
