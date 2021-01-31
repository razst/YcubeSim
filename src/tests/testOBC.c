/*
 * testOBC.c
 *
 *  Created on: 31 בינו׳ 2021
 *      Author: magshimim
 */
#include "Basic.h"
#include "..\OBC.h"
#include "..\errors.h"

void testFRAMstart(void){
	int err;
	err = FRAM_start();
	CU_ASSERT(err==E_NO_SS_ERR);
	err = FRAM_start();
	CU_ASSERT(err==E_IS_INITIALIZED);
}
