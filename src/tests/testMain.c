/*
 * mainTests.c
 *
 *  Created on: Jan 22, 2021
 *      Author: pc
 */


#include "testMain.h"
#include "testTRX.h"
#include "testOBC.h"
#include "Basic.h"





int runMainTests(void){
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("TRX Tests", 0, 0);

    CU_add_test(suite, "send message", testSendMeesage);
    CU_add_test(suite, "trx init", testTrxInit);
    CU_add_test(suite, "test FRAM_START", testFRAMstart);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
