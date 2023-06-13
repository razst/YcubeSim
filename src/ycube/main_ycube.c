#include "main_ycube.h"

#include <stdlib.h>
#include <../hal/boolean.h>

#include <string.h>
#include "TRXVU.h"
#include "EPS.h"
#include "ERRORS.h"
#include "utils.h"

void test()
{
//	for (int i = 0; i < 6; i++)
//	{
//	    LogError(logFileName , i, "a");
//	}
//
//    FILE* f = fopen(logFileName , "r");
//    if (f != NULL) {
//        char line[30];
//        while (fgets(line, sizeof(line), f) != NULL)
//        {
//            printf("%s", line);
//        }
//        fclose(f);
//        FILE* F = fopen("YcubeSim\ErrorLog.txt", "w");
//        fclose(F);
//    }
//    fclose(logFileName);
}


void taskMain()
{
	// WDT_startWatchdogKickTask(10 / portTICK_RATE_MS, FALSE);

	// Opens the log error file for writing
	// TO DO: Add the current date to the LogError file name and create a new file every day



	InitSubsystems();

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
