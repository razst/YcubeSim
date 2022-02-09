/*
 * mainTests.c
 *
 *  Created on: Jan 22, 2021
 *      Author: pc
 */


#include "testMain.h"
#include "testTRX.h"
#include "testOBC.h"
#include "testBasic.h"
#include "testTelemetry.h"
#include "testEPS.h"


/*
 * Main testing function, add all test functions here...
 */
int runMainTests(void){
	startTesting();

	printf("\n/*start TRX test Functions */\n\n");
	testTRXInit();
	testTRXSendMeesage();
	testIsisAntS_initialize();
	testISIStrxvuIdleState();
	printf("\n/*start TRX test Functions */\n\n");

	printf("\n/* EPS test Functions */\n\n");
	testISIS_EPS_Init();
	testIsisSolarPanelv2_initialize();
	testIsisSolarPanelv2_getState();
	testIsisSolarPanelv2_Dinitialize();
	//testGet_eps_temp ();
	//testINA219();
	printf("\n/* EPS test Functions */\n\n");

	printf("\n/*start TLM test Functions */\n\n");
	 testTLMfs_init();
     testhcc_mem_init();
     testf_enterFS();
     //testf_initvolume();
	printf("\n/*finish TLM test Functions */\n\n");


	printf("\n/*Start OBC test Functions */\n\n");
	testFRAMstart();
	testFRAMwrite();
	testFRAMread();
	testTime_start();
	testTime_setGetUnixEpoch();
	testvTaskDelay();
	finishTesting();
	printf("\n/*Finish OBC test Functions */\n\n");

	return 0;
}
