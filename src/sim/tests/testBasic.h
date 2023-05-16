/*
 * testBasic.h
 *
 *  Created on: Feb 1, 2021
 *      Author: pc
 */

#ifndef TESTS_TESTBASIC_H_
#define TESTS_TESTBASIC_H_

#include <time.h>

extern int passed;
extern int failed;

#define ASSERT_TRUE(value)\
	if (value){\
		passed++;\
		printf("\tTime:%lu\tPassed..%s\n", getTimePasst(),__func__);\
	}else{\
		failed++;\
		printf("\tTime:%lu\tFailed..%s, %s, line %d. got:%d\n", getTimePasst(),__func__, __FILE__,__LINE__,value);\
	}\

#define ASSERT_NOT_INT(value,expected)\
	if (expected!=value){\
		passed++;\
		printf("\tTime:%lu\tPassed..%s\n", getTimePasst(),__func__);\
	}else{\
		failed++;\
		printf("\tTime:%lu\tFailed..%s, %s, line %d. got:%d expected:%d\n", getTimePasst(),__func__, __FILE__,__LINE__,value,expected);\
	}\

#define ASSERT_INT(value,expected)\
	if (expected==value){\
		passed++;\
		printf("\tTime:%lu\tPassed..%s\n", getTimePasst(),__func__);\
	}else{\
		failed++;\
		printf("\tTime:%lu\tFailed..%s, %s, line %d. got:%d expected:%d\n", getTimePasst(),__func__, __FILE__,__LINE__,value,expected);\
	}\

/*
 * compare and assert to strings
 * expected - address of expected string (char *)
 * value - address of value string (char *)
 */
#define ASSERT_STR(value,expected)\
	if (strcmp(expected,value)==0){\
		passed++;\
		printf("\tTime:%lu\tPassed..%s\n", getTimePasst(),__func__);\
	}else{\
		failed++;\
		printf("\tTime:%lu\tFailed..%s, %s, line %d. got:%d expected:%d\n", getTimePasst(),__func__, __FILE__,__LINE__,value,expected);\
	}\

/*
 * compare and assert to strings that shouldn't be equal
 * expected - address of expected string (char *)
 * value - address of value string (char *)
 */
#define ASSERT_NOT_STR(value,expected)\
	if (strcmp(expected,value)!=0){\
		passed++;\
		printf("\tTime:%lu\tPassed..%s\n", getTimePasst(),__func__);\
	}else{\
		failed++;\
		printf("\tTime:%lu\tFailed..%s, %s, line %d. got:%d expected:%d\n", getTimePasst(),__func__, __FILE__,__LINE__,value,expected);\
	}\

void startTesting();

void finishTesting();

__time_t getTimePasst();

void testxQueueCreate();

void testxQueueSend();

void testxQueueReceive();

#endif /* TESTS_TESTBASIC_H_ */
