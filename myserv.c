#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>

int main()
{
    struct sockaddr_in addr;
    struct sockaddr post;
    post.sa_family = AF_INET;
    socklen_t len;
    addr.sin_port =htons(8080);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd == -1)
        return 1;
    if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)) != 0)  
    {
        printf("bind failed.");
        return 1;
    }
     printf("waiting for connection....\n");
    if (listen(sockfd,10) != 0)
    {
        printf("listen failed.");
        return 1;
    }
   
     struct sockaddr_in strg;
     socklen_t len_t = sizeof(strg);
   int newfd =  accept(sockfd,(struct sockaddr*)&strg,&len_t);
   if (newfd == -1)
   {
        printf("accept failed.");
        return 1;
   }
   send(newfd,"hello man ",10,0);
   printf("your message was send it .");
   close(sockfd);
   close(newfd);
}