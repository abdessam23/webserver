#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
#include <sys/epoll.h>

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
     
     fcntl(sockfd, F_SETFL, O_NONBLOCK);
    if (listen(sockfd,10) != 0)
    {
        printf("listen failed.");
        return 1;
    }
    struct epoll_event* event;

    
   printf("waiting for connection....\n");
    int epoll_fd = epoll_create(5);
    epoll_ctl(epoll_fd,5,5,event);
     struct sockaddr_storage strg;
     socklen_t len_t = sizeof(strg);
   int newfd =  accept(sockfd,(struct sockaddr*)&strg,&len_t);
   if (newfd == -1)
   {
        printf("accept failed.");
        return 1;
   }
   char buf[10];
   while(1)
   {
       int s = read(newfd,buf,10);
       buf[s] = '\0';
       if (s == 0)
            break;
        
        printf("%s \n",buf);
        memset(buf,0,10);
   }
   close(sockfd);
   close(newfd);
}