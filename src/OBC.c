/*
 * OBC.c
 *
 *  Created on: 24 בינו׳ 2021
 *      Author: Noam Loev
 */
#include "utils.h"
#include "errors.h"
#include "OBC.h"
#include "unistd.h"
#include <stdio.h>
#include <time.h>
#include<stdlib.h>
#include<sys/time.h>

Boolean _flagF_FRAM_start=FALSE;
Boolean _flag_Time_start=FALSE;
Boolean _flagF_xQueue_create=FALSE;

time_t time_delta;
time_t sysTime;

xSemaphoreHandle _handle = 0;
char semaphoreArray[100] = {0};

FILE *fptr;
char *endPO;

int FRAM_start(void){
	if(_flagF_FRAM_start==FALSE)
	{
		_flagF_FRAM_start = TRUE;
		if(access(FRAM_FILE_NAME, F_OK ) != 0 ) {
			createFRAMfile();
		}
		return E_NO_SS_ERR;
	}
	return E_IS_INITIALIZED;
}

void createFRAMfile()
{
	char data[FRAM_SIZE] = {0};
	FILE *fptr;
	fptr = fopen(FRAM_FILE_NAME,"a");
	fwrite(data , 1 , sizeof(data) , fptr);
	fclose(fptr);
}

int FRAM_write(const unsigned char *data, unsigned int address, unsigned int size){
	if(size <= FRAM_SIZE){
		if(_flagF_FRAM_start == TRUE){
			FILE *fptr;
			fptr = fopen(FRAM_FILE_NAME,"rb+");
			if(fptr == NULL)
			{
				return E_FILE;
			}
			fseek(fptr , address, SEEK_SET);
			fwrite(data , size , 1 , fptr);
			fclose(fptr);
		}
		else{
			return E_NOT_INITIALIZED;
		}
		return E_NO_SS_ERR;
	}else{
		return E_TRXUV_FRAME_LENGTH;

	}
}

int FRAM_read(const unsigned char *data, unsigned int address, unsigned int size){
	if(size <= FRAM_SIZE){
		if(_flagF_FRAM_start == FALSE){
			return E_NOT_INITIALIZED;
		}
		FILE *fptr;
		fptr = fopen(FRAM_FILE_NAME,"rb");

		if(fptr != NULL)
		{
			fseek(fptr , address, SEEK_SET );
			fread(data, size, 1, fptr);
//			printf("FRAM_read: %s\n", fptr);
			fclose(fptr);
		}
		else{
			return E_NOT_INITIALIZED;
		}
		return E_NO_SS_ERR;
	}else{
		return E_REQUEST_LENGTH_LONG;
	}
}

int FRAM_stop()
{
	_flagF_FRAM_start = FALSE;
	return E_NO_SS_ERR;
}

int Time_start(Time *theTime, const unsigned int syncInterval)
{
	if(_flag_Time_start==TRUE){
		struct tm info;
			info.tm_sec = theTime->seconds;        /* seconds,  range 0 to 59          */
			info.tm_min = theTime->minutes;        /* minutes, range 0 to 59           */
			info.tm_hour = theTime->hours;        /* hours, range 0 to 23             */
			info.tm_mday = theTime->date;        /* day of the month, range 1 to 31  */
			info.tm_mon = theTime->month-1;       /* month, range 0 to 11             */
			info.tm_year = theTime->year+100;       /* The number of years since 1900   */
//			info.tm_wday = theTime->day;        /* day of the week, range 0 to 6    */

		int newTime = mktime(&info);
		if(newTime == -1){
			return E_TIME;
		}
//		printf("new time %d\n", newTime);
		time(&sysTime);

		time_delta = newTime - sysTime;//TODO fix time zone
		return E_IS_INITIALIZED;
	}
	else{
		_flag_Time_start = TRUE;
		return E_NO_SS_ERR;
	}
}

int Time_setUnixEpoch(const unsigned int newTime)
{
	if(_flag_Time_start==TRUE){

		time(&sysTime);
		time_delta = newTime - sysTime;
		return E_NO_SS_ERR;
	}
	else{
		return E_NOT_INITIALIZED;
	}
}

int Time_getUnixEpoch(unsigned int *theTime){
	if(_flag_Time_start==TRUE){
		time_t sysTime;
		time(&sysTime);
		*theTime = time_delta + sysTime;
		return E_NO_SS_ERR;
	}
	return  E_NOT_INITIALIZED;
}

int Time_stop(){
	_flag_Time_start = FALSE;
	return E_NO_SS_ERR;
}

void vTaskDelay(long t){
	sleep(t/1000);
}

void vSemaphoreCreateBinary(xSemaphoreHandle * handle){
	*handle = _handle;
	semaphoreArray[_handle] = 0;
	_handle++;
}

Boolean vSemaphoreTake(xSemaphoreHandle handle, TickType_t xTicksToWait){

	while(semaphoreArray[handle] == 1){
		sleep(0.001);
	}
	semaphoreArray[handle] = 1;
}

void vSemaphoreGive(xSemaphoreHandle handle){
	semaphoreArray[handle] = 0;
}

XQueue* xQueueCreate(int uxQueueLength, int uxItemSize){
	XQueue *queue;
	if(access(QUEUE_FILE_NAME, F_OK ) != 0 ) {
			//createFRAMfile();

			queue->uxQueueLength = uxQueueLength;
			queue->uxItemSize = uxItemSize;

			char data[QUEUE_SIZE] = {0};
			fptr = fopen(QUEUE_FILE_NAME,"ab+");
			endPO = fseek(fptr , 0, SEEK_END);
			//data = uxQueueLength;
			fwrite(data , sizeof(data), 1, fptr);
			queue->pointer = fptr;
			//fclose(fptr);

		}
		return queue;
}

void* xQueueSend(XQueue *xQueue, void* pvItemToQueue, int xTicksToWait)
{
	if(xQueue == NULL)
	{
		return E_FILE;
	}
	//XQueue *queue;
	int size = xQueue->uxItemSize * xQueue->uxQueueLength;
	//xQueue->uxQueueLength;

	//int size = uxItemSize * uxQueueLength;
	fseek(xQueue->pointer , 0, SEEK_CUR);
	if(xQueue->pointer + size >= QUEUE_SIZE){
		return QUEUE_FULL;
	}else{

		fwrite(pvItemToQueue, xQueue->uxItemSize , 1 , xQueue->pointer);
		//fclose(fptr);
	}
		return E_NO_SS_ERR;
}

int xQueueReceive(XQueue* xQueue, void *pvBuffer, TickType_t xTicksToWait) {
	char * i = fseek(fptr, 0, SEEK_SET);
	if(i =! fptr){

	}
	return QUEUE_EMPTY;
}


/*int* xQueueReceive(char xQueue, char pvBuffer, char xTicksToWait){
	if(size <= QUEUE_SIZE){
		if(_flagF_xQueue_create == FALSE){
			return E_NOT_INITIALIZED;
		}
		if(fptr == NULL)
		{
			return E_FILE;
		}else{
			if(fptr != NULL)
			{
				fseek(fptr , 0, SEEK_CUR );
				fread(data, size, 1, fptr);
	//			printf("FRAM_read: %s\n", fptr);
				fclose(fptr);
			}
			else{
				return E_NOT_INITIALIZED;
			}
		}
		return E_NO_SS_ERR;
	}else{
		return E_REQUEST_LENGTH_LONG;
	}
}
*/
int queue_stop()
{
	_flagF_xQueue_create = FALSE;
	return E_NO_SS_ERR;
}
