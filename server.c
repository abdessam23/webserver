#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <unistd.h>     // For close
#include <stdio.h>      // For printf
#include <stdlib.h>     // For exit
#include <string.h>

int main() {
    // 1. Create the socket (Domain: IPv4, Type: TCP)
    int server_fd = socket(AF_INET,SOCK_STREAM, 0); 
    if (server_fd == -1) { perror("socket failed"); exit(1); }

    // 2. Define the address (IP and Port)
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on 0.0.0.0 (any interface)
    address.sin_port = htons(8080);       // Port 8080 (converted to network byte order)

    // 3. Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(1);
    }

    // 4. Start listening (Backlog of 10 connections)
    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        exit(1);
    }

    printf("Server listening on port 8080...\n");

    // 5. Accept a connection
    // We create generic storage for the client's address info
    struct sockaddr_storage client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // This block waits here until a client connects!
    int new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    
    if (new_socket < 0) {
        perror("accept failed");
        exit(1);
    }
    char buf[10];
    printf("Client connected! fd: %d\n", new_socket);
    while (1)
    {
       read(new_socket,buf,10);
       printf("the message recevied : %s \n",buf);
       
       if (buf[0] == 'q')
        break;
        memset(buf,0,10);
    }
    
    
    
    // Cleanup
    close(new_socket);
    close(server_fd);
    return 0;
}