/*
 * testBasic.c
 *
 *  Created on: Feb 1, 2021
 *      Author: pc
 */
#include "stdio.h"
#include "testBasic.h"

int passed=0;
int failed=0;


void startTesting(){
	printf("Start Testing...\n");
	passed=0;
	failed=0;
}

void finishTesting(){
	printf("Tests Summary:\n");
	printf("\tAssert passed:%d\n",passed);
	printf("\tAssert failed:%d\n",failed);
}
