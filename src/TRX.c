/*
 * TRX.c
 *
 *  Created on: 6/12/20
 *      Author: Emmanuel Gelkop
 */
#include "TRX.h"
#include "utils.h"
#include "errors.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


// all local variables
Boolean _initFlag=FALSE;
ISIStrxvuFrameLengths _maxFrameLengths;
Boolean _initAnts=FALSE;
ISISantsI2Caddress _address;

int IsisTrxvu_initialize(ISIStrxvuI2CAddress *address, ISIStrxvuFrameLengths *maxFrameLengths, ISIStrxvuBitrate* default_bitrates, unsigned char number){
	if(_initFlag) return E_IS_INITIALIZED;

	_maxFrameLengths.maxAX25frameLengthRX = maxFrameLengths->maxAX25frameLengthRX;
	_maxFrameLengths.maxAX25frameLengthTX = maxFrameLengths->maxAX25frameLengthTX;
	_initFlag=TRUE;
	return E_NO_SS_ERR;
}

int IsisAntS_initialize(ISISantsI2Caddress* address, unsigned char number){
	if(_initAnts) return E_IS_INITIALIZED;
	_address.addressSideA=address->addressSideA;
	_address.addressSideB=address->addressSideB;
	_initAnts=TRUE;
	return E_NO_SS_ERR;
}


int sendMessage(){
    int sockfd;
    char *message = "Hello from Sat";
    struct sockaddr_in     servaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        printf("Unable to open socket\n");
        return -1;
    }

    // set socket options enable broadcast
	int broadcastEnable = 1;
	int ret = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
	if (ret) {
		printf("Unable to set broadcast option\n");
		close(sockfd);
		return -2;
	}

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(UDP_PORT);
    servaddr.sin_addr.s_addr  = INADDR_BROADCAST;
    //servaddr.sin_addr.s_addr   = inet_addr("192.168.14.118");
    //servaddr.sin_addr.s_addr = INADDR_ANY;


    int messageX = 30;
    sendto(sockfd, (const char *)message, strlen(message),
    //sendto(sockfd, &messageX, sizeof(messageX),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
    printf("Message sent.\n");

    close(sockfd);
    return 0;
}



