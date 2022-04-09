#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>


long* my_read(char* name, int* len)
{
    int fd = open(name, O_RDONLY);
    if(fd == -1)
    {
        errx(3, "Couldn't open %s", name);
    }

    char buffer[8];

    long* fingerprint = NULL;
    size_t nb = 0;

    ssize_t res;

    while((res = read(fd, buffer, sizeof(long))) != 0)
    {
        if(res == -1)
        {
            errx(3, "Couldn't read");
        }
        nb += 1;
        fingerprint = realloc(fingerprint, sizeof(long) * nb);
        if(fingerprint == NULL)
        {
            errx(3, "Couldn't realloc");
        }
        *(fingerprint + nb - 1) = *((long*) &buffer[0]);
        //printf(".%ld = %ld\n", nb, *(fingerprint + nb - 1));
        *len += 1;
    }
    close(fd);

    return fingerprint;
};