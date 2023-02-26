#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define DEFAULT_PORT 8080
#define BUFF_SIZE 4096

int main(int argc, char const* argv[])
{
    int server_fd, recv_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char recv_buffer[BUFF_SIZE];
    const char* hello_msg = "Hello from server";
  
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
  
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("failed to set socket options");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(DEFAULT_PORT);
  
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("socket bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Prepare for listening
    int max_conns = 5;
    if (listen(server_fd, max_conns) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Await for connection
    while ((recv_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) >= 0) {
        valread = read(recv_socket, recv_buffer, BUFF_SIZE);
        sprintf("Server received: %s\n", recv_buffer);
    }
    close(recv_socket);

    shutdown(server_fd, SHUT_RDWR);

    return 0;
}