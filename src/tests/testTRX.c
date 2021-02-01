/*
 * testTRX.c
 *
 *  Created on: Jan 22, 2021
 *      Author: pc
 */

#include "..\TRX.h"
#include "..\errors.h"
#include "..\utils.h"
#include "testBasic.h"


/*
 * unit test for sending message
 */
void testTRXSendMeesage(void)
{
	char data[] = "test123";
	char avail=0;

	int err = IsisTrxvu_tcSendAX25DefClSign(0, data,strlen(data), &avail);

	ASSERT_INT(err,E_NO_SS_ERR);
}

/*
 * unit test for TRX init
 */
void testTRXInit(void){
	ISIStrxvuFrameLengths fl;
	fl.maxAX25frameLengthRX = 200;
	fl.maxAX25frameLengthTX = 200;

	int err = IsisTrxvu_initialize(NULL,&fl,NULL,0);
	ASSERT_INT(err,E_NO_SS_ERR);
	err = IsisTrxvu_initialize(NULL,&fl,NULL,0);
	ASSERT_INT(err,E_IS_INITIALIZED);
}

