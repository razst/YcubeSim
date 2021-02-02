/*
 * testOBC.c
 *
 *  Created on: 31 בינו׳ 2021
 *      Author: magshimim
 */


#include "..\OBC.h"
#include "..\errors.h"
#include "testBasic.h"

void testFRAMstart(void){
	int err;
	err = FRAM_start();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = FRAM_start();
	ASSERT_INT(err,E_IS_INITIALIZED);
}
