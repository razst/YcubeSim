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

#define UNIX_DATE_JAN_D1_Y2000{\
	.seconds = 0,\
	.minutes = 0,\
	.hours = 0,\
	.day = 1,\
	.date = 1,\
	.month = 1,\
	.year = 0,\
	.secondsOfYear = 0};

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
	Time expected_deploy_time = UNIX_DATE_JAN_D1_Y2000;
	err = Time_stop();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_start(&expected_deploy_time,0);
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_start(&expected_deploy_time,0);
	ASSERT_INT(err,E_IS_INITIALIZED);
	int t;
	err = Time_getUnixEpoch(&t);
	ASSERT_TRUE(t >= 946684800);

	ASSERT_TRUE(t <= 946684802);

}

void testTime_setGetUnixEpoch(){
	int err;
	int t;
	Time expected_deploy_time = UNIX_DATE_JAN_D1_Y2000;
	err = Time_stop();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_setUnixEpoch(1617638400);
	ASSERT_INT(err,E_NOT_INITIALIZED);
	err = Time_start(&expected_deploy_time,0);
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_setUnixEpoch(1617638400);
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_getUnixEpoch(&t);
	ASSERT_INT(err,E_NO_SS_ERR);
	ASSERT_TRUE(t>=1617638400);
	err = Time_setUnixEpoch(1617638500);
	ASSERT_INT(err,E_NO_SS_ERR);
	err = Time_getUnixEpoch(&t);
	ASSERT_INT(err,E_NO_SS_ERR);
	ASSERT_TRUE(t >= 1617638500);
}

void testvTaskDelay(){
	int err;
	int t;
	err = Time_setUnixEpoch(1617638400);
	ASSERT_INT(err,E_NO_SS_ERR);
	vTaskDelay(2000);
	err = Time_getUnixEpoch(&t);
	ASSERT_INT(err,E_NO_SS_ERR);
	ASSERT_TRUE(t == 1617638400 + 2);
	printf("t: %d", t);
}

