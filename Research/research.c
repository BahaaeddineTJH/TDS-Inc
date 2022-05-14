#define _GNU_SOURCE

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
#include "dictionary.h"
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

long research2(long* db_song,long* hash, size_t len_song, size_t len_hash){
    dictionary* dic = NULL;
    //printf("dic_create() done\n");
    long max = 0;
    printf("len_hash = %zu\n",len_hash);
    printf("len_song = %zu\n",len_song);
    for(size_t i=0; i<len_hash; ++i){
        printf("i = %zu\n",i);
        long h = hash[i];
        for(size_t j=0; j< len_song; ++j){
            printf("j = %zu\n",j);
            if(h == db_song[j]){
                for(size_t h=0; h<i; ++h){
                    int offset = abs((int) j - (int) i);
                    char* c_offset;
                    asprintf(&c_offset, "%d", offset);
                    if(!dic){
                        dic = dic_create();
                        long* count = malloc(sizeof(long));
                        *count = 1;
                        max = max==0 ? 1 : max;
                        dic_append(dic,c_offset,count);
                        //printf("dic_append() done\n");
                    }
                    else{
                        long* count = dic_get_data(dic,c_offset);
                        long* c = malloc(sizeof(long));
                        if(!count){
                            *c = 1;
                            max = max==0 ? 1 : max;
                            dic_append(dic,c_offset,c);
                            //printf("dic_append() done\n");
                        }
                        else{
                            *c = (*count) + 1;
                            max = max<*c ? *c : max;
                            dic_update(dic,c_offset,c);
                            //printf("dic_update() done\n");
                        }
                    }
                }
            }
        }
    }

    dic_destroy(dic);
    return max;
}

char* open_all_files(long* p, char* path,  size_t duration)
{
    struct dirent *de;
    char* path2 = calloc(strlen(path)+2,1);
    strcpy(path2,path);
    printf("path2 = %s\n",path2);
    path2[strlen(path)] = '/';
    DIR *dr = opendir(path2);
    printf("path2 = %s\n",path2);

    if (dr == NULL)
    {
        errx(EXIT_FAILURE, "Could not open current directory");
    }

    char* b = path2;
    char* result = NULL;
    long max;
    while ((de = readdir(dr)) != NULL)
    {
        if(strcmp(de->d_name, ".") && strcmp(de->d_name, ".."))
        {
            char *c = malloc(strlen(de->d_name) + strlen(path2) + 1);
            strcpy(c,b);
            strcat(c,de->d_name);
            //printf("%s\n",c);
            size_t len = 0;
            long* file = my_read(c, &len);
            {
                long nb_match = research2(file, p, len, duration);
                if(max < nb_match){
                    max = nb_match;
                    result = de->d_name;
                }
            }
            printf("%s score: %ld\n",de->d_name,max);
            free(c);
        }
    }
    //printf("%s\n", result);
    closedir(dr);
    return result;
}
