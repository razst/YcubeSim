/*
 * TRXUV.c
 *
 *  Created on: 23 במאי 2023
 *      Author: Magshimim
 */

#include "..\sim\TRX.h"

xSemaphoreHandle xDumpLock = NULL;
xSemaphoreHandle xIsTransmitting = NULL;// mutex on transmission.


void initSemaphores()
{
	//create the transmit semaphore
	if(xIsTransmitting == NULL)
			vSemaphoreCreateBinary(xIsTransmitting);

	//create the dump semaphore
	if(xDumpLock == NULL)
		vSemaphoreCreateBinary(xDumpLock);
/*	if(xDumpQueue == NULL) TODO
		xDumpQueue = xQueueCreate(1, sizeof(Boolean));*/
}


int initTrxvu()
{
	ISIStrxvuI2CAddress TRXVUaddress; //define address struct
	ISIStrxvuFrameLengths TRXVUframeLength; //define frame size struct
	ISISantsI2Caddress antennaAddress; //define anttenas address struct
	ISIStrxvuBitrate TRXVUbitrates; //define bitrate enum

	//define addresses
	TRXVUaddress.addressVu_rc = 0x1;
	TRXVUaddress.addressVu_tc = 0x2;

	//define frame sizes
	TRXVUframeLength.maxAX25frameLengthRX = 100;
	TRXVUframeLength.maxAX25frameLengthTX = 100;

	//define antennas addresses
	antennaAddress.addressSideA = 0x3;
	antennaAddress.addressSideB = 0x4;

	//define bitrates as 9600
	TRXVUbitrates = trxvu_bitrate_9600;

	//initialize the TRXVU
	//if (logError(IsisTrxvu_initialize(&TRXVUaddress, &TRXVUframeLength,&TRXVUbitrates, 1) ,"InitTrxvu-IsisTrxvu_initialize") ) return -1;

	vTaskDelay(1000); // wait a little

	//initialize the antennas
	//if (logError(IsisAntS_initialize(&antennaAddress, 1),"InitTrxvu-IsisAntS_initialize")) return -1;

	initSemaphores();

	return 0;
}


int TRX_Logic()
{
	return 0;
}


