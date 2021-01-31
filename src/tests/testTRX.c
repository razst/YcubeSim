/*
 * testTRX.c
 *
 *  Created on: Jan 22, 2021
 *      Author: pc
 */

#include "Basic.h"
#include "..\TRX.h"
#include "..\errors.h"




void testTrxInit(void){
	ISIStrxvuFrameLengths fl;
	fl.maxAX25frameLengthRX = 200;
	fl.maxAX25frameLengthTX = 200;

	int err = IsisTrxvu_initialize(NULL,&fl,NULL,0);
	CU_ASSERT(err==E_NO_SS_ERR);
	err = IsisTrxvu_initialize(NULL,&fl,NULL,0);
	CU_ASSERT(err==E_IS_INITIALIZED);
}


void testSendMeesage(void)
{
	CU_ASSERT(1 == 1);
}
