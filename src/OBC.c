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

	return E_NO_SS_ERR;
}

int FRAM_write(int sucsses, const unsigned char *data, unsigned int address, unsigned int size){
	if(sucsses == E_NO_SS_ERR){
	//FARM_start did work
	printf("it worked\n");
	}
	else{
	//FRAM_start didnt work
	}
	return E_NO_SS_ERR;
}

