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
#include <pthread.h>
#include "OBC.h"

// all local variables
Boolean _initFlag=FALSE;
ISIStrxvuFrameLengths _maxFrameLengths;
Boolean _initAnts=FALSE;
ISISantsI2Caddress _address;
ISIStrxvuRxFrame _rxframe;
Boolean _flagF_xQueueS_create = FALSE;

pthread_t thread_id;//pthread id for idle//

int IsisTrxvu_deinitialize(ISISantsI2Caddress* address){
	_initFlag = FALSE;
}


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
	xQueueS_Send( data,length);
	return E_NO_SS_ERR ;
}
/*
int QueueS_Create(char uxQueueLength, char uxItemSize){
	if(_flagF_xQueueS_create == FALSE)
	{
		_flagF_xQueueS_create = TRUE;
		if(access(QUEUE_FILE_NAME, F_OK ) != 0 ) {
			//createFRAMfile();
			char data[QUEUE_SIZE] = {0};
			fptr = fopen(QUEUE_FILE_NAME,"ab+");
			endPO = fseek(fptr , 0, SEEK_END);
			fwrite(data , sizeof(data), 1, fptr);
			fclose(fptr);

		}
		return E_NO_SS_ERR;
	}
	return E_IS_INITIALIZED;
}

int* xQueueS_Send(char data, char size)
{
	if(size <= QUEUE_SIZE){
			if(_flagF_xQueue_create == TRUE){
				if(fptr == NULL)
				{
					return E_FILE;
				}
				fseek(fptr , 0, SEEK_CUR);
				if(fptr + size >= endPO){
					return QUEUE_FULL;
				}else{
					fwrite(data , size , 1 , fptr);
					fclose(fptr);
				}
			}
			else{
				return E_NOT_INITIALIZED;
			}
			return E_NO_SS_ERR;
		}else{
			return E_TRXUV_FRAME_LENGTH;
		}

int IsisTrxvu_rcGetFrameCount(unsigned char index, unsigned short *frameCount){

	if(!_initFlag) return E_NOT_INITIALIZED;
		if (index!=0) return E_INDEX_ERROR;

		*frameCount= _rxframe.rx_length;

	if (index!=0) return E_INDEX_ERROR;


	return E_NO_SS_ERR ;
}


