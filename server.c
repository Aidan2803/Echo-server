#include "net_funcs.h"
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

int main() {
    int serverfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(50000);

    Bind(serverfd, (struct sockaddr*)&addr, sizeof(addr));
    Listen(serverfd, 5);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int accepted_socketfd = Accept(serverfd, (struct sockaddr*)&client_addr, &client_addr_len);

    char buffer[256];
    ssize_t read_count = Read(accepted_socketfd, buffer, sizeof(buffer));
    write(STDOUT_FILENO, buffer, read_count);
    write(accepted_socketfd, buffer, read_count);

    sleep(1);

    close(accepted_socketfd);
    close(serverfd);

    return 0;
}
