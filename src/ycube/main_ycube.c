#include "main_ycube.h"

#include <stdlib.h>
#include <../hal/boolean.h>

#include "TRXVU.h"
#include "EPS.h"
#include "ERRORS.h"
#include <stdio.h>
#include <time.h>


int LogError(int error, char* msg) //TO DO: enter data into log file.
{
	//get current time in this format dd/mm/yyyy hh:mm:ss.sss
	time_t t;
    t = time(NULL);
    char time[20] = {0};
    struct tm *tm = localtime(&t);
	sprintf(time, "%02d/%02d/%d %02d:%02d:%02d.%03d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(t % 1000)); // Extract milliseconds from t
	/*FILE* F = fopen("ErrorLog.txt", 'w');
	fprintf(F, strcat(time, str(error));
	fclose(F);*/

    return error;
}

void taskMain()
{
//	WDT_startWatchdogKickTask(10 / portTICK_RATE_MS, FALSE);
//
	InitSubsystems();
	LogError(0,"a");
//
	while (TRUE) {
//		EPS_Conditioning();

		TRX_Logic();

//		TelemetryCollectorLogic();

//		Maintenance();

		vTaskDelay(10);
		printf("*\n");
	}
}

int InitSubsystems()
{
	initEPS();
	initTrxvu();
	return 0;
}


// main operation function. will be called upon software boot.
int main_ycube()
{

	printf ("Starting YcubeSim...\n");
	taskMain();
}
