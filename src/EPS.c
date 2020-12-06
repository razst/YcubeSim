/*
 * EPS.c
 *
 *  Created on: Nov 22, 2020
 *      Author: pc
 */

#include <stdio.h>
#include "EPS.h"
#include "errors.h"


ISIS_EPS_t _isis_eps;
int _flagEpsInit = 0;

int initEPS(){
	printf("init EPS...\n");
	return 0;
}


int getTelematry(EPSTelematry* data){
	data->vBat = 5;
	data->temp = 10;
	return 0;
}

int ISIS_EPS_Init( ISIS_EPS_t* isis_eps, uint8_t isis_epsCount ){
	_flagEpsInit = 1;
	_isis_eps.i2cAddr = isis_eps->i2cAddr;

}

int getVBat(){
	if (! _flagEpsInit) return E_NOT_INITIALIZED;


}
