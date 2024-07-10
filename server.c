#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg){
	perror(msg);
	exit(1);	
}

void send_response(int sockfd, const char *status, const char *content_type, const char *body) {
    char response[1024];
    sprintf(response, "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %ld\r\n\r\n%s", status, content_type, strlen(body), body);
    write(sockfd, response, strlen(response));
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
	while (1) {
        	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        	if (newsockfd < 0) {
            		error("Error on accept");
        	}	
        
       		bzero(buffer, 1024);
        	read(newsockfd, buffer, 1023);
        
        	char *response_body = "<html><body><h1>Hello, World!</h1></body></html>";
        	send_response(newsockfd, "200 OK", "text/html", response_body);
        
        	close(newsockfd);
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
