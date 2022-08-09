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

	printf("start TRX test Functions \n");
	/*testTRXInit();
	testTRXSendMeesage();
	printf("end testTRXSendMeesage \n");
	testIsisAntS_initialize();*/
    testISIStrxvuIdleState();
	printf("end TRX test Functions \n");
/*
	printf("\n/EPS test Functions \n");
	testISIS_EPS_Init();
	testIsisSolarPanelv2_initialize();
	testIsisSolarPanelv2_getState();
	testIsisSolarPanelv2_Dinitialize();
	//testGet_eps_temp ();
	//testINA219();
	printf(" EPS test Functions \n");

	printf("start TLM test Functions \n");
	 testTLMfs_init();
     testhcc_mem_init();
     testf_enterFS();
     //testf_initvolume();
	printf("finish TLM test Functions \n");


	printf("Start OBC test Functions \n");
	testFRAMstart();
	testFRAMwrite();
	testFRAMread();
	testTime_start();
	testTime_setGetUnixEpoch();
	testvTaskDelay();
	finishTesting();
	printf("Finish OBC test Functions \n");
*/
	return 0;
}
