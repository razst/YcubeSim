/*
 * testBasic.c
 *
 *  Created on: Feb 1, 2021
 *      Author: pc
 */
#include <stdio.h>
#include "testBasic.h"

int passed=0;
int failed=0;
struct timespec start, end;

__time_t getTimePasst(){
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	return (end.tv_sec - start.tv_sec);
}

void startTesting(){
	printf("Start Testing...\n");
	passed=0;
	failed=0;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
}

void finishTesting(){
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	printf("\nTests Summary:\n");
	printf("\tTook:\t\t%lu seconds\n", getTimePasst());
	printf("\tAssert passed:\t%d\n",passed);
	printf("\tAssert failed:\t%d\n",failed);
}
