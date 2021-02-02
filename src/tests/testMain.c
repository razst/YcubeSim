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
	printf("\n/* EPS test Functions */\n\n");
	/* TLM test Functions */

    
    
	/* OBC test Functions */
	testFRAMstart();

	finishTesting();
	return 0;
}
