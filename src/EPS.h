/*
 * EPS.h
 *
 *  Created on: Nov 22, 2020
 *      Author: pc
 */

#ifndef EPS_H_
#define EPS_H_


typedef struct epsTelematry{

	int vBat;
	short temp;

}EPSTelematry;


/*
 * Desc: intitilize the EPS
 * in:
 * return: error code
 */
int initEPS();

/*
 * Desc: get EPS telematry
 * in:pointer to EPSTelematry struct
 * return: error code
 */
int getTelematry(EPSTelematry* data);



#endif /* EPS_H_ */
