/*
 * TRX.h
 *
 Created on: 6/12/20
 *      Author: Emmanuel Gelkop
 */

#ifndef TRX_H_
#define TRX_H_
/**
 *  Struct for defining ISIS TRXVU I2C Address.
 */
typedef struct _ISIStrxvuI2CAddress
{
    unsigned char addressVu_rc; ///< I2C address of the VU_RC.
    unsigned char addressVu_tc; ///< I2C address of the VU_TC.
} ISIStrxvuI2CAddress;

/**
 *  Struct for defining ISIS TRXVU buffers length.
 */
typedef struct _ISIStrxvuFrameLengths
{
    unsigned int maxAX25frameLengthTX; ///< AX25 maximum frame size for transmission.
    unsigned int maxAX25frameLengthRX; ///< AX25 maximum frame size for reception.
} ISIStrxvuFrameLengths;

/**
 * Enumeration list of bitrate options for setting the bitrate in the TRXVU.
 */
typedef enum __attribute__ ((__packed__)) _ISIStrxvuBitrate
{
    trxvu_bitrate_1200 = 0x01, ///< Transmission Bitrate 1200 bps.
    trxvu_bitrate_2400 = 0x02, ///< Transmission Bitrate 2400 bps.
    trxvu_bitrate_4800 = 0x04, ///< Transmission Bitrate 4800 bps.
    trxvu_bitrate_9600 = 0x08 ///< Transmission Bitrate 9600 bps.
} ISIStrxvuBitrate;

/**
 *  @brief      Initialize the ISIS TRXVU with the corresponding i2cAddress from the array of TRXVU I2C Address structure.
 *  @note       This function can only be called once.
 *  @param[in]  address array of TRXVU I2C Address structure.
 *  @param[in]  maxFrameLengths array of maximum frame length structures for TRXVU.
 *  @param[in]	default_bitrates initial default bitrate.
 *  @param[in]  number number of attached TRXVU in the system to be initialized. - Note: the sim supports only one TRXVU!
 *  @return     Error code according to <hal/errors.h>
 */
int IsisTrxvu_initialize(ISIStrxvuI2CAddress *address, ISIStrxvuFrameLengths *maxFrameLengths, ISIStrxvuBitrate* default_bitrates, unsigned char number);




/**
 *	Struct for defining ISIS Antenna Systems Status I2C Address.
 */
typedef struct _ISISantsI2Caddress
{
	unsigned char addressSideA; ///< I2C address of the AntS side A microcontroller
	unsigned char addressSideB; ///< I2C address of the AntS side B microcontroller
} ISISantsI2Caddress;
/*!
 * 	Initialize the ISIS Antenna Systems with the corresponding i2cAddress from the array of Antenna Systems I2C Address structure.
 *  @note       This function can only be called once.
 * 	@param[in]  address array of Antenna Systems I2C Address structure.
 * 	@param[in]  number number of attached Antenna Systems in the system to be initialized.
 * 	@return     The error status of the initialization, defined in <hal/errors.h>.
 */
int IsisAntS_initialize(ISISantsI2Caddress* address, unsigned char number);

#endif /* TRX_H_ */
