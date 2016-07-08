#include "stdafx.h"
#include <stdio.h>
#include <winsock2.h>
#include <iostream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")

#define IP "192.168.1.34"

/*
[+] Author  : B3mB4m
[~] Contact : b3mb4m@protonmail.com
[~] Greetz  : Bomberman,T-Rex,Pixi
*/


int CALLBACK ConditionAcceptFunc(
    LPWSABUF lpCallerId,
    LPWSABUF lpCallerData,
    LPQOS pQos,
    LPQOS lpGQOS,
    LPWSABUF lpCalleeId,
    LPWSABUF lpCalleeData,
    GROUP FAR * g,
    DWORD_PTR dwCallbackData
    )
{


	 SOCKADDR_IN* pHost = (SOCKADDR_IN*)lpCallerId->buf;
	 if(inet_addr(IP)==pHost->sin_addr.S_un.S_addr){
		return CF_ACCEPT;
	 }else{
		return CF_REJECT;
	 }
		

}



int main(){
	WSADATA wsa;
	BOOL optval  = true;
	int iResult;
	int error;


	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr("");
    server.sin_family = AF_INET;
    server.sin_port = htons( 4444 );



	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0){
		printf("The Winsock dll not found!\n");
		return 0;
	}else{
		printf("The Winsock dll found!\n");
		printf("The status: %s.\n", wsa.szSystemStatus);
	}

	
	SOCKET Socket;
	Socket = WSASocketA(AF_INET, SOCK_STREAM, 0, 0, 0, 0);
	if (Socket == INVALID_SOCKET){
		return 1;
	}


	if (bind(Socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR){
		return 1;
	}
	
	
	
	setsockopt(Socket, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, (char *) &optval , 1 );
    iResult = listen( Socket, 0);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }



	error = WSAAccept( Socket, 0, 0, &ConditionAcceptFunc, 0);
	if (error == INVALID_SOCKET){
		printf("\nAccept failed.\n");
		return 1;
	}else
		printf("\nWelcome sir !\n");
	

}
