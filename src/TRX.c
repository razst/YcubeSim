/*
 * TRX.c
 *
 *  Created on: 6/12/20
 *      Author: Emmanuel Gelkop
 */
#include "TRX.h"


// all local variables
Boolean _initFlag=FALSE;
ISIStrxvuFrameLengths _maxFrameLengths;
Boolean _initAnts=FALSE;
ISISantsI2Caddress _address;
ISIStrxvuRxFrame _rxframe;
Boolean _flagF_xQueueS_create = FALSE;
pthread_t thread_id;//pthread id for idle//
pthread_t thread_id2;//pthread id for Q sending//
Boolean flag_thread2=FALSE;

void IsisTrxvu_deinitialize(ISISantsI2Caddress* address){
	_initFlag = FALSE;
}


int IsisTrxvu_initialize(ISIStrxvuI2CAddress *address, ISIStrxvuFrameLengths *maxFrameLengths, ISIStrxvuBitrate* default_bitrates, unsigned char number){
	if(_initFlag) return E_IS_INITIALIZED;

	_maxFrameLengths.maxAX25frameLengthRX = maxFrameLengths->maxAX25frameLengthRX;
	_maxFrameLengths.maxAX25frameLengthTX = maxFrameLengths->maxAX25frameLengthTX;

	psend=xQueueCreate(80,10);
	pget=xQueueCreate(80,10);
	_initFlag=TRUE;
	IsisTrxvu_tcStartReadingQ(50);

	return E_NO_SS_ERR;
}

int IsisAntS_initialize(ISISantsI2Caddress* address, unsigned char number){
	if(_initAnts) return E_IS_INITIALIZED;
	_address.addressSideA=address->addressSideA;
	_address.addressSideB=address->addressSideB;
	_initAnts=TRUE;
	return E_NO_SS_ERR;
}

int sendIdle(void *vargp){
	char data[] = "idle";
	char avail=0;
	while(1==1){

		IsisTrxvu_tcSendAX25DefClSign(0, data,strlen(data), &avail);
		sleep(10);
	}
}

int IsisTrxvu_tcSetIdlestate(unsigned char index, ISIStrxvuIdleState state){
	if(!_initFlag) return E_NOT_INITIALIZED;
	if (state==trxvu_idle_state_on){
		pthread_create(&thread_id, NULL, sendIdle, NULL);
	}else{
		pthread_cancel(thread_id);
	}
	return E_NO_SS_ERR ;
}

int sendfromQ(){

	printf("                                            sendfromQ:start \n");
	unsigned char*buffer=malloc(psend->uxItemSize);

	while(2>0){
		sleep(3);

      printf("                                           sendfrom Q : the Q SIZE is: %d \n",xQUsedCount(psend));
		if(xQUsedCount(psend)!=0){
			printQ(psend);
			printf("                                     sendfromQ:receiving from Q \n");
			int res=xQueueReceive(psend,buffer,10);
            printf("                                     sendfrom q :the data is %s  \n",buffer);
			int	err=sendUDPMessage(buffer,sizeof(buffer));
			printf("                                     sendfromQ:after sendUDPMessage %d \n", err);


		}
	}
}

int IsisTrxvu_tcStartReadingQ(unsigned char index){
    printf("IsisTrxvu_tcStartReadingQ:start \n");
    if(!_initFlag) return E_NOT_INITIALIZED;
    if(flag_thread2) return E_NOT_INITIALIZED;
	pthread_create(&thread_id2, NULL, sendfromQ, NULL);
    printf("IsisTrxvu_tcStartReadingQ:thread created. end. \n");

    flag_thread2=TRUE;
	return E_NO_SS_ERR;
}

int IsisTrxvu_tcStartReadingQ_killThread(unsigned char index){
    printf("IsisTrxvu_tcStartReadingQ_killThread:start \n");

	pthread_cancel(thread_id2);
	flag_thread2=FALSE;
	return E_NO_SS_ERR;
}


int sendUDPMessage_old(unsigned char *data, unsigned char length){
    int sockfd;
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
    servaddr.sin_addr.s_addr  = INADDR_BROADCAST;
    //servaddr.sin_addr.s_addr   = inet_addr("192.168.14.118");
    //servaddr.sin_addr.s_addr = INADDR_ANY;


    sendto(sockfd, (const char *)data,length,
    //sendto(sockfd, &messageX, sizeof(messageX),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
    printf("Message sent.\n");

    close(sockfd);
    return E_NO_SS_ERR ;
}


int sendUDPMessage(unsigned char *data, unsigned char length) {
//	int s;
//	unsigned short port;
//	struct sockaddr_in server;
//	char buf[32];
//
//	port = htons(20001);
//
//	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
//		printf("sdnbhjx");
//		return 111;
//	}
//	server.sin_family = AF_INET; /* Internet Domain    */
//	/*    server.sin_port        = port;               /* Server Port        */
//	/*    server.sin_addr.s_addr = inet_addr("192.168.137.69"); /* Server's Address   */
//
//	data = "12345";
//	strcpy(buf, data);
//
//	if (sendto(s, buf, (strlen(buf) + 1), 0, (struct sockaddr*) &server,
//			sizeof(server)) < 0) {
//		printf("12321");
//		return 111;
//	}
//	printf("after sending");
//	close(s);

//	int sockfd;
//	struct sockaddr_in servaddr;
//	// Creating socket file descriptor
//	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//	if (sockfd < 0) {
//		perror("socket creation failed");
//		printf("Unable to open socket\n");
//		return 111;
//	}
//
//	// set socket options enable broadcast
//	int broadcastEnable = 1;
//	int ret = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable,
//			sizeof(broadcastEnable));
//	if (ret) {
//		printf("Unable to set broadcast option\n");
//		close(sockfd);
//		return 111;
//	}
//
//	memset(&servaddr, 0, sizeof(servaddr));
//
//	// Filling server information
//	servaddr.sin_family = AF_INET;
//	servaddr.sin_port = htons(1234);
//	//servaddr.sin_addr.s_addr  = INADDR_BROADCAST;
//	servaddr.sin_addr.s_addr = inet_addr("1");
//	//servaddr.sin_addr.s_addr = INADDR_ANY;
//	//////////////////////////////////////////////////////////  char data="hello";
//	//////////////////////////////////////////////////////////  char length=sizeof(data);
//
//	sendto(sockfd, (const char*) data, length,
//	//sendto(sockfd, &messageX, sizeof(messageX),
//			MSG_CONFIRM, (const struct sockaddr*) &servaddr, sizeof(servaddr));
//	printf("Message sent.\n");
//
//	close(sockfd);
//
	printf(" sendUDPMessage:the data is %s \n",data);

	int s;
	unsigned short port;
	struct sockaddr_in server;

	port = htons(DOWN_PORT);

	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("sdnbhjxn");
		return 111;
	}
	server.sin_family = AF_INET; /* Internet Domain    */
	server.sin_port = port; /* Server Port        */
	server.sin_addr.s_addr = inet_addr("0.0.0.0"); /* Server's Address   */


	if (sendto(s, data, (strlen(data) + 1), 0, (struct sockaddr*) &server,
			sizeof(server)) < 0) {
		printf("1232\n");
		return 111;
	}
	close(s);
	//LZ - end
	printf("Starting 123 ...\n");

	return 0;
}
int IsisTrxvu_tcSendAX25DefClSign(unsigned char index, unsigned char *data, unsigned char length, unsigned char *avail){


	if(!_initFlag) return E_NOT_INITIALIZED;
	if (index!=0) return E_INDEX_ERROR;

	/*sendUDPMessage(data, length);
	 */
	char newdata [psend->uxItemSize];
	for (int i=0;i<length;i++){
		newdata[i]=data[i];
	}
	for (int i=length;i<psend->uxItemSize;i++){
		newdata[i]=0xff;
	}

	printf("IsisTrxvu_tcSendAX25DefClSign:start \n");
    sleep(10);
	printf("now   \n");
	xQueueSend(psend,newdata,100);
	printf("IsisTrxvu_tcSendAX25DefClSign:after xQsend \n");
	/*

		char  ch[10];
		xQueueReceive(psend,ch,10);
		printf("IsisTrxvu_tcSendAX25DefClSign:received from Queue: %s \n",&ch[0]);
		xQueueSend(psend,data,100);
		printf("IsisTrxvu_tcSendAX25DefClSign:Queue Count after QueueSend: %d \n",xQUsedCount(psend));
		xQueueReceive(psend,ch,10);
		printf("IsisTrxvu_tcSendAX25DefClSign:received from Queue: %s \n",&ch[0]);

	 */
	//printf("\n beforeqcount \n");
	//*avail=(unsigned char) xQUsedCount(psend);
	//printf("\n afterQcount \n");
	return E_NO_SS_ERR ;
}

int IsisTrxvu_rcGetFrameCount(unsigned char index, unsigned short *frameCount){

	if(!_initFlag) return E_NOT_INITIALIZED;


	*frameCount=xQUsedCount(pget);
	return E_NO_SS_ERR;
}

int IsisTrxvu_rcGetCommandFrame(unsigned char index, ISIStrxvuRxFrame *rx_frame){
	if(!_initFlag) return E_NOT_INITIALIZED;
	int check=xQueueReceive(pget,rx_frame->rx_framedata,100);
	return check||E_NO_SS_ERR ;
}

int IsisTrxvu_tcSetAx25Bitrate(unsigned char index, ISIStrxvuBitrate bitrate){
	return E_NO_SS_ERR;
}
