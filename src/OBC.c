/*
 * OBC.c
 *
 *  Created on: 24 בינו׳ 2021
 *      Author: Noam Loev
 */
#include "utils.h"
#include "errors.h"
#include <stdio.h>

Boolean _flagF_FRAM_start=FALSE;

int FRAM_start(void){
	printf ("FRAM_start...\n");
	_flagF_FRAM_start = TRUE;
	return E_NO_SS_ERR;
}

int FRAM_write(const unsigned char *data, unsigned int address, unsigned int size){
	if(_flagF_FRAM_start == TRUE){
	//FARM_start did work
		printf("it worked\n");
	}
	else{
	//FRAM_start didnt work
		printf("error!");
		return E_NOT_INITIALIZED;
	}
	return E_NO_SS_ERR;
}

