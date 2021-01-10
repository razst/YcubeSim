/*
 * isis_eps_driver.h
 *
 *  Created on: 3 בינו׳ 2021
 *      Author: User
 */

#ifndef ISIS_EPS_DRIVER_H_
#define ISIS_EPS_DRIVER_H_
#include <stdint.h>

/*!
 * Union for storing the parameters for struct ReplyHeader.
 */
typedef union __attribute__ ((__packed__)) _isis_eps_replyheader_t
{
	unsigned char raw[5];
	struct __attribute__ ((__packed__))	{
		uint8_t stid; /*!< "See \""System Type Identifier (STID)\"" (page 22)" */
		uint8_t ivid; /*!< "See \""Interface Version Identifier (IVID)\"" (page 23)" */
		uint8_t rc; /*!< "See \""Board Identifier (BID)\"" (page 24)" */
		uint8_t bid; /*!< Response code as stated in the header (inside parenthesis). */
		uint8_t cmderr : 4; /*!< "See \""Response Status Information (STAT)\"" (page 25)" */
		uint8_t stat : 4; /*!< "See \""Response Status Information (STAT)\"" (page 25)" */
	} fields;
} isis_eps__replyheader_t;

/*!
 * Union for storing the parameters for struct VIPDeng.
 */
typedef union __attribute__ ((__packed__)) _isis_eps__vipdeng_t
{
	unsigned char raw[6];
	struct __attribute__ ((__packed__))	{
		int16_t volt; /*!<  */
		int16_t current; /*!<  */
		int16_t power; /*!<  */
	} fields;
} isis_eps__vipdeng_t;

/*!
 * Union for storing the parameters for struct CCSDeng.
 */
typedef union __attribute__ ((__packed__)) _isis_eps__ccsdeng_t
{
	unsigned char raw[8];
	struct __attribute__ ((__packed__))	{
		int16_t volt_in_mppt; /*!<  */
		int16_t curr_in_mppt; /*!<  */
		int16_t volt_out_mppt; /*!<  */
		int16_t curr_out_mppt; /*!<  */
	} fields;
} isis_eps__ccsdeng_t;

/*!
 * Union for storing the parameters received by GetHousekeepingEngIncDB Tm.
 */

typedef union __attribute__ ((__packed__)) _isis_eps__gethousekeepingengincdb__from_t
{
	unsigned char raw[174];
	struct __attribute__ ((__packed__))
	{
		isis_eps__replyheader_t reply_header; /*!< "See \""System Type Identifier (STID)\"" (page 22)" */
		uint8_t reserved; /*!< reserved */
		int16_t volt_brdsup; /*!< Voltage of internal board supply in raw form */
		int16_t temp; /*!< Measured temperature provided by a sensor internal to the MCU in raw form */
		isis_eps__vipdeng_t dist_input; /*!< Input V, I and P data taken at the input of the distribution part of the unit in raw form. Negative values indicate output flow. */
		isis_eps__vipdeng_t batt_input; /*!< Input V, I and P data taken at the input of the battery part of the unit in raw form. Negative values indicate output flow. */
		uint16_t stat_obc_on; /*!< Bitflag field indicating channel-on status for the output bus channels. */
		uint16_t stat_obc_ocf; /*!< Bitflag field indicating overcurrent latch-off fault status for the output bus channels. */
		uint16_t bat_stat; /*!< Bitflag field indicating BP board */
		int16_t temp2; /*!< 2 and 4 cell battery pack: Battery pack temperature in between the center battery cells. *
		int16_t temp3; /*!< 2 cell battery pack: not used 4 cell battery pack: Battery pack temperature on the front of the battery pack. */
		int16_t volt_vd0; /*!< Voltage of voltage domain 0 */
		int16_t volt_vd1; /*!< Voltage of voltage domain 0 */
		int16_t volt_vd2; /*!< Voltage of voltage domain 0 */
		isis_eps__vipdeng_t vip_obc00; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc01; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc02; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc03; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc04; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc05; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc06; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc07; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc08; /*!< Output V, I and P of output bus channel */
		isis_eps__ccsdeng_t cc1; /*!< Data on conditioning chain */
		isis_eps__ccsdeng_t cc2; /*!< Data on conditioning chain */
		isis_eps__ccsdeng_t cc3; /*!< Data on conditioning chain */
		isis_eps__vipdeng_t vip_obc09; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc10; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc11; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc12; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc13; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc14; /*!< Output V, I and P of output bus channel */
		isis_eps__vipdeng_t vip_obc15; /*!< Output V, I and P of output bus channel */
		isis_eps__ccsdeng_t cc4; /*!< Data on conditioning chain */
		isis_eps__ccsdeng_t cc5; /*!< Data on conditioning chain */
	} fields;
} isis_eps__gethousekeepingengincdb__from_t;




#endif /* ISIS_EPS_DRIVER_H_ */
