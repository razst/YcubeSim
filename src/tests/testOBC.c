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
void testFRAMwrite(){
	char data[] = "string 123";
	int address = 1;
	int err;
	err = FRAM_stop();
	err = FRAM_write(&data,  address,  sizeof(data));
	ASSERT_INT(err,E_NOT_INITIALIZED);
	err = FRAM_start();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = FRAM_write(&data,  address,  sizeof(data));
	ASSERT_INT(err,E_NO_SS_ERR);

}
