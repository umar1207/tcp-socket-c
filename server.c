#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/wait.h>

// server code

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("socket");
        exit(1);
    }

    printf("Socket created successfully\n");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    printf("Socket binded successfully\n");

    if(listen(sockfd, 10) == -1)
    {
        perror("listen");
        exit(1);
    }

    printf("Listening...\n");

    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_size);
    if(client_sockfd == -1)
    {
        perror("accept");
        exit(1);
    }

    printf("Connection accepted\n");

    char buffer[1024];
    int bytes_received = recv(client_sockfd, buffer, sizeof(buffer), 0);
    if(bytes_received == -1)
    {
        perror("recv");
        exit(1);
    }

    printf("Received: %s\n", buffer);

    close(client_sockfd);
    close(sockfd);
    return 0;
}

