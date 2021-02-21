/*
 * testTelemetry.c
 *
 *  Created on: 21 ����� 2021
 *      Author: Alihai
 */

#include "..\Telemetry.h"
#include "..\errors.h"
#include "testBasic.h"





void testTLMfs_init(void){
	int err=fs_init();
	ASSERT_INT(err,E_NO_SS_ERR);
}

void  testhcc_mem_init(void){
	int err=hcc_mem_init();
	ASSERT_INT(err,E_NO_SS_ERR);
}
