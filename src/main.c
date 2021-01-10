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
#include "TRX.h"
#include "Telemetry.h"


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


}


int initTelematrey(){
	f_enterFS();
}

int sendMessage(){

	char data[] = "test123";
	char avail=0;
	IsisTrxvu_tcSendAX25DefClSign(0, data,strlen(data), &avail);

}

int main(void) {
	EPSTelematry epsData;

	printf ("Starting YcubeSim...\n");
	initTelematrey();
	initTrx();
	createDir();
	initEPS();
	while (1==1){
		printf ("Bat Temp = %d\n",epsData.temp);
		sendMessage();
		usleep(1000000);
	}
	return 0;
}
