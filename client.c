
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define PORT "8080" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:

int main()
{
    struct  addrinfo hints,*res;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if(getaddrinfo("localhost",PORT,&hints,&res) == 0)
    {
    
        printf("info succed");
    }
    struct addrinfo *rp;
    int sfd;
    for(rp = res;rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
        if (sfd == -1)
            continue;
        if (connect(sfd,rp->ai_addr,rp->ai_addrlen))
        {
            break;
        }
        close(sfd);
    }
    
}