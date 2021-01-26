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
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>


Boolean _flagF_enterFS=FALSE;
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
	if( _flagTelemetryInit){
		pid_t tid = syscall(SYS_gettid);
		printf("thread id = %d\n",tid);
		for (int i=0; i<=100; i++){
			if(ArraythreadID[i]==0){
				ArraythreadID[i]=tid;
				_flagF_enterFS= TRUE;
				return E_NO_SS_ERR;
			}//if
		}//for
		return E_MEM_ALLOC ;
	}
	return E_NOT_INITIALIZED;
}

void f_releaseFS ( ){
	if(_flagF_enterFS){
		pid_t tid = syscall(SYS_gettid);
		for (int i=0; i<=100; i++){
			if (ArraythreadID[i]== tid){
				ArraythreadID[i]=0;
			}///if
		}///for
	}
}

int f_initvolume (int drvnumber, F_DRIVERINIT driver_init,  unsigned long driver_param ){
	int err= E_NO_SS_ERR;
	if(_flagF_enterFS){
		if (drvnumber==0){
			err = mkdir("SD0",0777);
			if (err != E_NO_SS_ERR)
				return err;
			err = chdir("SD0");
			if (err != E_NO_SS_ERR)
				return err;
		}
		if (drvnumber==1){
			err = mkdir("SD1",0777);
			if (err != E_NO_SS_ERR)
				return err;
			err =  chdir("SD1");
			if (err != E_NO_SS_ERR)
				return err;
		}
	}
//	int err= E_MEM_ALLOC; TODO fix
	return err;
}

F_FILE * f_open (const char * filename,const char * mode ){
	if(_flagF_enterFS){
		return fopen (filename,mode);
	}
}

long f_write ( const void * buf, long size,long size_st, F_FILE * filehandle ){
	long items_written=0;
	if(_flagF_enterFS){
		items_written=fwrite(buf, size,size_st,filehandle);
		if (items_written != 0)
			return items_written;
	}
	return items_written;
}


int f_close ( F_FILE * filehandle ){
	int err= E_NO_SS_ERR;
	if(_flagF_enterFS){
		err=fclose(filehandle);
		if (err != E_NO_SS_ERR)
			return err;
	}
	err= E_MEM_ALLOC;
	return err;
}

int f_flush ( F_FILE * filehandle ){
	int err= E_NO_SS_ERR;
		if(_flagF_enterFS){
			err=fflush(filehandle);
			if (err != E_NO_SS_ERR)
				return err;
	}
//	err= E_MEM_ALLOC; TODO fix
	return err;
}



long f_read ( void * buf, long size, long size_st, F_FILE * filehandle ){
	long items_read =0;
	if(_flagF_enterFS){
		items_read= fread(buf,  size, size_st, filehandle);
//		if (items_read != 0) TODO fix
//			return items_read;
	}
	return items_read;
}













