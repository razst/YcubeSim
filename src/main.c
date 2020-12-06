/*
 ============================================================================
 Name        : HelloCrossC.c
 Author      : Raz
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include "EPS.h"


void createDir(){

	struct stat st = {0};

	if (stat("/SD0", &st) == -1) {
		mkdir("/SD0", 0700);
	}

}


int main(void) {
	EPSTelematry epsData;

	printf ("Starting YcubeSim...\n");
	createDir();
	initEPS();
	while (1==1){
		getTelematry(&epsData);
		printf ("Bat Temp = %d\n",epsData.temp);

		usleep(1000000);
	}
	return 0;
}
