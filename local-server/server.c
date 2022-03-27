#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <err.h>
#include <signal.h>

int main(int argc, char** argv)
{
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage:\n"
                "Arg 1 = Port number (e.g. 2048)");
    char* port = argv[1];

    struct addrinfo hints;
    struct addrinfo* results;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;

    int e = getaddrinfo(NULL,port,&hints,&results);
    if(e)
        errx(1,"Fail getting address on port %s: %s",
                port,gai_strerror(e));

    struct addrinfo* ai;
    int sck;
    for(ai=results; ai!=NULL; ai=ai->ai_next){
        sck = socket(ai->ai_family,ai->ai_socktype,ai->ai_protocol);
        if(sck == -1) continue;
        int rvalue = 1;
        if(setsockopt(sck,SOL_SOCKET,SO_REUSEADDR,&rvalue,sizeof(int)) == -1)
            errx(1,"Could not set sockopt");
        if(bind(sck,ai->ai_addr,ai->ai_addrlen) != -1) break;
        close(sck);
    }
    freeaddrinfo(results);
    if(ai == NULL)
        errx(1,"Could not bind");
    if(listen(sck,5) == -1)
        errx(1,"Could not listen");

    printf("Listening to port %s\n",port);
    printf("Waiting for connections...\n");
    while (1) {
        int client = accept(sck, NULL, NULL);
        if (client == -1)
            errx(1, "Couldn't connect to peer");
        if (!fork()){
            close(sck);
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
