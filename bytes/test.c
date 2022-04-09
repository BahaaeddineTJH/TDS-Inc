#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include "read.h"
#include "write.h"

int main()
{
    struct dirent *de;
    DIR *dr = opendir("bin/");
  
    if (dr == NULL)
    {
        errx(EXIT_FAILURE, "Could not open current directory" );
    }

    size_t size = 10;

    long* fingerprint = malloc(sizeof(long) * size);
    if(fingerprint == 0)
    {
        errx(3, "Failed to malloc hash_ta in fingerprint!");
    }

    for (size_t i = 0; i < size; i++)
    {
        *(fingerprint + i) = i;
    }

    //char * b = "bin/";
    while ((de = readdir(dr)) != NULL)
    {
        if(strcmp(de->d_name, ".") && strcmp(de->d_name, ".."))
        {
            /*char *c = malloc(strlen(de->d_name) + 5);
            strcpy(c,b);
            strcat(c,de->d_name);
            printf("%s\n",c);*/

            my_write(de->d_name, size, fingerprint);

            //my_read(c);

            //free(c);
        }
    }
            

    free(fingerprint);
    closedir(dr);

    return 0;
};