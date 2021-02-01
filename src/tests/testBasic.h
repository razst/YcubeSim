/*
 * testBasic.h
 *
 *  Created on: Feb 1, 2021
 *      Author: pc
 */

#ifndef TESTS_TESTBASIC_H_
#define TESTS_TESTBASIC_H_

extern int passed;
extern int failed;

#define ASSERT_INT(value,expected)\
	if (expected==value){\
		passed++;\
		printf("\tPassed..%s\n",__func__);\
	}else{\
		failed++;\
		printf("\tFailed..%s, %s, line %d. got:%d expected:%d\n",__func__, __FILE__,__LINE__,value,expected);\
	}\

void startTesting();

void finishTesting();


#endif /* TESTS_TESTBASIC_H_ */
