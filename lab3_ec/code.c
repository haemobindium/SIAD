#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<netdb.h>
#include<string.h>
//struct hostnet *gethostbyname(const char *name);

int main(int argc, char *argv[])
{

char *servername;
char *path;
int port;


printf("Client program \n");
if(argc!=3)
{

printf("Usage : %s <server> <port> \n", argv[0]);
exit(0);
}



servername = argv[1];
path=argv[2];
port = 80;
//atoi(argv[2]);

printf("Servername= %s , port=%d \n",servername,port);



int sockfd;

sockfd = socket(AF_INET, SOCK_STREAM, 0);

if(sockfd<0)
{
perror("ERROR opening socket");
}



struct hostent *server_he; //a host address entry
if ((server_he = gethostbyname(servername)) == NULL) {
        perror( " error in gethostbyname");
        return 2;
}

struct sockaddr_in serveraddr; // store the server's addr

bzero((char *) &serveraddr, sizeof(serveraddr));

serveraddr.sin_family = AF_INET;

bcopy((char *)server_he->h_addr,
(char *)&serveraddr.sin_addr.s_addr,
server_he->h_length);

serveraddr.sin_port = htons(port);


if(connect(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
{
perror("Cannot connect to the server");
exit(0);
}
else
printf("Connected to the server");


char request[255];
sprintf(request,"GET /%s HTTP/1.0\r\nHost:%s\r\n\r\n",path,servername);
char *msg = "GET / HTTP/1.0\r\n\r\n";
int bytes_sent;
printf("message:%s",request);
bytes_sent = send(sockfd, request, strlen(request) , 0);

char buffer[1024];
bzero(buffer,1024);

int byte_received;
bzero(buffer , 1024);
byte_received = recv(sockfd, buffer , 1024, 0);
if(byte_received < 0)
    error ("ERROR reading from socket");
printf("Message received : %s", buffer);




close(sockfd);
return 0;

}
