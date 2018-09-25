//server
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
	SOCKET server = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(server == INVALID_SOCKET){
		printf("Socket failed with error : %d\n",WSAGetLastError());
        return end;
	}

	// struct to stock IP + PORT + Version Protocol(IPv4,IPv6,...)
	struct sockaddr_in serverInformation;
    serverInformation.sin_family = AF_INET; // AF_INET = IPv4
    serverInformation.sin_addr.s_addr = INADDR_ANY; // accept any address ip, or use hotsname or ip address
	serverInformation.sin_port = htons(port); // port

	// link socket with ip + port + protocole
	error = bind(server, (sockaddr*)&serverInformation, sizeof(serverInformation));
	if(error == INVALID_SOCKET){
		printf("Bind failed with error : %d\n",WSAGetLastError());
		closesocket(server);
		return end;
	}

	// place a socket in a state in which it is listening for an incoming connection
	error = listen(server, 5);
	if(error == SOCKET_ERROR){
		printf("listen failed with error : %d\n",WSAGetLastError());
		closesocket(server);
		return end;
	 }
	
	// Accept The Client
	SOCKET client;
	client= accept(server, 0, 0); 
	if(client == INVALID_SOCKET){
		printf("Server: can't accept the victim...\n");
		return end;
	}
	printf("[+] Connected To Client.\t(Success)\n\n\n\n");

	// chat
	int bytes;
	char in [256];
	char out[256];

	while(1){

		printf("[+] Client : ");

		//receive msg from client
		bytes = recv(client,in,sizeof(in),0);

		if(bytes == SOCKET_ERROR){
			//closesocket(client); 
			//return end; 
		}else{
			printf("%s\n",in);
		}

		printf("[+] Server : ");
		fgets(out, sizeof(out), stdin);
		printf("\n");

		//send msg to client
		bytes = send(client,out,sizeof(out),0);

		if(bytes != SOCKET_ERROR){
			//closesocket(client);
			//return end; 
		}else{
			
		}
	
	}

	// Shutdown the server
	closesocket(client);
	WSACleanup();

	printf("[+] Server : End Connection.\t(Shutdown)\n");

	system("pause");
	return 0;
}
