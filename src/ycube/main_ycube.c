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

//		xTaskHandle taskMainHandle;
//
//		TRACE_CONFIGURE_ISP(DBGU_STANDARD, 2000000, BOARD_MCK);
//		// Enable the Instruction cache of the ARM9 core. Keep the MMU and Data Cache disabled.
//		CP15_Enable_I_Cache();
//
//		// The actual watchdog is already started, this only initializes the watchdog-kick interface.
//		WDT_start();
//
//		// create the main operation task of the satellite
//		#ifdef TESTING
//			xTaskGenericCreate(taskTesting, (const signed char*) "taskTesting", 4096,
//					NULL,
//					configMAX_PRIORITIES - 2, &taskMainHandle, NULL, NULL);
//		#else
//			xTaskGenericCreate(taskMain, (const signed char*) "taskMain", 4096, NULL,
//					configMAX_PRIORITIES - 2, &taskMainHandle, NULL, NULL);
//		#endif
//
//
//
//		vTaskStartScheduler();
}
