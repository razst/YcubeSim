/*
 * TRX.c
 *
 *  Created on: 6/12/20
 *      Author: Emmanuel Gelkop
 */
#include "TRX.h"
#include "utils.h"
#include "errors.h"

// all local variables
Boolean _initFlag=FALSE;
ISIStrxvuFrameLengths _maxFrameLengths;
Boolean _initAnts=FALSE;
ISISantsI2Caddress _address;

int IsisTrxvu_initialize(ISIStrxvuI2CAddress *address, ISIStrxvuFrameLengths *maxFrameLengths, ISIStrxvuBitrate* default_bitrates, unsigned char number){
	if(_initFlag) return E_IS_INITIALIZED;

	_maxFrameLengths.maxAX25frameLengthRX = maxFrameLengths->maxAX25frameLengthRX;
	_maxFrameLengths.maxAX25frameLengthTX = maxFrameLengths->maxAX25frameLengthTX;
	_initFlag=TRUE;
	return E_NO_SS_ERR;
}

int IsisAntS_initialize(ISISantsI2Caddress* address, unsigned char number){
	if(_initAnts) return E_IS_INITIALIZED;
	_address.addressSideA=address->addressSideA;
	_address.addressSideB=address->addressSideB;
	_initAnts=TRUE;
	return E_NO_SS_ERR;
}



