#include "main_ycube.h"

#include <stdlib.h>
#include <../hal/boolean.h>

#include "TRXVU.h"
#include "EPS.h"

void taskMain()
{
//	WDT_startWatchdogKickTask(10 / portTICK_RATE_MS, FALSE);
//
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
