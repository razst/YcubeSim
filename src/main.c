/*
 * main.c
 *
 *  Created on: 16 May 2023
 *      Author: user
 */
#define TEST_ON

#include <stdio.h>

int main()
{
	#ifdef TEST_ON
	printf("start TEST mode");
	runMainTests();
	#else
	printf("start SIM mode");
	#endif
	return 0;
}
