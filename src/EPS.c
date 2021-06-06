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
#include "../HW/ina219.h"


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
int IsisSolarPanelv2_Dinitialize(){
	 _flagSolarPanelInit = FALSE;
	 return E_NO_SS_ERR;

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
	response->fields.temp = get_eps_temp();
	printf ("%d",response->fields.temp);
	get_VIP(response->fields.)
}

int get_eps_temp (){
	FILE *temperatureFile;
	int T;
	temperatureFile = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
	if (temperatureFile == NULL)
		return E_INPUT_POINTER_NULL;
	fscanf (temperatureFile, "%d", &T);
	fclose (temperatureFile);
	return T;
}

void get_VIP(isis_eps__vipdeng_t temp,int address){

	float SHUNT_OHMS = 0.1;
	float MAX_EXPECTED_AMPS = 3.2;

	INA219_Init(SHUNT_OHMS, MAX_EXPECTED_AMPS, address); // defualt INA219 I2C address is 0x40
	INA219_configure(RANGE_16V, GAIN_8_320MV, ADC_12BIT, ADC_12BIT);
	temp->fields.current=INA219_current();
	temp->fields.power=INA219_power();
	temp->fields.volt=INA219_voltage();


}
