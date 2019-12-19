// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include "parser.h" 
#define PORT 9999 
   

//     int BytesSent, nlen;
     int i;
     int timer;
     uint8_t frame[255];
     char tbuffer[33];


int main(int argc, char const *argv[]) 
{ 
    readkeys();
    int sock = 0, BytesSent; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
    char sendbuf[1024];
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

     setup(0,sendbuf);
     send(sock, sendbuf, ((sendbuf[4]+5) &0xff ), 0);
     recv(sock , buffer, 1024,0);
     printf("\n");
     printf("Incoming Message\n");
	 for(i =0;i < buffer[4]+5;i++){printf("%02X ",buffer[i]&0xff);}
     printf("\n");

     setup(1,sendbuf);
     send(sock, sendbuf, ((sendbuf[4]+5) &0xff ), 0);
     recv(sock , buffer, 1024,0);
     printf("\n");
     printf("Incoming Message\n");
	 for(i =0;i < buffer[4]+5;i++){printf("%02X ",buffer[i]&0xff);}
     printf("\n");

     setup(2,sendbuf);
     send(sock, sendbuf, ((sendbuf[4]+5) &0xff ), 0);
     recv(sock, buffer, 1024,0);
     printf("\n");
     printf("Incoming Message\n");
	 for(i =0;i < buffer[4]+5;i++){printf("%02X ",buffer[i]&0xff);}
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

            genemm(sendbuf);
            memcpy(&sendbuf[43],&frame[0],(frame[2]+3));
            sendbuf[42] = frame[2]+3;
            for(int i =0;i < 0xcf;i++){printf("%02X ",sendbuf[i]&0xff);}
            printf("\n");
            BytesSent = send(sock, sendbuf, ((sendbuf[4]+5) &0xff ), 0);

     if(BytesSent == SO_ERROR)
          printf("Client: send() error.\n");
     else
     {
          printf("Client: send() is OK - bytes sent: %d\n", BytesSent);
     }
     usleep(50000);
        }
    file.close();
    printf("Database processed... Continue sending NULL-Packets\n");
    timer = (time(0)+120);
    }
    else printf("ERROR: database.bin not found! \n");
    timer = (time(0)+120);
    }


	genemm(sendbuf);
	BytesSent = send(sock, sendbuf, ((sendbuf[4]+5) &0xff ), 0);

	if(BytesSent == SO_ERROR)
          printf("Client: send() error .\n");
	else
     {
          //printf("Client: send() is OK - bytes sent: %d\n", BytesSent);
     }

usleep(50000);
}
    return 0; 
} 
