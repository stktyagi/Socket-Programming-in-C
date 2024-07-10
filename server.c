#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

void error(char *msg){
    perror(msg);
    exit(1);    
}

void send_response(int sockfd, const char *status, const char *content_type, const char *body) {
    char response[1024];
    sprintf(response, "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %ld\r\n\r\n%s",
            status, content_type, strlen(body), body);
    write(sockfd, response, strlen(response));
}

struct http_request {
    char method[10];
    char path[256];
    char version[10];
};

void parse_request(char *buffer, struct http_request *req) {
    sscanf(buffer, "%s %s %s", req->method, req->path, req->version);
}

void handle_route(int sockfd, struct http_request *req) {
    if (strcmp(req->path, "/") == 0) {
        send_response(sockfd, "200 OK", "text/html", "<html><body><h1>Home Page</h1></body></html>");
    } else if (strcmp(req->path, "/about") == 0) {
        send_response(sockfd, "200 OK", "text/html", "<html><body><h1>About Page</h1></body></html>");
    } else {
        send_response(sockfd, "404 Not Found", "text/html", "<html><body><h1>404 Not Found</h1></body></html>");
    }
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno, clilen;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    if (argc < 2) {
        fprintf(stderr, "Port number not provided\n");
        exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening socket");
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Error on binding");
    }
    
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    
    while (1) {
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        error("Error on accept");
    }
    
    bzero(buffer, 1024);
    read(newsockfd, buffer, 1023);
    
    struct http_request req;
    parse_request(buffer, &req);
    
    if (strcmp(req.method, "GET") == 0) {
        handle_route(newsockfd, &req);
    } 
	else {
        send_response(newsockfd, "405 Method Not Allowed", "text/html", "<html><body><h1>405 Method Not Allowed</h1></body></html>");
    }
    
    close(newsockfd);
}
    
    close(sockfd);
    return 0;
}
