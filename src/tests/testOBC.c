/*
 * testOBC.c
 *
 *  Created on: 31 בינו׳ 2021
 *      Author: magshimim
 */


#include "..\OBC.h"
#include "..\errors.h"
#include "testBasic.h"

#include <stdio.h>

void testFRAMstart(void){
	int err;
	err = FRAM_start();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = FRAM_start();
	ASSERT_INT(err,E_IS_INITIALIZED);
}
void testFRAMwrite(){
	char data[] = "string 123";
	int address = 10;
	int err;
	err = FRAM_stop();
	err = FRAM_write(&data,  address,  sizeof(data));
	ASSERT_INT(err,E_NOT_INITIALIZED);
	err = FRAM_start();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = FRAM_write(&data,  address,  sizeof(data));
	ASSERT_INT(err,E_NO_SS_ERR);

}

void testFRAMread(){
	char datain[] = "string 1234";
	char dataout[20] = {0};
	int address = 1;
	int err;
	err = FRAM_stop();
	err = FRAM_write(&datain,  address,  sizeof(datain));
	ASSERT_INT(err,E_NOT_INITIALIZED);
	err = FRAM_read(&dataout,  address,  sizeof(datain));
	ASSERT_INT(err,E_NOT_INITIALIZED);
	err = FRAM_start();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = FRAM_write(&datain,  address,  sizeof(datain));
	ASSERT_INT(err,E_NO_SS_ERR);
	err = FRAM_read(&dataout,  address,  sizeof(datain));
	ASSERT_INT(err,E_NO_SS_ERR);
	int ret = strcmp(dataout, datain);
//	printf("rest=%d\n",ret);
	ASSERT_TRUE(ret==0);
}

void testTime_start(){
	int err;
	err = Time_stop();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_start();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_start();
	ASSERT_INT(err,E_IS_INITIALIZED);
}

void testTime_setUnixEpoch(){
	int err;
	err = Time_stop();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_setUnixEpoch(1617638400);
	ASSERT_INT(err,E_NOT_INITIALIZED);
	err = Time_start();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_setUnixEpoch(1617638400);
	ASSERT_INT(err,E_NO_SS_ERR);
}

void testTime_getUnixEpoch(){
	int err;
	err = Time_stop();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_setUnixEpoch(1617638400);
	ASSERT_INT(err,E_NOT_INITIALIZED);
	err = Time_getUnixEpoch(1617637560);
	ASSERT_INT(err,E_NOT_INITIALIZED);
	err = Time_start();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_setUnixEpoch(1617638400);
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_getUnixEpoch(1617637560);
	ASSERT_INT(err,E_NO_SS_ERR);
}
