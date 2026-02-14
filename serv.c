#include <netdb.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    struct  addrinfo hints,*res;
    char buf[100];
    hints.ai_family= AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if(getaddrinfo("localhost","8080", &hints,&res) != 0)
    {
        printf("hello");
        return 1;
    }
    struct addrinfo *rp;
    int sfd;
    for(rp = res; rp != NULL;rp = rp->ai_next) 
    {

        sfd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
        if (sfd == -1)
            continue;
        // listen(sfd,10)
        if (bind(sfd,(struct sockaddr*)rp->ai_addr,rp->ai_addrlen) == 0)
        {
            printf("fd : %d",sfd);
            break;
        }
        close(sfd);
    }
    if (rp == NULL)
    {
      printf("yes it is null\n");
      return 1;  
    }
    while (1)
    {
        int n = read(sfd,buf,10);
        if (n == 0)
            continue;
        if(n == -1)
        {
            continue;
        }
        else 
            printf("buf : %s",buf);
    }
    

    return 0;
    
}