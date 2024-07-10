# Single-Threaded basic HTTP Server over TCP

## server.c

error() - called whena system call fails


sockfd - file descriptor, value returned by socket system call 
newsockfd - file descriptor, value returned by accept system call
portno - port number on which server accepts connections
clilen - needed for accept system call, stores size of address of client
n - number of characters read or written


buffer - server reads characters from socket connections to this buffer


socketaddr_in - structure containing an internet address

    struct sockaddr_in
    {

        short   sin_family; /* must be AF_INET */
  
        u_short sin_port;
  
        struct  in_addr sin_addr;
  
        char    sin_zero[8]; /* Not used, must be zero */
  
    };

serv_addr - address of server

cli_addr - address of client which connects to server



socket() - creates a new socket, it takes 3 arguements

--> address domain of the socket, AF_UNIX OR AF_INET and many others

--> Type of socket, SOCK_STREAM(TCP) or SOCK_DGRAM(UDP)

--> protocol - If this argument is zero, the OS will choose the most appropriate protocol,TCP for stream sockets and UDP for datagram sockets.

The socket system call returns an entry in file descriptor table, If the socket call fails, it returns -1.



bzero() - sets all value in a buffer to zero, it takes 2 arguements  

--> pointer to the buffer

--> size of the buffer

here, it initializes serv_addr to zero



short sin_family, which contains a code for the address family. It should always be set to the symbolic constant AF_INET.
unsigned short sin_port, which contain the port number. htons() converts a port number in host byte order to a port number in network byte order.
unsigned long s_addr. This field contains the IP address of the host, there is a symbolic constant INADDR_ANY which gets this address.



bind() - binds the socket to an address

in this case the address of the current host and port number on which the server will run.

it takes 3 arguements - 

--> the socket file descriptor

--> the address to which it is bound

--> size of address to which it is bound



The second argument is a pointer to a structure of type sockaddr.

but what is passed in is a structure of type sockaddr_in, and so this must be cast to the correct type. 

This can fail for a number of reasons, the most obvious being that this socket is already in use on this machine.



listen() - listen on the socket for connections, it takes 2 arguements

--> socket file descriptor

--> backlog queues



accept() - block until a client connects to a server, takes 2 arguements

--> the new file descriptor, the one returned by accept()

-->  the total number of characters it will read in the socket 





## client.c

    struct  hostent
    {
      char    *h_name;        /* official name of host */
      char    **h_aliases;    /* alias list */
      int     h_addrtype;     /* host address type */
      int     h_length;       /* length of address */
      char    **h_addr_list;  /* list of addresses from name server */
      #define h_addr  h_addr_list[0]  /* address, for backward compatiblity */
    };


## Usage

    gcc -o server server.c
    ./server 8080 

choose any other port if you want.
if you want to test using client executable

    gcc -o client client.c
    ./client 127.0.0.1 8080
    GET / HTTP/1.1

