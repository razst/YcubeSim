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
#include "string.h"

Boolean _flagF_FRAM_start=FALSE;
Boolean _flag_Time_start=FALSE;
Boolean _flagF_xQueue_create=FALSE;

time_t time_delta;
time_t sysTime;

xSemaphoreHandle _handle = 0;
char semaphoreArray[100] = {0};

FILE *fptr;
int n_queues = 0;
char data1[QUEUE_SIZE+0] = {'\0'};
char data2[QUEUE_SIZE+1] = {'\0'};
char data3[QUEUE_SIZE+2] = {'\0'};

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
	XQueue *queue = malloc(sizeof(XQueue));
	//if(access(QUEUE_FILE_NAME, F_OK ) != 0 ) {
	if(queue){
	//createFRAMfile();

			queue->uxQueueLength = uxQueueLength;
			queue->uxItemSize = uxItemSize;

			//char data[QUEUE_SIZE] = {0};
			//fptr = fopen(QUEUE_FILE_NAME,"ab+");
			//endPO = fseek(fptr , 0, SEEK_END);
			//data = uxQueueLength;
			//fwrite(data , sizeof(data), 1, fptr);
			switch (n_queues) {
				case 0:
					queue->pointer = &data1[0];
					n_queues++;
					break;
				case 1:
					queue->pointer = &data2[0];
					n_queues++;
					break;
				case 2:
					queue->pointer = &data3[0];
					n_queues++;
					break;
			}

			//fclose(fptr);
			return queue;
		}
		//return queue;
}

void* xQueueSend(XQueue *xQueue, void* pvItemToQueue, int xTicksToWait)
{
	printf("xQueueSend: start");
	if(xQueue == NULL)
	{
		return E_FILE;
	}
	printQ(xQueue);
	char* endpo=strchrnul((char*)xQueue->pointer,'\0');


    int size_tmp = (int)endpo - (int)xQueue->pointer;

    if(size_tmp + xQueue->uxQueueLength >= QUEUE_SIZE){
		printf("xQueueSend: Queue is full \n");
		return QUEUE_FULL;
	}
	printf("xQueueSend: Queue is unfull \n");
	memcpy(endpo,pvItemToQueue,xQueue->uxItemSize);

	printQ(xQueue);
	return E_NO_SS_ERR;
}

int xQueueReceive(XQueue* xQueue, void *pvBuffer, TickType_t xTicksToWait) {
	printf("xQueueReceive: start \n" );
	printQ(xQueue);

	char* endPO = strchrnul((char*)xQueue->pointer, '\0');

	char * startPO = (char*)xQueue->pointer; //fseek(fptr, 0, SEEK_SET);
	if(endPO != startPO){
		printf("xQueueReceive: Queue isn't empty \n" );

		memcpy(pvBuffer, xQueue->pointer, xQueue->uxItemSize);
		printQ(xQueue);


		//while (*(sizeof(char)+startPO)) /* Check against NULL char*/
		while (*startPO) /* Check against NULL char*/
		{
			memcpy(startPO, xQueue->uxItemSize+startPO, sizeof(char));
			startPO++;
		}
		//startPO++;

		//*startPO = '\0';
		printQ(xQueue);

		//printf("xQueueReceive: queue pointer values: %s \n" ,*(xQueue->pointer) );
		 if(pvBuffer != NULL){
			 return E_NO_SS_ERR;
		 }
		 else{
			 printf("xQueueReceive: Q is empty \n" );
			 return QUEUE_EMPTY;
		 }
	}
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



//noam, I write for myself a new command here(that return how much used plase there is in the Queue)
int xQUsedCount(XQueue* xQueue){

	char* p=xQueue->pointer;
	int count=0;
	while(*p){
		count++;
		p++;
	}
return (count/xQueue->uxItemSize);
}
void printQ(XQueue* xQueue){
	char* p=xQueue->pointer;
	printf("Queue: \n");
	for (char i=0;i<=20;i++){

		printf(" %c _" ,*(p+i));
			}
	printf("\n");
}

