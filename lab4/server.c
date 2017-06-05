#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<netdb.h>
#include<string.h>

int main(int argc, char *argv[])
{

	char *servername;
	char *path;
	int port;
	printf("Client program \n");
	if(argc!=2)
	{
	printf("Usage : %s <port> \n", argv[0]);
	exit(0);
	}

	servername = argv[1];
	path=argv[2];
	port= atoi(argv[1]);
	printf("Servername= %s , port=%d \n",servername,port);
	int sockfd;
	int serversockfd;
	serversockfd = socket(AF_INET, SOCK_STREAM, 0);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(serversockfd<0)
	{
	perror("ERROR opening socket");
	}
	struct sockaddr_in serveraddr; 
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(port);
	
	int optval =1;
	setsockopt(serversockfd, SOL_SOCKET , SO_REUSEADDR , &optval , sizeof(int));
	if(bind (serversockfd,(struct sockaddr * ) &serveraddr , sizeof(serveraddr))< 0)
	{
	perror ("ERROR on binding");
	exit(3);
	}

	int listen (int serversockfd , int backlog);
	if(listen(serversockfd,5)<0)
	{
	perror("ERROR on listen"); exit(1);
	}
	printf("Server is listening on port %d \n" ,port);

	while(1)
	{

	struct sockaddr_in clientaddr;

	int clientlen = sizeof(clientaddr);
	int childfd = accept(serversockfd, (struct sockaddr *) &clientaddr , (socklen_t *) &clientlen);

	if(childfd<0)
	{
	perror("ERROR on accept ") ;
	exit(2);

	}

	printf("server established connection with %s \n",inet_ntoa(clientaddr.sin_addr));

	int byte_received;
	char buffer[1024];
	bzero(buffer, 1024);
	byte_received = recv(childfd, buffer, 1024, 0);

	if (byte_received < 0)
	 {
		perror("ERROR reading from socket"); 
		exit(1);
	}
	printf("Message received: %s", buffer);

	char *msg = "This is a test message from server: ";
	int bytes_sent;
	bytes_sent = send(childfd, msg, strlen(msg), 0);
	/* get message line from the user */
	char buffer2[1024];
	printf("Enter your message:");
	bzero(buffer2, 1024);
	fgets(buffer2, 1024, stdin);
	bytes_sent = send(childfd, buffer2,strlen(msg), 0);
	}
	close(sockfd);
	close(serversockfd);
	return 0;
}
	

