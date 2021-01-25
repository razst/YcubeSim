/*
 * OBC.h
 *
 *  Created on: 24 בינו׳ 2021
 *      Author: Noam Loev
 */

#ifndef OBC_H_
#define OBC_H_

int FRAM_start(void);

int FRAM_write(const unsigned char *data, unsigned int address, unsigned int size);

#endif /* OBC_H_ */
