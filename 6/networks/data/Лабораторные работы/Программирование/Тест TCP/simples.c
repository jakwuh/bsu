#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_PORT 5001

int main(void) {

	char Buffer[128],c;
	unsigned short port=DEFAULT_PORT;
	int retval;
	int fromlen;
	int socket_type = SOCK_STREAM;   //TCP-protocol
	struct sockaddr_in local, from;
	WSADATA wsaData;
	SOCKET listen_socket, msgsock;

	if (WSAStartup(0x101,&wsaData) == SOCKET_ERROR) {
		fprintf(stderr,"WSAStartup failed with error %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}

   //Create a socket
	listen_socket = socket(AF_INET, socket_type,0); // TCP socket
	if (listen_socket == INVALID_SOCKET){
		fprintf(stderr,"Server: Error Opening socket: Error %d\n",
              WSAGetLastError());
		WSACleanup();
		return -1;
	}
	//
	// bind() associates a local address and port combination with the
	// socket just created.
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(port);  // Port MUST be in Network Byte Order

	if (bind(listen_socket,(struct sockaddr*)&local,sizeof(local) )
		== SOCKET_ERROR) {
		fprintf(stderr,"bind() failed with error %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}

	if (listen(listen_socket,5) == SOCKET_ERROR) {
		fprintf(stderr,"listen() failed with error %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}
	printf("Server listening on port %d , protocol TCP\n",port);

   fromlen =sizeof(from);

   msgsock = accept(listen_socket,(struct sockaddr*)&from, &fromlen);
   if (msgsock == INVALID_SOCKET) {
       fprintf(stderr,"accept() error %d\n",WSAGetLastError());
       WSACleanup();
       return -1;
   }
   printf("accepted connection from %s, port %d\n",
            inet_ntoa(from.sin_addr),
            htons(from.sin_port)) ;

   retval = recv(msgsock,Buffer,sizeof (Buffer),0 );
   if (retval == SOCKET_ERROR) {
      fprintf(stderr,"Server: recv() failed: error %d\n",WSAGetLastError());
      closesocket(msgsock);
      return -1;
   }
   if (retval == 0) {
      printf("Client closed connection\n");
      closesocket(msgsock);
      return -1;
   }
   printf("Received %d bytes, data [%s] from client\n",retval,Buffer);

   fprintf(stdout, "Input message\n");
   gets(Buffer);

   retval = send(msgsock,Buffer,sizeof(Buffer),0);
   if (retval == SOCKET_ERROR) {
      fprintf(stderr,"Server: send() failed: error %d\n",WSAGetLastError());
   }

   printf("Press Enter");
   c=getc(stdin);

   closesocket(msgsock);
   WSACleanup();
   return 0;
}


