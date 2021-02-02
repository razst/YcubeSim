/*
 * testEPS.c
 *
 *  Created on: 2 áôáø× 2021
 *      Author: User
 */
#include "..\EPS.h"
#include "..\errors.h"
#include "..\utils.h"
#include "testBasic.h"

void testISIS_EPS_Init(){
	ISIS_EPS_t i;
	 i.i2cAddr = "t";
	 uint8_t isis_epsCount = "t";
	int err = ISIS_EPS_Init(&i, isis_epsCount);
	ASSERT_INT(err,E_NO_SS_ERR);

	err = ISIS_EPS_Init(&i, isis_epsCount);
	ASSERT_INT(err,E_IS_INITIALIZED);

}
void testIsisSolarPanelv2_initialize(){
	int err = IsisSolarPanelv2_initialize(8);
	ASSERT_INT(err,E_INDEX_ERROR);

	err = IsisSolarPanelv2_initialize(0);
	ASSERT_INT(err,ISIS_SOLAR_PANEL_STATE_SLEEP);

	err = IsisSolarPanelv2_initialize(0);
	ASSERT_INT(err,E_IS_INITIALIZED);



}



