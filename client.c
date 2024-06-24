#include "net_funcs.h"
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

int main() {
    int client_sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(50000);

    InetPton(AF_INET, "127.0.0.1", &addr.sin_addr);
    Connect(client_sockfd, (struct sockaddr*)&addr, sizeof(addr));

    char buffer[256] = "Hi, server!\n";
    write(client_sockfd, buffer, strlen(buffer));
    ssize_t read_count = Read(client_sockfd, buffer, sizeof(buffer));
    write(STDOUT_FILENO, buffer, read_count);

    sleep(5);

    close(client_sockfd);

    return 0;
}
