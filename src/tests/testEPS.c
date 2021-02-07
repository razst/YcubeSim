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
void testIsisSolarPanelv2_getState(){
	IsisSolarPanelv2_Dinitialize();
	int err = IsisSolarPanelv2_getState();
	ASSERT_INT (err,ISIS_SOLAR_PANEL_STATE_NOINIT);

	IsisSolarPanelv2_initialize(0);
	err = IsisSolarPanelv2_getState();
	ASSERT_INT (err, ISIS_SOLAR_PANEL_STATE_SLEEP);

}
void testIsisSolarPanelv2_Dinitialize(){
	int err = IsisSolarPanelv2_Dinitialize();
	ASSERT_INT(err,E_NO_SS_ERR);
}

void testGet_eps_temp (){
	int err = get_eps_temp ();
	for (int i = 0; i<1000000000; i++);

	int err2 = get_eps_temp ();
ASSERT_NOT_INT(err,err2);
printf ("The temperature is %d C,temerture 2 is %d C.\n", err,err2);

}


