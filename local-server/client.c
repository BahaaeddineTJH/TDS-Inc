#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <err.h>

int main(int argc, char** argv) {
    if (argc != 3)
        errx(EXIT_FAILURE, "Usage:\n"
                           "Arg 1 = Port number (e.g. 2048)"
                           "Arg 2 = ip address (e.g. 127.0.0.1)");
    int port = atoi(argv[1]);
    char *ip =argv[2];

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);

    if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1){
        perror("connect");
        exit(EXIT_FAILURE);
    }
    printf("Connected to the server.\n");
    /*
     *  send request
     */
    return 0;
}