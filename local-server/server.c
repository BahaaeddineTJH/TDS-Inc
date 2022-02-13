#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <err.h>
#include <arpa/inet.h>
#include <signal.h>

int main(int argc, char** argv)
{
    if (argc != 3)
        errx(EXIT_FAILURE, "Usage:\n"
                           "Arg 1 = Port number (e.g. 2048)"
                           "Arg 2 = ip address (e.g. 127.0.0.1)");
    char* port = argv[1];
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int server_socket = socket(hints.ai_family, hints.ai_socktype, 0);
    if (server_socket == -1){
        errx(1,"socket error");
    }
    int rvalue = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &rvalue, sizeof(int)) == -1){
        errx(1,"Couldn't set socket's option");
    }

    struct sockaddr_in server_addr, client_addr;
    char* ip = argv[2];
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = hints.ai_family;
    server_addr.sin_port = atoi(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    if (bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(server_socket, 5) == -1)
        errx(1,"listen error");

    printf("Waiting for connections...\n");
    while (1) {
        socklen_t socklen = sizeof(client_addr);
        int client = accept(server_socket, (struct sockaddr *)&client_addr, &socklen);
        if (client == -1)
            errx(1, "Couldn't connect to peer");
        if (!fork()){
            close(server_socket);
            printf("New connection (pid = %i)\n",getpid());
            /*
             * action for client
             */
            close(client);
            printf("Close connection (pid = %i)\n",getpid());
            exit(0);
        }
        close(client);
        signal(SIGCHLD,SIG_IGN);
    }
}