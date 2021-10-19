/*
 * OBC.h
 *
 *  Created on: 24 בינו׳ 2021
 *      Author: Noam Loev
 */

#ifndef OBC_H_
#define OBC_H_

#define FRAM_FILE_NAME "FRAM"
#define QUEUE_FILE_NAME "QUEUE"
#define FRAM_SIZE 512
#define QUEUE_SIZE 512

#include <time.h>
#include<stdlib.h>
#include<sys/time.h>

typedef int xSemaphoreHandle;
typedef long TickType_t;

typedef struct __attribute__ ((__packed__)) _Time {
	unsigned char seconds; ///< Seconds of the minute.
	unsigned char minutes; ///< Minutes in the hour.
	unsigned char hours; ///< Hour of the day.
	unsigned char day;  ///< Day of the week (Sunday=1, Monday=2, ..., Saturday=7)
	unsigned char date; ///< Date of the month.
	unsigned char month; ///< Month of the year (January = 1).
	unsigned char year; ///< Year since 2000 (2000 = 0).
	unsigned int  secondsOfYear; ///< Number of seconds since the start of year.
} Time;


/*
 * starts the FRAM system
 */
int FRAM_start(void);

/*
 * writes data into FRAM
 * data - pointer to data to be written in FRAM
 * address - the address of FRAM
 * size - the amount of bytes to be written
 */
int FRAM_write(const unsigned char *data, unsigned int address, unsigned int size);

/*
 * stops the FRAM system
 */
int FRAM_read(const unsigned char *data, unsigned int address, unsigned int size);

/*
 * reads from the FRAM file
 */
int FRAM_stop();

int Time_start(Time *theTime, const unsigned int syncInterval);

int Time_setUnixEpoch(const unsigned int epochTime);
int Time_getUnixEpoch(unsigned int *theTime);
void vSemaphoreCreateBinary(xSemaphoreHandle * handle);

void vTaskDelay(long t);

int xQueueCreate();
int xQueueSend(const unsigned char *data, unsigned int address, unsigned int size);
int xQueueReceive(const unsigned char *data, unsigned int address, unsigned int size);

#endif /* OBC_H_ */
