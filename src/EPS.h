/*
 * EPS.h
 *
 *  Created on: Nov 22, 2020
 *      Author: pc
 */

#ifndef EPS_H_
#define EPS_H_

#include <stdint.h>

/*!
 *  ISIS_EPS instance structure
 *  */
typedef struct
{
	uint8_t i2cAddr; /*!< I2C address used for this instance */
}
ISIS_EPS_t;


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

/*!
 *	Initialize ISIS_EPS instances
 *
 *	@param[in] Pointer to array of ISIS_EPS instances.
 *	@param[in] Count of ISIS_EPS instances. - Note: the sim supports only 1 instance!
 * 	@return ISIS_EPS_ERR_t
 */
int ISIS_EPS_Init( ISIS_EPS_t* isis_eps, uint8_t isis_epsCount );


#endif /* EPS_H_ */
