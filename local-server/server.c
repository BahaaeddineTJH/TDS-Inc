#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <err.h>
#include <signal.h>

#include "../Research/research.h"

#define BUF_SIZE 256

void rewrite(int fd,void* buf,size_t len){
    size_t i = 0;
    while(i < len){
        ssize_t r = write(fd,buf+i,len-i);
        if(r == -1)
            errx(1,"Could not write into fd");
        i += (size_t) r;
    }
}

long* read_data(int client,size_t* len){
    char buf[BUF_SIZE];
    char* data = NULL;
    ssize_t r;
    *len = 0;
    while((r = read(client,buf,BUF_SIZE)) != 0){
        if(r == -1)
            errx(1,"Could not read from client");
        data = realloc(data,*len+r);
        memcpy(data+*len,buf,r);
        *len += (size_t) r;
        if(data[*len-1] == '\n')
            break;
    }
    *len /= sizeof(long);
    return (long*)data;
}

void process_client(int client,char* path){
    size_t len;
    long* data = read_data(client,&len);
    char* result = open_all_files(data,path,len);
    if(!result){
        char err_msg[] = "not found";
        rewrite(client,err_msg,strlen(err_msg)+1);
    }
    else{
        rewrite(client,result,strlen(result)+1);
    }
}

int main(int argc, char** argv)
{
    if (argc != 3)
        errx(EXIT_FAILURE, "Usage:\n"
                "Arg 1 = Port number (e.g. 2048)"
                "Arg 2 = Path to bin");
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
            process_client(client,argv[2]);
            close(client);
            printf("Close connection (pid = %i)\n",getpid());
            exit(0);
        }
        close(client);
        signal(SIGCHLD,SIG_IGN);
    }
}
