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
	printf("getUDPMessage: before recvfrom func \n");
	printf("getUDPMessage:sockfd- %d \n",sockfd);
	n = recvfrom(sockfd, (char *)buffer, MAX_FRAME_LENGTH,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
	printf("getUDPMessage:after recvfrom func \n");
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
	// TODO check & implement avail

	// start GCS UDP server
	startUDPServer();

	printf("testTRXSendMeesage: start \n");

	// send msg from sat
	char data[] = "test123456\0";
	char avail=0;

	IsisTrxvu_deinitialize(NULL);
	int	err = IsisTrxvu_tcSendAX25DefClSign(0, data,strlen(data), &avail);
	ASSERT_INT(err,E_NOT_INITIALIZED);

	ISIStrxvuFrameLengths Fl;
		Fl.maxAX25frameLengthRX = 200;
		Fl.maxAX25frameLengthTX = 200;

	IsisTrxvu_initialize(NULL,&Fl,NULL,0);

	err = IsisTrxvu_tcSendAX25DefClSign(0, data,strlen(data), &avail);
	ASSERT_INT(err,E_NO_SS_ERR);

	IsisTrxvu_tcStartReadingQ(0);

	// check that what we got in GCS is the same as the data we sent
    char buffer[MAX_FRAME_LENGTH];

	getUDPMessage(&buffer);

	ASSERT_STR(&data,&buffer)
	// send one byte less in the length
	err = IsisTrxvu_tcSendAX25DefClSign(0, data,strlen(data)-2, &avail);
	ASSERT_INT(err,E_NO_SS_ERR);

	// check what we got in GCS is different than our data
	getUDPMessage(&buffer);

	ASSERT_NOT_STR(&data,&buffer)

	stopUDPServer();

	printf("testTRXSendMeesage: end \n");
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
void testIsisAntS_initialize(void){
	ISISantsI2Caddress adress;
	adress.addressSideA=10;
	adress.addressSideB=11;
	int error=IsisAntS_initialize( &adress, 0);
	ASSERT_INT(error,E_NO_SS_ERR);
    error=IsisAntS_initialize( &adress, 0);
		ASSERT_INT(error,E_IS_INITIALIZED);
}

void testISIStrxvuIdleState(void){

	startUDPServer();
	char data[]="idle";
	char buffer[MAX_FRAME_LENGTH];

	IsisTrxvu_deinitialize(NULL);
	// test before trx init - should fail
	int er=IsisTrxvu_tcSetIdlestate(0,trxvu_idle_state_on);
	ASSERT_INT(er,E_NOT_INITIALIZED);

	// init trx and test that it now pass
	ISIStrxvuFrameLengths fl;
	fl.maxAX25frameLengthRX = 200;
	fl.maxAX25frameLengthTX = 200;
	er = IsisTrxvu_initialize(NULL,&fl,NULL,0);

	ASSERT_INT(er,E_NO_SS_ERR);
    er=IsisTrxvu_tcSetIdlestate(0,trxvu_idle_state_on);
	ASSERT_INT(er,E_NO_SS_ERR);
	printf("testISIStrxvuIdleState: after 3 tests \n");

	// TODO test that it sends "idle" messages.. + test turning off idle

	getUDPMessage(&buffer);
	ASSERT_STR(&data,&buffer)

    er=IsisTrxvu_tcSetIdlestate(0,trxvu_idle_state_off);
	ASSERT_INT(er,E_NO_SS_ERR);


    printf("testISIStrxvuIdleState: end of test \n");

	stopUDPServer();
}

void testIsisTrxvu_tcStartReadingQ(void){
	printf("testIsisTrxvu_tcStartReadingQ:start \n");
	startUDPServer();
	char data[]="test123456";
		char buffer[MAX_FRAME_LENGTH];

	IsisTrxvu_deinitialize(NULL);
		// test before trx init - should fail
		int er=IsisTrxvu_tcStartReadingQ(0);
		ASSERT_INT(er,E_NOT_INITIALIZED);

		ISIStrxvuFrameLengths fl;
			fl.maxAX25frameLengthRX = 200;
			fl.maxAX25frameLengthTX = 200;
			er = IsisTrxvu_initialize(NULL,&fl,NULL,0);
			ASSERT_INT(er,E_NO_SS_ERR);
		    er=IsisTrxvu_tcStartReadingQ(0);
			ASSERT_INT(er,E_NO_SS_ERR);

			xQueueSend(psend,data,100);
			getUDPMessage(&buffer);
				ASSERT_STR(&data,&buffer)
			stopUDPServer();

}

void testGetframeCount(void){

}
void testIsisTrxvu_rcGetCommandFrame(void){

	IsisTrxvu_deinitialize(NULL);
	ISIStrxvuRxFrame* pointer;

	          pointer->rx_framedata=100; ///< Pointer to an array receiving reception frame data.

	          int er=IsisTrxvu_rcGetCommandFrame(0,pointer);
	ASSERT_INT(er,E_NOT_INITIALIZED);

	   ISIStrxvuFrameLengths fl;
	     	fl.maxAX25frameLengthRX = 200;
			fl.maxAX25frameLengthTX = 200;
			IsisTrxvu_initialize(NULL,&fl,NULL,0);

	     char flag1=122333;
	     xQueueSend(pget,flag1,100);

	     char flag2=333221;
	   	     xQueueSend(pget,flag2,100);

		er=IsisTrxvu_rcGetCommandFrame(0,pointer);
		ASSERT_INT(er,E_NO_SS_ERR);
                                                        //checking if data got to place
		ASSERT_INT(flag1,pointer->rx_framedata);
                                                       //checking if removeing from Q
		IsisTrxvu_rcGetCommandFrame(0,pointer);
		ASSERT_INT(flag2,pointer->rx_framedata);

}

