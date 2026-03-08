#pragma once 
#include <netdb.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <exception>
#include <fcntl.h>
#include "client.hpp"
#define max_event 10

class Master
{
private:
    std::map<int,Client*> m; 
public:
    Master();
    void run();
    ~Master();
};

void Master::run()
{
    struct sockaddr_in hint;
    socklen_t len;
    
    int socket_fd = socket(AF_INET,SOCK_STREAM,0);
    if (socket_fd == -1)
    {
        throw  std::runtime_error("Socket failed .");
    }

    int op = 1;

    if (setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&op,sizeof(op)) < 0)
    {
        throw std::runtime_error("setsocketop failed .");
    }


    if (bind(socket_fd,(struct sockaddr*)&hint,len) != 0)
    {
        throw  std::runtime_error("bind failed .");
    }
     fcntl(socket_fd,O_NONBLOCK);
    if (listen(socket_fd,10) != 0)
    {
        throw  std::runtime_error("bind failed .");
    }
    //create epoll instance...
    int epoll_fd = epoll_create(0);
    struct epoll_event event;

    //add it socketfd in list watch .....
    if (epoll_ctl(epoll_fd,EPOLL_CTL_ADD,socket_fd,&event) != 0)
    {
        perror("epoll_ctl failed .");
        return ;
    }
    struct  epoll_event  arr_event[max_event];
    
    // start loop and waiting for events
    while (1)
    {
        struct sockaddr_in client_add;
        socklen_t len_add = sizeof(client_add);
        
        int active_ev = epoll_wait(epoll_fd,arr_event,max_event,-1);
        if(active_ev == -1)
            break; // what should do here ??
        for(int i = 0; i < active_ev;i++)
        {
            if (arr_event[i].data.fd == socket_fd)
            {
                
                int newfd = accept(socket_fd,(struct sockaddr*)&client_add, &len_add);
                if (epoll_ctl(epoll_fd,EPOLL_CTL_ADD,socket_fd,&event) != 0)
                {
                    perror("epoll_ctl failed .");
                    return ;
                }
                fcntl(newfd,O_NONBLOCK);
            }
            else if (event.events && EPOLLIN ) //??
            {
                //readrequest(); .........
            }
            else if (event.events && EPOLLOUT){
                //sendresponse;..........
            }
            else
            //break
            break;
        }
    }
    
}

Master::Master()
{
}

Master::~Master()
{
}
