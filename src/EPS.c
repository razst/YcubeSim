/*
 * EPS.c
 *
 *  Created on: Nov 22, 2020
 *      Author: pc
 */
#include "utils.h"
#include <stdio.h>
#include "EPS.h"
#include "errors.h"


ISIS_EPS_t _isis_eps;
Boolean _flagEpsInit = FALSE;
Boolean _flagSolarPanelInit = FALSE;

int ISIS_EPS_Init( ISIS_EPS_t* isis_eps, uint8_t isis_epsCount ){
	_flagEpsInit = TRUE;
	_isis_eps.i2cAddr = isis_eps->i2cAddr;
	return E_NO_SS_ERR;
}

int IsisSolarPanelv2_initialize( SPIslave slave ){
	 _flagSolarPanelInit = TRUE;
}

int initEPS(){
	printf("init EPS...\n");
	return 0;
}


int getTelematry(EPSTelematry* data){
	data->vBat = 5;
	data->temp = 10;
	return 0;
}

int getVBat(){
	if (! _flagEpsInit) return E_NOT_INITIALIZED;


}
