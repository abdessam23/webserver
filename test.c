#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    struct addrinfo hints,*res;

    int status = getaddrinfo("gsup.com","80", &hints,&res);

    if (status != 0)
    {
        printf("get Failed : %s",gai_strerror(status));
        return 1;
    }
    char *s = inet_ntop()
    printf("The get successed !");
    freeaddrinfo(res);
    return 0;
}