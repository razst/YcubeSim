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
#include <pthread.h>
#include "EPS.h"
#include "TRX.h"
#include "OBC.h"
#include "Telemetry.h"
#include <time.h>




void createDir(){

	struct stat st = {0};

	if (stat("/SD0", &st) == -1) {
		mkdir("/SD0", 0700);
	}

}

void initEPS(){
	//ISIS_EPS_Init();
}

int initTrx(){
	ISIStrxvuI2CAddress address;
	address.addressVu_rc = 0; // TODO not in use
	address.addressVu_tc = 0; // TODO not in use
	ISIStrxvuFrameLengths maxFrameLengths;
	maxFrameLengths.maxAX25frameLengthRX = 300; // TODO not implemented yet
	maxFrameLengths.maxAX25frameLengthTX = 300; // TODO not implemented yet
	ISIStrxvuBitrate default_bitrates;
	default_bitrates = trxvu_bitrate_9600;  // TODO not implemented yet

	IsisTrxvu_initialize(&address, &maxFrameLengths, &default_bitrates, 1);

	return 0;

}


int initTelematrey(){
	f_enterFS();
}



void testTime(){
	time_t startTime;
	time(&startTime);
	printf("%d\n",startTime);
	vTaskDelay(2000);

	time_t currTime;
	time(&currTime);
	printf("time passed: %d\n",currTime - startTime);

}



//TODO: change linker to dynamic link CUnit lib to reduce bin size + #IFDEF TESTING
int main(void) {
	printf ("Starting YcubeSim...\n");
//	FRAM_start();//to chek if it has been don
	testTime();
//	runMainTests();
//	FRAM_write(0, 0, 0);
//	printf ("End YcubeSim...\n");
	return 0;
}
