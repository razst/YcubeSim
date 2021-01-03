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
if (_flagEpsInit == TRUE){
	return E_IS_INITIALIZED;
}
	_flagEpsInit = TRUE;
	_isis_eps.i2cAddr = isis_eps->i2cAddr;
	return E_NO_SS_ERR;
}


int IsisSolarPanelv2_initialize( SPIslave slave ){
	if (_flagSolarPanelInit == TRUE){
		return E_IS_INITIALIZED;
	}

	if (slave != slave0_spi){
		return E_INDEX_ERROR;
	}

	 _flagSolarPanelInit = TRUE;

	 return IsisSolarPanelv2_getState();
}

/* TODO: need to complete the function| AWAKE/SLEEP
 *
 */
IsisSolarPanelv2_State_t IsisSolarPanelv2_getState(){
	if (_flagSolarPanelInit == FALSE){
		return ISIS_SOLAR_PANEL_STATE_NOINIT;
	}
	return ISIS_SOLAR_PANEL_STATE_SLEEP;
}
