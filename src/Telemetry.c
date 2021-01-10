/*
 * Telemetry.c
 *
 *  Created on: 6 בדצמ× 2020
 *      Author: Alihai
 */
#include "utils.h"
#include "errors.h"
#include <sys/types.h>
#include <sys/syscall.h>
#include "Telemetry.h"



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


int f_enterFS() {
	pid_t tid = syscall(SYS_gettid);
	printf("thread id = %d\n",tid);
	for (int i=0; i<=100; i++){
		if(ArraythreadID[i]==0){
			ArraythreadID[i]=tid;
			return E_NO_SS_ERR;
		}//if
	}//for
	return E_MEM_ALLOC ;
}

void f_releaseFS ( ){
	pid_t tid = syscall(SYS_gettid);

	for (int i=0; i<=100; i++){
		if (ArraythreadID[i]== tid){
			ArraythreadID[i]=0;
		}///if
	}///for
}


F_FILE * f_open (const char * filename,const char * mode ){
	fopen (filename,mode);
}
