#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "..\EPS.h"
#include "..\errors.h"
#include "testBasic.h"

void testISIS_EPS_Init(){
	ISIS_EPS_t i;
	i.i2cAddr = 55; //"t";
	uint8_t isis_epsCount = 55; //"t";
	//55 is just a random value
	int err = ISIS_EPS_Init(&i, isis_epsCount);
	ASSERT_INT(err,E_NO_SS_ERR);

	err = ISIS_EPS_Init(&i, isis_epsCount);
	ASSERT_INT(err,E_IS_INITIALIZED);
}

void testIsisSolarPanelv2_initialize(){

}

void testIsisSolarPanelv2_getState(){

}

void testIsisSolarPanelv2_Dinitialize(){

}

void testGet_eps_temp (){

}
