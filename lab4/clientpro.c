#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>

int bind(int serversockfd, struct sockaddr *serveraddr, socklen_t addrlen);
int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
int listen(int serversockfd, int backlog);
int accept(int sockfd, struct sockaddr *clientaddr, socklen_t *addrlen); 
int send(int sockfd, const void *msg, int len, int flags);
int serversockfd;

int main(int argc, char *argv[])
{

char servername[256];
printf("Client program\n");
if(argc!=3) 
{
printf("Usage: %s <server> <port>\n",argv[0]);
exit(0);
}
strcpy(servername,argv[1]);
printf("Server:");
printf(servername);
printf("\n");
serversockfd = socket(AF_INET, SOCK_STREAM, 0);
if (serversockfd < 0) {
 perror("ERROR opening socket");
 exit (1);
}

struct sockaddr_in {
 short int sin_family; // Address family, AF_INET
 unsigned short int sin_port; // Port number
 struct in_addr sin_addr; // Internet address
 unsigned char sin_zero[8]; // Same size as sockaddr
};

struct sockaddr_in serveraddr; /* server's addr */
//…
bzero((char *) &serveraddr, sizeof(serveraddr));
serveraddr.sin_family = AF_INET;
/* this is an Internet address */
serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
/* let the system figure out our IP address */
serveraddr.sin_port = htons(port);
/* this is the port we will listen on */
int optval = 1;
setsockopt(serversockfd, SOL_SOCKET, SO_REUSEADDR, &optval , sizeof(int));
if (bind(serversockfd,(struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
{
 perror("ERROR on binding");
exit(3);
}
//listen
if (listen(serversockfd, 5) < 0)
 {perror("ERROR on listen"); exit(1);}
printf(”Server is listening on port %d \n", port );
 
//accept
while (1) {
struct sockaddr_in clientaddr; /* client address */
/* wait to accept a connection from client */
int clientlen = sizeof(clientaddr);
int childfd = accept(serversockfd, (struct sockaddr *) &clientaddr, (socklen_t *) &clientlen);
if (childfd < 0)
 {
perror("ERROR on accept"); exit(2);}
printf("server established connection with %s\n",
 inet_ntoa(clientaddr.sin_addr));
/* create a process or thread to handle the
communication with this new socket, continue listen on the
server socket for new connections */
} 
//receive
int recv(int sockfd, void *buf, int len, int flags);
//example:
int byte_received;
bzero(buffer, 1024);
byte_received = recv(sockfd, buffer, 1024, 0);
if (byte_received < 0)
 {
perror("ERROR reading from socket"); 
exit(1);
}
printf(”Message received: %s", buffer);
//send data
char *msg = ”This is a test message from server";
int bytes_sent;
bytes_sent = send(sockfd, msg, strlen(msg), 0);
/* get message line from the user */
char buffer[1024];
printf(”Enter your message:");
bzero(buffer, 1024);
fgets(buffer, 1024, stdin);
bytes_sent = send(sockfd, buffer, strlen(msg), 0);
//receive
const int MB = 1024*1024; // a megabyte!
char buffer[MB];
memset(buffer,0, MB);
int recv_count = 0;
while((recv_count=recv(sockfd,buffer, MB,0))!=0) {
}

return 0;
}
