#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <err.h>

int main(int argc, char** argv) {
    if (argc != 3)
        errx(EXIT_FAILURE, "Usage:\n"
                "Arg 1 = ip address (e.g. 127.0.0.1)\n"
                "Arg 2 = Port number (e.g. 2048)\n");

    struct addrinfo hints;
    struct addrinfo* results;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    int e = getaddrinfo(argv[1],argv[2],&hints,&results);
    if(e)
        errx(1,"Fail getting address on %s:%s : %s",
                argv[1],argv[2],gai_strerror(e));

    struct addrinfo* ai;
    int sck;
    int cnx;
    for(ai=results; ai!=NULL; ai=ai->ai_next){
        sck = socket(ai->ai_family,ai->ai_socktype,ai->ai_protocol);
        if(sck == -1) continue;
        cnx = connect(sck,ai->ai_addr,ai->ai_addrlen);
        if (cnx != -1) break;
        close(sck);
    }
    freeaddrinfo(results);

    if(cnx == -1)
        errx(1,"Connection failed.");
    printf("Connected to the server.\n");
    /*
     *  send request
     */
    return 0;
}
