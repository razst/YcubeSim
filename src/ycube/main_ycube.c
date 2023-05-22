#include "main_ycube.h"

#include <stdlib.h>
#include <../hal/boolean.h>

void taskMain()
{
//	WDT_startWatchdogKickTask(10 / portTICK_RATE_MS, FALSE);
//
//	InitSubsystems();
//
//	while (TRUE) {
//		EPS_Conditioning();
//
//		TRX_Logic();
//
//		TelemetryCollectorLogic();
//
//		Maintenance();
//
//		vTaskDelay(10);
//	}
}


// main operation function. will be called upon software boot.
int main_ycube()
{

	printf ("Starting YcubeSim...\n");

}
