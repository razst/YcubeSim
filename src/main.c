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

int endlessLoop(void *vargp){
	while( 1==1){
		printf("%c\n",&vargp);
		usleep(100000);

	}
}
<<<<<<< Updated upstream
int FRAM_start();
int FRAM_write(int sucsses);
=======
<<<<<<< HEAD
int FRAM_start();
int FRAM_write(int sucsses);
=======
>>>>>>> Stashed changes


//TODO: change linker to dynamic link CUnit lib to reduce bin size + #IFDEF TESTING
>>>>>>> 76379fce171233aea64b7983655c4c8f912f47ca
int main(void) {
	printf ("Starting YcubeSim...\n");
	int sucsses = 0;
	sucsses = FRAM_start();//to chek if it has been don
	//runMainTests();
	FRAM_write(sucsses);
	printf ("End YcubeSim...\n");
//	f_initvolume(0,NULL,0);
//	initTelematrey();
//	initTrx();
//	IsisTrxvu_tcSetIdlestate(1,trxvu_idle_state_on);
//	usleep(10000000);
//	sendMessage();
//	IsisTrxvu_tcSetIdlestate(1,trxvu_idle_state_off);
//	usleep(10000000);
//	sendMessage();
//	IsisTrxvu_tcSetIdlestate(1,trxvu_idle_state_on);
//	createDir();
//	initEPS();
//	while (1==1){
//		sendMessage();
//		usleep(1000000);
//	}
	return 0;
}
