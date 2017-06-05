#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>

int main(int argc, char *argv[])
{

char req[5555],host[99], path[99];
char buffer[55555];
int port=80;
printf("Welcome to Client program \n");
strcpy(req,argv[1]);
sscanf(req,"http://%[^/]/%s",host,path);

if(argc!=2)
{
printf("Usage : %s <server> <port> \n", argv[0]);
exit(0);
}

int sockfd;
sockfd = socket(AF_INET, SOCK_STREAM, 0);

if(sockfd<0)
{
perror("ERROR opening socket");
}

struct hostent *server_he; //a host address entry
if ((server_he = gethostbyname(host)) == NULL) {
        perror( " error in gethostbyname");
        return 2;
}

struct sockaddr_in serveraddr; // store the server's addr

bzero((char *) &serveraddr, sizeof(serveraddr));
serveraddr.sin_family = AF_INET;
bcopy((char *)server_he->h_addr,(char *)&serveraddr.sin_addr.s_addr,server_he->h_length);
serveraddr.sin_port = htons(port);

if(connect(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
{
perror("Cannot connect to the server");
exit(0);
}
else
printf("Connected to the server");


char req1[255];
sprintf(req1,"GET /%s HTTP/1.0\r\nHost:%s\r\n\r\n",path,host);
printf(req1,"Host=%s\r\n\r\n",path);
int bytes_sent;
printf("Message:%s",req1);
bytes_sent = send(sockfd, req1, strlen(req1) , 0);
bzero(buffer,10000);
int byte_recv;
byte_recv=recv(sockfd,buffer,10000,0);
if(byte_recv<0)
	error("Socket:Error");
printf("Message received: %s",buffer);

//searches for the last occurrence of the character c
//Can be used to get a filename URL Input
//Search in a string
char *data=strstr(buffer, "\r\n\r\n");
char ch= '/';
char *file;
file = strrchr(req,ch);	


//Parse the HTTP response code – format:
int code;
sscanf(buffer,"HTTP/1.%*[01] %d ",&code); //int sscanf(const char *str, const char *format, ...)

if(code!=200){
	char err[100];
	sscanf(buffer,"%[^\r]",err);
	printf("\nStatus Message is %s\n",err);
}	
else{

printf("HTTP Request is successful.\n");
	if(file!=NULL)
	{
		FILE *ofile= fopen(file+1,"w");			
		int bytes_remain=(byte_recv)-((data-buffer)+4);
		fwrite(data+4,bytes_remain,1,ofile);
		while((byte_recv=recv(sockfd,buffer,10000,0))!=0)
			fwrite(buffer,byte_recv,1,ofile);
		fclose(ofile);		
		
	}
	else 
	{
		FILE *record;
		record = fopen("index.html","w");
		
		int bytes_remain=(byte_recv)-((data-buffer)+4);
		fwrite(data+4,bytes_remain,1,record);
		while((byte_recv=recv(sockfd,buffer,10000,0))!=0)
			fwrite(buffer,byte_recv,1,record);
		fclose(record);	
	}
return 0;

}

}


