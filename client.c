
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
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags =AI_PASSIVE; 

    if(getaddrinfo("google.com",NULL,&hints,&res) != 0)
    {
    
        printf("info succed");
    }
    struct addrinfo* pr;
    for(pr = res;pr != NULL;pr = pr->ai_next)
    {
        struct sockaddr_in* p =(struct sockaddr_in* ) pr->ai_addr;
        char buf[INET_ADDRSTRLEN];
    
        inet_ntop(AF_INET,&p->sin_addr,buf,sizeof buf);
        printf("googele ---> : %s",buf);

    }
    freeaddrinfo(res);
    // struct addrinfo *rp;
    // int sfd;
    // for(rp = res;rp != NULL; rp = rp->ai_next)
    // {
    //     sfd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
    //     if (sfd == -1)
    //         continue;
    //     if (connect(sfd,rp->ai_addr,rp->ai_addrlen))
    //     {
    //         break;
    //     }
    //     close(sfd);
    // }
    // write(sfd,"hello world!",12);
    return 0;

}