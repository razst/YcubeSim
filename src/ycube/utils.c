/*
 * utils.c
 *
 *  Created on: Jun 13, 2023
 *      Author: Magshimim
 */

#include <stdio.h>
#include <time.h>
#include "ERRORS.h"
#include "utils.h"

int LogError(int error, char* msg)
{

	// TODO check this function !
	if(error != ER_NO_ERROR)
	{
		time_t t;
		t = time(NULL);
		char time_str[50] = {0};
	    struct tm *tm = localtime(&t);
	    char Error[20];
	    // Enters the date and time to time_str
	    sprintf(time_str, "%02d/%02d/%d %02d:%02d:%02d.%03d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(t % 1000)); // Extract milliseconds from t
	    if(logFileName != NULL) {fprintf(logFileName, "%s %s\n", time_str, Error);}
	}
	return error;
}
