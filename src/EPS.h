/*
 * EPS.h
 *
 *  Created on: Nov 22, 2020
 *      Author: pc
 */

#ifndef EPS_H_
#define EPS_H_

#include <stdint.h>

typedef enum _SPIslave {
	slave0_spi = 0, //!< slave0_spi In case of bus0, this is the FRAM.
	slave1_spi = 1, //!< slave1_spi In case of bus0, this is the RTC.
	slave2_spi = 2, //!< slave2_spi In case of bus0, this is the Supervisor Microcontroller(PIC).
	slave3_spi = 3, //!< slave3_spi Only available for bus1, uses a GPIO-connector pin, see board.h.
	slave4_spi = 4, //!< slave4_spi Only available for bus1, uses a GPIO-connector pin, see board.h.
	slave5_spi = 5, //!< slave5_spi Only available for bus1, uses a GPIO-connector pin, see board.h.
	slave6_spi = 6, //!< slave6_spi Only available for bus1, uses a GPIO-connector pin, see board.h.
	slave7_spi = 7, //!< slave7_spi Only available for bus1, uses a GPIO-connector pin, see board.h.
} SPIslave;
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
 *	@param[in] Pointer to array of ISIS_EPS instances.
 *	@param[in] Count of ISIS_EPS instances. - Note: the sim supports only 1 instance!
 * 	@return ISIS_EPS_ERR_t
 */
int ISIS_EPS_Init( ISIS_EPS_t* isis_eps, uint8_t isis_epsCount );

/*
 * Initializes the internal hardware and software required for measuring the
 * temperatures of the ISIS solar panels.
 * @param[in] slave SPI slave to which LTC ADC driver is connected
 * @return A value defined by IsisSolarPanelv2_State_t

 * - note: need to complete the function.
 */
int IsisSolarPanelv2_initialize( SPIslave slave );

#endif /* EPS_H_ */
