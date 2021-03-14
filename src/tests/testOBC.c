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

void testFRAMread(){


	   FILE *fp;
	   char c[] = "88";
	   char buffer[100];

	   /* Open file for both reading and writing */
	   fp = fopen("file5.txt", "r+");

	   /* Write data to the file */
	   fwrite(c, strlen(c) + 1, 1, fp);

	   /* Seek to the beginning of the file */
	   fseek(fp, 0, SEEK_SET);

	   /* Read and display data */
	   fread(buffer, strlen(c)+1, 1, fp);
	   printf("str=%s\n", buffer);
	   fclose(fp);





	return;
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
	printf("rest=%d\n",ret);
	ASSERT_TRUE(ret==0);
}
