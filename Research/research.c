#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <complex.h>
#include <fftw3.h>
#include <sox.h>
#include <err.h>
#include <errno.h>
#include <dirent.h>
#include <math.h>

#include "../bytes/read.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

unsigned long countSetBits(unsigned long n)
{
    unsigned long count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

long research(long* file, long* p, size_t duration, size_t len)
{
    long nb = 0;
    size_t i = 0;
    while(i < len && i < duration)
    {
        //printf("%ld, %ld = ", *(p + i), *(file + i));
        unsigned int count = countSetBits(*(p + i)^*(file + i));
        //printf("%d\n", count);
        nb += count;
        i += 1;
    }
    return nb;
}

char* open_all_files(long* p, size_t duration)
{
    struct dirent *de;
    DIR *dr = opendir("bin/");
  
    if (dr == NULL)
    {
        errx(EXIT_FAILURE, "Could not open current directory");
    }

    char* b = "bin/";
    char* result;
    long threshold = 10;
    long percentage;
    while ((de = readdir(dr)) != NULL)
    {
        if(strcmp(de->d_name, ".") && strcmp(de->d_name, ".."))
        {
            char *c = malloc(strlen(de->d_name) + 5);
            strcpy(c,b);
            strcat(c,de->d_name);
            //printf("%s\n",c);

            size_t len = 0;
            long* file = my_read(c, &len);
            //if(len >= duration)
            {
                long cur = research(file, p, duration, len);
                percentage = (cur * 100)/(MIN(duration, len) * 8 * sizeof(long));
                //printf("%s\n",c);
                //printf("%ld\n", cur);
                //printf("%ld\n", percentage);    
                if(percentage <= threshold)
                {
                    result = malloc(strlen(de->d_name) + 5);
                    strcpy(result, c);
                    break;
                }
            }
            free(c);
        }
    }
    //printf("%s\n", result);
    closedir(dr);
    return result;
}