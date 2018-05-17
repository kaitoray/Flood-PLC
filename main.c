/* connect.c
it is used to connect PLC
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>     /* Note: winsock2.h has included windows.h */
#include <conio.h>  //Include keyboard listening function kbhit()
#include <time.h>
#include "reference.h"

SOCKET        newsocket;   /* defined in winsock2.h */
byte sendMessageStr[100]; /* message to be sent to server */
byte SessionHandle1, SessionHandle2, SessionHandle3, SessionHandle4;	/*session handle value*/
byte ConnectionID1, ConnectionID2, ConnectionID3, ConnectionID4;		/*connection ID*/
byte CIPCount1 = 0xfa, CIPCount2 = 0x00;
char  recvBuffer[100], input=0;
int sendStatus, recvStatus, i;


int main(void)
{
	WSADATA       wsa_data;           /* defined in winsock2.h */
	struct sockaddr_in HMI;     /* defined in winsock2.h */
	struct hostent     *host = NULL;  /* defined in winsock2.h */

	//double time_old, time_new, time_interval = 0;


	printf("======== Connect to PLC ========\n\n");

	/* Step 1: startup winsocket - this is for Windows only */
	/* in pair with WSACleanup()                    */
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
	{
		puts("WSAStartup failed!");
		exit(1);
	}

	/* Step 2: Create socket and check it is successful */
	/* in pair with closesocket()               */
	for (;;)
	{
		newsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (newsocket == INVALID_SOCKET)
		{
			printf("Failed to create socket(): %d\n", WSAGetLastError());
			exit(1);
		}

		/* Step 3: Setup TCP Server Parameters */
		HMI.sin_family = AF_INET;
		HMI.sin_addr.s_addr = inet_addr(MY_SERVER_IP_ADDRESS); /* defined in tcpserverclient.h */
		HMI.sin_port = htons(MY_SERVER_PORT_NUMBER);           /* defined in tcpserverclient.h */

															   /* Step 3.2: Connect to the TCP Server */
		if (connect(newsocket, (struct sockaddr *)&HMI, sizeof(HMI)) == SOCKET_ERROR)
		{
			printf("connect() failed: %d\n", WSAGetLastError());
			exit(1);
		}

		/* Step 4: Listen */
		listen(newsocket, 8);

		/*Step 5: Initialization */
		// Register session
		byte Rgsession[] = { 0x65, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x44, 0x56, 0x41, 0x4e, 0x43, 0x45, 0x44, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
		sendStatus = send(newsocket, Rgsession, 28, 0);
		// Receive session number
		recvStatus = recv(newsocket, recvBuffer, 128, 0);
		// Store session number
		//SessionHandle1 = recvBuffer[4];
		//SessionHandle2 = recvBuffer[5];
		//SessionHandle3 = recvBuffer[6];
		//SessionHandle4 = recvBuffer[7];
		recvBuffer[recvStatus] = 0x00; /* '\0' */

		//Ask for connection ID
		//byte connetionmanager[] = {0x6f, 0x00, 0x40, 0x00, SessionHandle1, SessionHandle2, SessionHandle3, SessionHandle4, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb2, 0x00, 0x30, 0x00, 0x54, 0x02, 0x20, 0x06, 0x24, 0x01, 0x07, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x41, 0x52, 0x43, 0x48, 0x49, 0x45, 0x02, 0x00, 0x00, 0x00, 0x80, 0x84, 0x1e, 0x00, 0xfc, 0x43, 0x80, 0x84, 0x1e, 0x00, 0xfc, 0x43, 0xa3, 0x03, 0x01, 0x00, 0x20, 0x02, 0x24, 0x01 };
		//sendStatus = send(newsocket, connetionmanager, 88, 0);
		// Receive session number
		//recvStatus = recv(newsocket, recvBuffer, 128, 0);
		//ConnectionID1 = recvBuffer[44];
		//ConnectionID2 = recvBuffer[45];
		//ConnectionID3 = recvBuffer[46];
		//ConnectionID4 = recvBuffer[47];
		//recvBuffer[recvStatus] = 0x00; /* '\0' */
	}
	return 0;
}



