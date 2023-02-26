#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DEFAULT_PORT 8080
#define LOCALHOST "127.0.0.1"
#define BUFF_SIZE 4096

int main(int argc, char const* argv[])
{
    int status, valread, client_fd;
    struct sockaddr_in server_addr;
    char* hello_msg = "Hello from client!";
    char* host = LOCALHOST;
    char* recv_buf[BUFF_SIZE];
    
    memset(recv_buf, 0, sizeof(recv_buf));
    
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DEFAULT_PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary
    if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
        perror("Invalid or unsupported address\n");
        exit(EXIT_FAILURE);
    }
    
    if ((status = connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) { 
        perror("Connection to server failed\n");
        exit(EXIT_FAILURE);
    }
    
    send(client_fd, hello_msg, strlen(hello_msg), 0);
    printf("Hello message sent\n");
    if ((valread = read(client_fd, recv_buf, BUFF_SIZE)) < 0) {
        perror("Could not read response from server");
        exit(EXIT_FAILURE);
    }
    printf("Message received from server: %s\n", recv_buf);

    // Close socket
    close(client_fd);
    
    return 0;
}