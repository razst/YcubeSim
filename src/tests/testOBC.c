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
	char data2[888] = {0};
	memset(data2, "a", 888);
	int address = 10;
	int err;
	err = FRAM_stop();
	err = FRAM_write(&data,  address,  sizeof(data));
	ASSERT_INT(err,E_NOT_INITIALIZED);
	err = FRAM_start();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = FRAM_write(&data2,  address,  sizeof(data2));
	ASSERT_INT(err,E_TRXUV_FRAME_LENGTH);
	err = FRAM_write(&data,  address,  sizeof(data));
	ASSERT_INT(err,E_NO_SS_ERR)
}

void testFRAMread(){
	char datain[] = "string 123";
	char datain2[888] = {0};
	memset(datain2, "a", 888);
	char dataout[20] = {0};
	char dataout2[700] = {0};
	int address = 1;
	int err;
	err = FRAM_stop();
	err = FRAM_write(&datain,  address,  sizeof(datain));
	ASSERT_INT(err,E_NOT_INITIALIZED);
	err = FRAM_read(&dataout,  address,  sizeof(datain));
	ASSERT_INT(err,E_NOT_INITIALIZED);
	err = FRAM_start();
	ASSERT_INT(err,E_NO_SS_ERR);
	err = FRAM_write(&datain2,  address,  sizeof(datain2));
	ASSERT_INT(err,E_TRXUV_FRAME_LENGTH);
	err = FRAM_write(&datain,  address,  sizeof(datain));
	ASSERT_INT(err,E_NO_SS_ERR)
	err = FRAM_read(&dataout2,  address,  sizeof(datain2));
	ASSERT_INT(err,E_REQUEST_LENGTH_LONG);
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

void testxQueueCreate(){
	XQueue* err;
	err = xQueueCreate(3,4);
	ASSERT_INT(err, err != NULL);
	err = xQueueCreate(3,4);
	ASSERT_INT(err, err != NULL);
	err = xQueueCreate(3,4);
	ASSERT_INT(err, err != NULL);
	err = xQueueCreate(3,4);
	ASSERT_INT(err, err->pointer == NULL);
	//err = xQueueCreate(4,5);
	//ASSERT_INT(err,E_IS_INITIALIZED);
}

void testxQueueSend(){

}

void testxQueueReceive(){
	int* err;
	char data[] = "atring 123";
	char copy[200] = {0};
	err = xQueueReceive(data, copy, 10);
	ASSERT_INT(err, E_NO_SS_ERR);
}

