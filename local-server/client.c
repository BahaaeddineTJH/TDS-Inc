#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <err.h>

#include "../finger-print/finger_print.h"

#define BUFFER_SIZE 256

void rewrite(int fd, void* buf, size_t len){
    size_t index = 0;
    while(index < len){
        ssize_t r = write(fd,buf+index,len-index);
        if(r == -1)
            errx(1,"Could not write into fd");
        len += r;
    }
}

long* wrap_get_hash(char* path,size_t* len){
    sox_format_init();
    printf("Hello\n");
    songinfo s_info;
    double* in = get_data(path,&s_info);
    printf("Hello\n");
    fftw_complex* tab = create_tab(in, &s_info);
    free(in);
    printf("Hello\n");
    long* p = hash_tab(tab, &s_info);
    free(tab);
    printf("Hello\n");
    *len = s_info.duration;

    sox_format_quit();
    return p;
}

int main(int argc, char** argv) {
    if (argc != 4)
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

    //send song hash to server
    size_t len;
    long* hash = wrap_get_hash(argv[4],&len);
    printf("Hash Done.\n");
    write(cnx,hash,len*sizeof(long));
    printf("Hash sent\n");
    free(hash);

    printf("Waiting for answer...\n");

    //get answer from server
    char* answer = NULL;
    char buffer[BUFFER_SIZE];
    size_t answer_len = 0;
    ssize_t r;
    while ((r = read(cnx,buffer,BUFFER_SIZE)) != 0){
        if(r == -1)
            errx(1,"Could not read from fd");
        answer = realloc(answer,answer_len+r);
        for (ssize_t i = 0; i < r; ++i) {
            answer[len+i] = buffer[i];
        }
        len += r;
    }
    answer = realloc(answer,answer_len+1);
    answer[answer_len] = '\0';
    printf("the answer is : %s\n",answer);


    free(answer);

    close(cnx);

    return 0;
}
