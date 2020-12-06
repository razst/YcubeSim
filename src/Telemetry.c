/*
 * Telemetry.c
 *
 *  Created on: 6 בדצמ× 2020
 *      Author: Alihai
 */
#include "utils.h"
#include "errors.h"



Boolean _flagTelemetryInit = FALSE;
Boolean _flaghcc_mem_init = FALSE;



int fs_init(){
	_flagTelemetryInit = TRUE;
	return	E_NO_SS_ERR ;
}


int hcc_mem_init(){
	_flaghcc_mem_init = TRUE;
	return	E_NO_SS_ERR ;
}
