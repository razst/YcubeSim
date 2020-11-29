/*
 ============================================================================
 Name        : HelloCrossC.c
 Author      : Raz
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include "EPS.h"

int main(void) {
	EPSTelematry epsData;

	printf ("Starting ...\n");
	initEPS();
	while (1==1){
		getTelematry(&epsData);
		printf ("Bat Temp = %d\n",epsData.temp);

		usleep(1000000);
	}
	return 0;
}
