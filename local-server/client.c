#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <err.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "../fourrier/fourrier.h"
#include "../finger-print/finger_print.h"

#define BUF_SIZE 256

void rewrite(int fd,void* buf,size_t len){
    size_t i = 0;
    while(i < len){
        ssize_t r = write(fd,buf+i,len-i);
        i += (size_t) r;
    }
}

char* read_data(int fd){
     char buf[BUF_SIZE];
     char* data = NULL;
     size_t len = 0;
     ssize_t r;
     while((r = read(fd,buf,BUF_SIZE)) != 0){
         if(r == -1)
             errx(1,"Could not read from client");
         data = realloc(data,len+r);
         memcpy(data+len,buf,r);
         len += (size_t) r;
     }
     return data;
 }

long* wrap_get_hash(char* path,size_t* len){
    sox_format_init();
    songinfo s_info;
    double* in = get_data(path,&s_info);
    fftw_complex* tab = create_tab(in, &s_info);
    free(in);
    long* p = hash_tab(tab, &s_info);
    free(tab);
    *len = s_info.duration;

    sox_format_quit();
    return p;
}

int main(int argc, char** argv) {
    if (argc != 4)
        errx(EXIT_FAILURE, "Usage:\n"
                "Arg 1 = ip address (e.g. 127.0.0.1)\n"
                "Arg 2 = Port number (e.g. 2048)\n"
                "Arg 3 = path to mp3\n");

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
    int cnx = -1;
    for(ai=results; ai!=NULL; ai=ai->ai_next){
        cnx  = socket(ai->ai_family,ai->ai_socktype,ai->ai_protocol);
        if(cnx == -1) continue;
        connect(cnx,ai->ai_addr,ai->ai_addrlen);
        if (cnx != -1) break;
        close(cnx);
    }
    freeaddrinfo(results);

    if(!ai)
        errx(1,"Connection failed.");
    printf("Connected to the server.\n");

    //send song hash to server
    size_t len;
    long* hash = wrap_get_hash(argv[4],&len);
    printf("Hash Done.\n");
    rewrite(cnx,hash,len*sizeof(long));
    rewrite(cnx,"\n",1);
    free(hash);
    printf("data sent\n");
    printf("Waiting for answer...\n");
    char* answer = read_data(cnx);
    printf("the answer is : %s\n",answer);
    free(answer);

    close(cnx);

    return 0;
}
