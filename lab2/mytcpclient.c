#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<netdb.h>
#include<strings.h>
//struct hostnet *gethostbyname(const char *name);

int main(int argc, char *argv[])
{

char *servername;
int port;


printf("Client program \n");
if(argc!=3)
{

printf("Usage : %s <server> <port> \n", argv[0]);
exit(0);
}



servername = argv[1];
port = atoi(argv[2]);

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

struct sockaddr_in serveraddr; //store the servers address

bzero((char *) &serveraddr, sizeof(serveraddr)); //prepare to copy: clear sockaddr_in structure /*(in netwok programming, we often need to initialize a field, copy the contents of one field to another */

serveraddr.sin_family = AF_INET; //ser the family to AF_INET (IPv4)

bcopy((char *)server_he->h_addr,       //copy the server address from gethostbyname(..), //return in struct hostent(stored in *server_he)
(char *)&serveraddr.sin_addr.s_addr,
server_he->h_length);

serveraddr.sin_port = htons(port);

if (connect(sockfd, (struct sockaddr *) &serveraddr,
sizeof(serveraddr))<0)
{
perror("cannot Connect to the server\n");
exit(0);
}
else
printf("Connected to the server \n");

//char request(255);
//sprintf(request, "GET/%s HTTP/1.0\r\nHost:%s\r\n\r\n");


char *msg= "This is a test message by bindu from client \n";
int bytes_sent;
bytes_sent = send(sockfd, msg, strlen(msg), 0);

char buffer[1024];
bzero(buffer,1024);

int byte_received;
bzero(buffer , 1024);
byte_received = recv(sockfd, buffer, 1024, 0);
if(byte_received < 0)
    error("ERROR reading from socket");
printf("Message Received bindu : %s", buffer);

close(sockfd);
return 0;

}
