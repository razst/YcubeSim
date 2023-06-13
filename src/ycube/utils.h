/*
 * utils.h
 *
 *  Created on: Jun 13, 2023
 *      Author: Magshimim
 */

#ifndef YCUBE_UTILS_H_
#define YCUBE_UTILS_H_

#include "ERRORS.h"
#include <stdio.h>
#include <time.h>

static const char logFileName[] = "ErrorLog.txt";


/*
 * Input - Error type, message.
 * Output - The error that was recived.
 * Description - Append the errors to the logError file with the current date and time.
 * Potential errors - time_str and Error variables not having enough memory.
 *
 */
int LogError(int error, char* msg);



#endif /* YCUBE_UTILS_H_ */
