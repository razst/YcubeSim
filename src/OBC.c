/*
 * OBC.c
 *
 *  Created on: 24 בינו׳ 2021
 *      Author: Noam Loev
 */
#include "utils.h"
#include "errors.h"
#include "OBC.h"
#include "unistd.h"
#include <stdio.h>

Boolean _flagF_FRAM_start=FALSE;

int FRAM_start(void){
	if(_flagF_FRAM_start==FALSE)
	{
		_flagF_FRAM_start = TRUE;
		if(access(FRAM_FILE_NAME, F_OK ) != 0 ) {
			createFRAMfile();
		}
		return E_NO_SS_ERR;
	}
	return E_IS_INITIALIZED;
}

void createFRAMfile()
{
	char data[FRAM_SIZE] = {0};
	FILE *fptr;
	fptr = fopen(FRAM_FILE_NAME,"a");
	for(int i = 0; i < 1000; i++)
	{
		fwrite(data , 1 , sizeof(data) , fptr);
	}
	fclose(fptr);
}

int FRAM_write(const unsigned char *data, unsigned int address, unsigned int size){
	if(_flagF_FRAM_start == TRUE){
		FILE *fptr;
		fptr = fopen(FRAM_FILE_NAME,"a");
		if(fptr == NULL)
		{
	      return E_FILE;
		}
		fseek(fptr , address, SEEK_SET );
		fwrite(data , 1 , sizeof(data) , fptr);
		fclose(fptr);
	}
	else{
		return E_NOT_INITIALIZED;
	}
	return E_NO_SS_ERR;
}
int FRAM_stop()
{
	_flagF_FRAM_start = FALSE;
	return E_NO_SS_ERR;
}

