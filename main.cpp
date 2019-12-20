#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include "parser.h"
uint8_t frame[255];
char tbuffer[33];
int timer;

int main(int argc, char **argv)
{

     WSADATA              wsaData;
     SOCKET               SendingSocket;
     // Server/receiver address
     SOCKADDR_IN          ServerAddr, ThisSenderInfo;
     // Server/receiver port to connect to
     int  RetCode;
     // Be careful with the array bound, provide some checking mechani
     char sendbuf[1024];
     char buffer[1024];
     int BytesSent, nlen;
     unsigned int port;
     if(argc != 2){
        fprintf(stderr,"No Port defined! Exiting...\n");
        return -1;
     }

    readkeys();
    port = atoi(argv[1]);

     // Initialize Winsock version 2.2
     WSAStartup(MAKEWORD(2,2), &wsaData);
     printf("Client: Winsock DLL status is %s.\n", wsaData.szSystemStatus);

     // Create a new socket to make a client connection.
     // AF_INET = 2, The Internet Protocol version 4 (IPv4) address family, TCP protocol
     SendingSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
     if(SendingSocket == INVALID_SOCKET)
     {
          printf("Client: socket() failed! Error code: %d\n", WSAGetLastError());
          // Do the clean up
          WSACleanup();
          // Exit with error
          return -1;
     }
     else
          printf("Client: socket() is OK!\n");

     // Set up a SOCKADDR_IN structure that will be used to connect
     // to a listening server on port 5150. For demonstration
     // purposes, let's assume our server's IP address is 127.0.0.1 or localhost

     // IPv4
     ServerAddr.sin_family = AF_INET;
     // Port no.
     ServerAddr.sin_port = htons(port);
     // The IP address
     ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

     // Make a connection to the server with socket SendingSocket.
     RetCode = connect(SendingSocket, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr));
     if(RetCode != 0)
     {
          printf("Client: connect() failed! Error code: %d\n", WSAGetLastError());
          // Close the socket
          closesocket(SendingSocket);
          // Do the clean up
          WSACleanup();
          // Exit with error
          return -1;
     }
     else
     {
          printf("Client: connect() is OK, got connected...\n");
          printf("Client: Ready for sending and/or receiving data...\n");
     }

     // At this point you can start sending or receiving data on
     // the socket SendingSocket.

     // Some info on the receiver side...
     getsockname(SendingSocket, (SOCKADDR *)&ServerAddr, (int *)sizeof(ServerAddr));
     printf("Client: Receiver IP(s) used: %s\n", inet_ntoa(ServerAddr.sin_addr));
     printf("Client: Receiver port used: %d\n", htons(ServerAddr.sin_port));

     setup(0,sendbuf);
     send(SendingSocket, sendbuf, ((sendbuf[4]+5) &0xff ), 0);
     recv(SendingSocket , buffer, 1024,0);
     printf("\n");
     printf("Incoming Message\n");
	 for(int i =0;i < buffer[4]+5;i++){printf("%02X ",buffer[i]&0xff);}
     printf("\n");

     setup(1,sendbuf);
     send(SendingSocket, sendbuf, ((sendbuf[4]+5) &0xff ), 0);
     recv(SendingSocket , buffer, 1024,0);
     printf("\n");
     printf("Incoming Message\n");
	 for(int i =0;i < buffer[4]+5;i++){printf("%02X ",buffer[i]&0xff);}
     printf("\n");

     setup(2,sendbuf);
     send(SendingSocket, sendbuf, ((sendbuf[4]+5) &0xff ), 0);
     recv(SendingSocket , buffer, 1024,0);
     printf("\n");
     printf("Incoming Message\n");
	 for(int i =0;i < buffer[4]+5;i++){printf("%02X ",buffer[i]&0xff);}
     printf("\n");

     while(true){

     if(timer <= time(0)){
     ifstream file("database.bin", ios::in|ios::binary|ios::ate);
      if (file.is_open())
    {
        file.seekg(0, ios::beg);
        while(!file.eof()){
            file.read (tbuffer,33);
            parse(frame,tbuffer);
            printf("EMM to SEND: \n");
            for (int i=0;i <=(frame[2]+2) ;i++){printf("%02X ",frame[i]);}
            printf("\n");
            genframe(sendbuf);

            copyemm(sendbuf,frame);

            for(int i =0;i < 0xcf;i++){printf("%02X ",sendbuf[i]&0xff);}
            printf("\n");
            BytesSent = send(SendingSocket, sendbuf, ((sendbuf[4]+5) &0xff ), 0);

     if(BytesSent == SOCKET_ERROR)
          printf("Client: send() error %d.\n", WSAGetLastError());
     else
     {
          printf("Client: send() is OK - bytes sent: %d\n", BytesSent);
          memset(&ThisSenderInfo, 0, sizeof(ThisSenderInfo));
          nlen = sizeof(ThisSenderInfo);

          getsockname(SendingSocket, (SOCKADDR *)&ThisSenderInfo, &nlen);
          printf("Client: Sender IP(s) used: %s\n", inet_ntoa(ThisSenderInfo.sin_addr));
          printf("Client: Sender port used: %d\n", htons(ThisSenderInfo.sin_port));
     }
     Sleep(50);
        }
    file.close();
    printf("Database processed... Continue sending NULL-Packets\n");
    timer = (time(0)+120);
    }
    else printf("ERROR: database.bin not found! \n");
    timer = (time(0)+120);
    }
     genframe(sendbuf);
     BytesSent = send(SendingSocket, sendbuf, ((sendbuf[4]+5) &0xff ), 0);

     if(BytesSent == SOCKET_ERROR){
        printf("Client: send() error %d.\n", WSAGetLastError());
        return 0;

     }
     else
     {
          memset(&ThisSenderInfo, 0, sizeof(ThisSenderInfo));
          nlen = sizeof(ThisSenderInfo);

          getsockname(SendingSocket, (SOCKADDR *)&ThisSenderInfo, &nlen);
     }

Sleep(50);
}

     if( shutdown(SendingSocket, SD_SEND) != 0)
          printf("Client: Well, there is something wrong with the shutdown().The error code: %d\n", WSAGetLastError());
     else
          printf("Client: shutdown() looks OK...\n");
     // When you are finished sending and receiving data on socket SendingSocket,
     // you should close the socket using the closesocket API. We will
     // describe socket closure later in the chapter.
     if(closesocket(SendingSocket) != 0)
          printf("Client: Cannot close \"SendingSocket\" socket. Error code: %d\n", WSAGetLastError());
     else
          printf("Client: Closing \"SendingSocket\" socket...\n");

     // When your application is finished handling the connection, call WSACleanup.
     if(WSACleanup() != 0)
          printf("Client: WSACleanup() failed!...\n");
     else
          printf("Client: WSACleanup() is OK...\n");
     return 0;
}


