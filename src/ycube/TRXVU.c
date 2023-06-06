/*
 * TRXUV.c
 *
 *  Created on: 23 במאי 2023
 *      Author: Magshimim
 */

#include "..\sim\TRX.h"

int initTrxvu()
{
	ISIStrxvuI2CAddress TRXVUaddress; //define address struct
	ISIStrxvuFrameLengths TRXUVframeLength; //define frame size struct
	ISISantsI2Caddress anttenaAdress;
	ISIStrxvuBitrate TRXVUbitrates;

	//define addresses
	TRXVUaddress.addressVu_rc = 0x1;
	TRXVUaddress.addressVu_tc = 0x2;

	//define frame sizes
	TRXUVframeLength.maxAX25frameLengthRX = 100;
	TRXUVframeLength.maxAX25frameLengthTX = 100;

	//define antennas addresses
	anttenaAdress.addressSideA = 0x3;
	anttenaAdress.addressSideB = 0x4;

	TRXVUbitrates = trxvu_bitrate_9600;

	return 0;
}


int TRX_Logic()
{
	return 0;
}
