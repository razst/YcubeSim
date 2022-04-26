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

void IsisTrxvu_deinitialize(ISISantsI2Caddress* address){
	_initFlag = FALSE;
}


int IsisTrxvu_initialize(ISIStrxvuI2CAddress *address, ISIStrxvuFrameLengths *maxFrameLengths, ISIStrxvuBitrate* default_bitrates, unsigned char number){
	if(_initFlag) return E_IS_INITIALIZED;

	_maxFrameLengths.maxAX25frameLengthRX = maxFrameLengths->maxAX25frameLengthRX;
	_maxFrameLengths.maxAX25frameLengthTX = maxFrameLengths->maxAX25frameLengthTX;

	psend=xQueueCreate(10,10);
	pget=xQueueCreate(10,10);
	//IsisTrxvu_tcStartReadingQ(50);
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

int sendIdle(void *vargp){
	char data[] = "idle";
	char avail=0;
	while(1==1){

		IsisTrxvu_tcSendAX25DefClSign(0, data,strlen(data), &avail);
		usleep(100000);
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

	printf("sendfromQ:start \n");
	 char*buffer=malloc(psend->uxItemSize);
	printf("sendfromQ:starting infinite while loop \n");
	while(2>0){
		sleep(3);
		printf("sendfromQ:in loop \n");
		if(xQUsedCount(psend)!=0){
			printf("sendfromQ:receiving from Q \n");
			void* res=xQueueReceive(psend,buffer,10);

			sendUDPMessage(res,sizeof(res));
			printf("sendfromQ:after sendUDPMessage \n");
		}
	}
}

int IsisTrxvu_tcStartReadingQ(unsigned char index){
    printf("IsisTrxvu_tcStartReadingQ:start \n");
	if(!_initFlag) return E_NOT_INITIALIZED;
	pthread_create(&thread_id, NULL, sendfromQ, NULL);
    printf("IsisTrxvu_tcStartReadingQ:thread created. end. \n");

	return E_NO_SS_ERR;
}


int sendUDPMessage(unsigned char *data, unsigned char length){
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

int IsisTrxvu_tcSendAX25DefClSign(unsigned char index, unsigned char *data, unsigned char length, unsigned char *avail){


	if(!_initFlag) return E_NOT_INITIALIZED;
	if (index!=0) return E_INDEX_ERROR;

	/*sendUDPMessage(data, length);
	 */
	printf("IsisTrxvu_tcSendAX25DefClSign:start \n");
	xQueueSend(psend,data,100);

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
