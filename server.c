#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void error(char *msg){
	perror(msg);
	exit(1);	
}
int main(int argc, char *argv[]){
	int sockfd, newsockfd, portno, clilen, n;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	if (argc<2){
		fprintf(stderr, "no port provided");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0){
		error("error opening socket");	
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno=atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd, (struct sockaddr *) &serv_addr, 
		sizeof(serv_addr))<0)
		error("error on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd<0)
		error("error on accept");
	bzero(buffer,256);
	n=read(newsockfd, buffer, 255);
	if(n<0) error("error writing to socket");
	printf("here is the message %s",buffer);
	n = write(newsockfd,"I got your message",18);
	if (n < 0) error("ERROR writing to socket");
	return 0;
}
