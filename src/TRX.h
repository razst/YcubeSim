/*
 * TRX.h
 *
 Created on: 6/12/20
 *      Author: Emmanuel Gelkop
 */
#ifndef TRX_H_
#define TRX_H_

#include "utils.h"
#include "errors.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include "OBC.h"

#define DOWN_PORT     		27002 // to send all messages from sat to UDP server
#define UP_PORT       		28002 // to send all messages from UDP server to sat
#define MAX_FRAME_LENGTH 	300 // max bytes in each frame (UDP packet)

#define FRAM_FILE_NAME "FRAM"
#define QUEUE_FILE_NAME "QUEUE"
#define FRAM_SIZE 512
#define QUEUE_SIZE 512

XQueue* psend;
XQueue* pget;

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
 * Enumeration list of the Idle states of the TRXVU.
 */
typedef enum __attribute__ ((__packed__)) _ISIStrxvuIdleState
{
    trxvu_idle_state_off = 0x00,
    trxvu_idle_state_on = 0x01
} ISIStrxvuIdleState;

/**
 *  Struct for the TRXVU reception frame.
 */
typedef struct __attribute__ ((__packed__)) _ISIStrxvuRxFrame
{
    unsigned short rx_length; ///< Reception frame length.
    unsigned short rx_doppler; ///< Reception frame doppler measurement.
    unsigned short rx_rssi; ///< Reception frame rssi measurement.
    unsigned char* rx_framedata; ///< Pointer to an array receiving reception frame data.
} ISIStrxvuRxFrame;

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

/**
 *  @brief      De-Initialize the ISIS TRXVU with the corresponding i2cAddress from the array of TRXVU I2C Address structure.
 *  @note       This function can only be called once.
 *  @param[in]  address array of TRXVU I2C Address structure.
 *  @param[in]  maxFrameLengths array of maximum frame length structures for TRXVU.
 *  @param[in]	default_bitrates initial default bitrate.
 *  @param[in]  number number of attached TRXVU in the system to be initialized. - Note: the sim supports only one TRXVU!
 *  @return     Error code according to <hal/errors.h>
 *  */
void IsisTrxvu_deinitialize(ISISantsI2Caddress* address);



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
 *  @brief       send UDP data.
 *  @param[in]   data Pointer to the array containing the data to put in the AX.25 message.
 *  @param[in]   length Length of the data to be put in the AX.25 message.
 *  @return      Error code according to <hal/errors.h>
 */

int sendUDPMessage(unsigned char *data, unsigned char length);

/**
 *  @brief       Tell the TRXVU to transmit an AX.25 message with default callsigns and specified content.
 *  @param[in]   index index of ISIS TRXVU I2C bus address- Note: the sim supports only one TRXVU!
 *  @param[in]   data Pointer to the array containing the data to put in the AX.25 message.
 *  @param[in]   length Length of the data to be put in the AX.25 message.
 *  @param[out]  avail Number of the available slots in the transmission buffer of the VU_TC after the frame has been added. Set NULL to skip available slot count read-back.
 *  @return      Error code according to <hal/errors.h>
 */
int IsisTrxvu_tcSendAX25DefClSign(unsigned char index, unsigned char *data, unsigned char length, unsigned char *avail);


/**
 *  @brief       Set the idle state of the TRXVU transmitter, i.e. the state in between transmission.
 *  @param[in]   index index of ISIS TRXVU I2C bus address- Note: the sim supports only one TRXVU!
 *  @param[in]   state The desired idle state of the TRXVU. Use: trxvu_idle_state_on / trxvu_idle_state_off
 *  @return      Error code according to <hal/errors.h>
 */
int IsisTrxvu_tcSetIdlestate(unsigned char index, ISIStrxvuIdleState state);


/**
 *  @brief       Retrieve the number of telecommand frames present in the receive buffer of the TRXVU.
 *  @param[in]   index index of ISIS TRXVU I2C bus address.
 *  @param[out]  frameCount The number of telecommand frames in the buffer.
 *  @return      Error code according to <hal/errors.h>
 */
int IsisTrxvu_rcGetFrameCount(unsigned char index, unsigned short *frameCount);

/**
 *  @brief       Retrieve and delete a telecommand frame from the TRXVU.
 *  @note		 The rx_frame->rx_framedata pointer needs to point to a valid array where the reception frame data will be stored.
 *  @param[in]   index index of ISIS TRXVU I2C bus address.
 *  @param[in][out] rx_frame Pointer to the struct where the telecommand frame should be stored, that already has a valid rx_framedata pointer set.
 *  @return      Error code according to <hal/errors.h>
 */
int IsisTrxvu_rcGetCommandFrame(unsigned char index, ISIStrxvuRxFrame *rx_frame);

/**
 *  @brief       Set the AX.25 bitrate of the TRXVU transmitter.
 *  @param[in]   index index of ISIS TRXVU I2C bus address.
 *  @param[in]   bitrate The desired AX.25 bitrate of the TRXVU.
 *  @return      Error code according to <hal/errors.h>
 */
int IsisTrxvu_tcSetAx25Bitrate(unsigned char index, ISIStrxvuBitrate bitrate);


#endif /* TRX_H_ */
