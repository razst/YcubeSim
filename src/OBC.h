/*
 * OBC.h
 *
 *  Created on: 24 בינו׳ 2021
 *      Author: Noam Loev
 */

#ifndef OBC_H_
#define OBC_H_

#define FRAM_FILE_NAME "FRAM"
#define FRAM_SIZE 512

/*
 * starts the FRAM system
 */
int FRAM_start(void);

/*
 * writes data into FRAM
 * data - pointer to data to be written in FRAM
 * address - the address of FRAM
 * size - the amount of bytes to be written
 */
int FRAM_write(const unsigned char *data, unsigned int address, unsigned int size);

/*
 * stops the FRAM system
 */
int FRAM_stop();

#endif /* OBC_H_ */
