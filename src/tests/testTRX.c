/*
 * testTRX.c
 *
 *  Created on: Jan 22, 2021
 *      Author: pc
 */

#include "..\TRX.h"
#include "..\errors.h"
#include "..\utils.h"
#include "testBasic.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int sockfd = -1;


int startUDPServer(){
    struct sockaddr_in     servaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        printf("Unable to open socket\n");
        return E_SOCKET ;
    }

    // set socket options enable broadcast
	int broadcastEnable = 1;
	int ret = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
	if (ret) {
		printf("Unable to set broadcast option\n");
		close(sockfd);
		return E_SOCKET_OPT;
	}

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(DOWN_PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		return E_SOCKET;
	}

    printf("UDP server bounded.\n");

    return E_NO_SS_ERR ;
}

void stopUDPServer(){
	close(sockfd);
}

// Receive msg using UDP server
void getUDPMessage(char *buffer){
    struct sockaddr_in     cliaddr;
    int len, n;

	len = sizeof(cliaddr);  //len is value/resuslt

	n = recvfrom(sockfd, (char *)buffer, MAX_FRAME_LENGTH,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
	buffer[n] = '\0';
	printf("Client sent: %s\n", buffer);
    memset(&cliaddr, 0, sizeof(cliaddr));
//	sendto(sockfd, (const char *)hello, strlen(hello),
//		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
//			len);
//	printf("Hello message sent.\n");

}

/*
 * unit test for sending message
 */
void testTRXSendMeesage(void)
{
	// TODO check init first
	// TODO check & implement avail

	// start GCS UDP server
	startUDPServer();

	// send msg from sat
	char data[] = "test123";
	char avail=0;
	int err = IsisTrxvu_tcSendAX25DefClSign(0, data,strlen(data), &avail);
	ASSERT_INT(err,E_NO_SS_ERR);

	// check thta what we got in GCS is the same as the data we sent
    char buffer[MAX_FRAME_LENGTH];
	getUDPMessage(&buffer);
	ASSERT_STR(&data,&buffer)

	// send one byte less in the length
	err = IsisTrxvu_tcSendAX25DefClSign(0, data,strlen(data)-1, &avail);
	ASSERT_INT(err,E_NO_SS_ERR);

	// check what we got in GCS is diffrent than our data
	getUDPMessage(&buffer);
	ASSERT_NOT_STR(&data,&buffer)

	stopUDPServer();
}

/*
 * unit test for TRX init
 */
void testTRXInit(void){
	ISIStrxvuFrameLengths fl;
	fl.maxAX25frameLengthRX = 200;
	fl.maxAX25frameLengthTX = 200;

	int err = IsisTrxvu_initialize(NULL,&fl,NULL,0);
	ASSERT_INT(err,E_NO_SS_ERR);
	err = IsisTrxvu_initialize(NULL,&fl,NULL,0);
	ASSERT_INT(err,E_IS_INITIALIZED);
}

