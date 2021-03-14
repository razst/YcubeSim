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


/*
 * Main testing function, add all test functions here...
 */
int runMainTests(void){
	startTesting();

	/* TRX test Functions */
	testTRXInit();
	testTRXSendMeesage();

	/* EPS test Functions */
	printf("\n/* EPS test Functions */\n\n");
	testISIS_EPS_Init();
	testIsisSolarPanelv2_initialize();
	testIsisSolarPanelv2_getState();
	testIsisSolarPanelv2_Dinitialize();
	testGet_eps_temp ();
	printf("\n/* EPS test Functions */\n\n");
	/* TLM test Functions */
	printf("\n/*start TLM test Functions */\n\n");

	 testTLMfs_init();
     testhcc_mem_init();
     testf_enterFS();
     testf_initvolume();
	printf("\n/*finish TLM test Functions */\n\n");


	/* OBC test Functions */
	testFRAMstart();

	testFRAMwrite();

	testFRAMread();

	finishTesting();
	return 0;
}
