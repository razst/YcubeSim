/*
 * EPS.c
 *
 *  Created on: Nov 22, 2020
 *      Author: pc
 */

#include <stdio.h>
#include "EPS.h"

int initEPS(){
	printf("init EPS...\n");
	return 0;
}


int getTelematry(EPSTelematry* data){
	data->vBat = 5;
	data->temp = 25;
	return 0;
}

