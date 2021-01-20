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

int isis_eps__gethousekeepingengincdb__tm( uint8_t index, isis_eps__gethousekeepingengincdb__from_t *response ){
	response->fields.temp= (short) get_eps_temp();
	printf ("%d",response->fields.temp);
}

double get_eps_temp (){
	FILE *temperatureFile;
	double T;
	temperatureFile = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
	if (temperatureFile == NULL)
	  ; //print some message
	fscanf (temperatureFile, "%lf", &T);
	T /= 1000;
	printf ("The temperature is %6.3f C.\n", T);
	fclose (temperatureFile);
	return T;
}

