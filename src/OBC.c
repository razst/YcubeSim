/*
 * OBC.c
 *
 *  Created on: 24 בינו׳ 2021
 *      Author: Noam Loev
 */
#include "utils.h"
#include "errors.h"
#include <stdio.h>

Boolean _flagF_FRAM_start=FALSE;

int FRAM_start(void){
	if(_flagF_FRAM_start==FALSE)
	{
		_flagF_FRAM_start = TRUE;
		return E_NO_SS_ERR;
	}
	return E_IS_INITIALIZED;
}

//TODO: check if fram_write works.
int FRAM_write(const unsigned char *data, unsigned int address, unsigned int size){
	if(_flagF_FRAM_start == TRUE){
	//FARM_start did work
		int num;
		FILE *fptr;
		fptr = fopen("C:\\program.txt","w");

		if(fptr == NULL)
		{
	      printf("Error!");
	      exit(1);
		}

		fwrite(data , 1 , sizeof(data) , fptr);
		fclose(fptr);
		if ((fptr = fopen("C:\\program.txt","r")) == NULL){
			printf("Error! opening file");
			exit(1);
		}

		fscanf(fptr,"%d", &num);
		printf("Value of num = %d\n", num);
		fclose(fptr);
	}
	else{
	//FRAM_start didnt work
		printf("error!");
		return E_NOT_INITIALIZED;
	}
	return E_NO_SS_ERR;
}

