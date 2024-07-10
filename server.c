#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void dostuff(int);
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
	while(1){
		newsockfd=accept(sockfd, (struct sockaddr *) &cli_addr, clilen);
		if(newsockfd<0)
			error("error on accept");
		pid = fork()
		if (pid < 0)
             		error("ERROR on fork");
         	if (pid == 0)  {
             		close(sockfd);
             		dostuff(newsockfd);
             		exit(0);
         	}
		else close(newsockfd);
	}
	close(scokfd);
	return 0;
}

void dostuff (int sock){
   int n;
   char buffer[256];
   bzero(buffer,256);
   n = read(sock,buffer,255);
   if (n < 0) error("ERROR reading from socket");
   printf("Here is the message: %s\n",buffer);
   n = write(sock,"I got your message",18);
   if (n < 0) error("ERROR writing to socket");
}
