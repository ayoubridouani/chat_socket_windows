//client
#include "stdafx.h"

#pragma comment(lib,"ws2_32.lib")
#include <stdio.h>
#include <WinSock2.h>
#include <windows.h>

#define true 1
#define false 0
#define end -1

int	error;
int const port = 1178;
char* const hostname = "192.168.1.4";
int main(void){
	
	// initialise WinSocket
	WORD wVersionRequested = MAKEWORD(2,2); // determine the version windows socket ===> 2
	WSAData lpwsdata; // pointer to stock all informations socket
	error = WSAStartup(wVersionRequested,&lpwsdata);
	if(error != false){ 
		printf("WSAStartup failed with error : %d\n",error);
		return end;
	}



	// create socket
	SOCKET client = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(client == INVALID_SOCKET){
		printf("Socket failed with error : %d\n",WSAGetLastError());
        return end;
	}

	struct hostent *host_entry = gethostbyname(hostname);
	
	// struct to stock IP + PORT + Version Protocol(IPv4,IPv6,...)
	struct sockaddr_in serverInformation;
    serverInformation.sin_family = AF_INET; // AF_INET = IPv4
    serverInformation.sin_addr.s_addr = *(unsigned long*) host_entry->h_addr;
	serverInformation.sin_port = htons(port); // port

	// connect client with server
	error = connect(client, (sockaddr*)&serverInformation, sizeof(serverInformation));
	while(error == SOCKET_ERROR){
	error = connect(client, (sockaddr*)&serverInformation, sizeof(serverInformation));
		if(error == SOCKET_ERROR){
			printf("Connect failed with error : %d\n",WSAGetLastError());
			return end;
		}
	}


	printf("[+] Connected To Server.\t(Success)\n\n\n\n");


	

	int bytes;
	char out[256];
	char in [256];
	while(1){
		
		printf("[+] Client : ");
		fgets(out, sizeof(out), stdin);
		printf("\n");

		//send msg to client
		bytes = send(client, out, sizeof(out), 0);

		if(bytes == SOCKET_ERROR){
			//closesocket(client); 
			//return end; 
		}else{
			
		}

		//receive msg from client
		bytes = recv(client,in,sizeof(in),0);

		if(bytes == SOCKET_ERROR){
			//closesocket(client); 
			//return end; 
		}else{
			printf("[+] Server : %s\n", in);
		}
	}


	// Shut down the server
	closesocket(client);
	WSACleanup();
	printf("\n[+] Disconnected From Server.\t(Shutdown)\n");



	system("pause");
	return 0;
}
