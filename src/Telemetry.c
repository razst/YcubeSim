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
static int ArraythreadID [100]={0};



int fs_init(){
	if(_flagTelemetryInit) return E_IS_INITIALIZED;
	_flagTelemetryInit = TRUE;
	return	E_NO_SS_ERR ;
}


int hcc_mem_init(){
	if(_flaghcc_mem_init) return E_IS_INITIALIZED;
	_flaghcc_mem_init = TRUE;
	return	E_NO_SS_ERR ;
}


int f_enterFS(int threadID ){
	for (int i=0; i<=100; i++){
		if(ArraythreadID[i]==0){
			ArraythreadID[i]=threadID;
			return E_NO_SS_ERR;
		}//if
	}//for
	return E_MEM_ALLOC ;
}

void f_releaseFS (int threadID ){
	for (int i=0; i<=100; i++){
		if (ArraythreadID[i]== threadID){
			ArraythreadID[i]=0;
		}///if
	}///for
}
