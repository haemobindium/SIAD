#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netdb.h>
#include <string.h>

int main(int argc,char *argv[])
    {
	int sockfd;
	int port;
	char *servername;
        int serversockfd;
        int optval = 1;
        
	printf("hello,i am client\n");
	servername =  argv[1];
	struct hostent *server_he;
	//struct hostent *gethostbyname(const char *name);
	char buffer[1024];
	int bytes_sent;
	int byte_received;
        char *msg ="Hello I am Client ";
        int client;
	if (argc!=2)
	{
	printf("Usage: %s <server> <port>\n", argv[0]);
	exit(0);
	}
	port =atoi(argv[1]);
	//printf("Servername= %s ,port=%d\n", servername,port);
        //socket
	serversockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
	perror("Not valid");
	exit(1);
	}
	
	struct sockaddr_in serveraddr;
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(port);       
        setsockopt(serversockfd, SOL_SOCKET, SO_REUSEADDR, &optval,sizeof(int));
        //Binding
        if(bind(serversockfd,(struct sockaddr *) &serveraddr,sizeof(serveraddr))<0){
        perror("ERROR on binding");
        exit(3);
           }
        //Listen
        int listen(int serversockfd,int backlog);
        if(listen(serversockfd, 5)< 0)
        {
        perror("ERROR on listen");
       exit(1);
        }
        printf("Server is listening on port %d \n", port);
        while(1) {
        struct sockaddr_in clientaddr;
        int clientlen = sizeof(clientaddr);
        //accept
        int childfd = accept(serversockfd,(struct sockaddr *)&clientaddr,(socklen_t *)&clientlen);
        if (childfd < 0)
        {
         perror("ERROR on accept");exit(2);
         }
        printf("server established connectin with %s\n",inet_ntoa(clientaddr.sin_addr));
        //send
        bytes_sent=send(sockfd,msg,strlen(msg),0);
        char buffer[1024];
        printf("enter message");
        //bzero(buffer,1024);
        //fgets(buffer,1024,stdin);
        bytes_sent=send(childfd,msg,strlen(msg),0);
        bzero(buffer ,1024);
        //Receive
        byte_received =recv(childfd,buffer,1024,0);
        if(byte_received <0)
         {perror("ERROR reading from socket"); exit(1);}
         printf("Message received: %s",buffer);	
		return 0;
}
}
