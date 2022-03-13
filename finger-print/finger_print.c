#include <complex.h>
#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <sox.h>
#include <err.h>
#include <errno.h>
#include <math.h>
#include <complex.h>
#include <string.h>

#include "fourrier.h"

#define FUZ_FACTOR 2
#define SAMPLE_SIZE 44100

fftw_complex* create_tab(double* song, size_t song_size)
{
    printf("beginning of create_tab\n");

    size_t chunk_size = SAMPLE_SIZE * 4;

    fftw_complex* res = malloc(sizeof(fftw_complex) * song_size);
    if(res == 0)
    {
        errx(3, "Failed to malloc res in create_tab!");
    }


    for (size_t i = 0; i < song_size; i += chunk_size)
    {
        if(i + chunk_size > song_size)
        {
            chunk_size = song_size - i;
        }

        fftw_complex* cur = malloc(sizeof(fftw_complex) * chunk_size);
        if(cur == 0)
        {
            errx(3, "Failed to malloc cur in create_tab!");
        }

        fourrier_transform(song + i, cur, chunk_size);

        memcpy(res + i, cur, chunk_size);

        free(cur);
    }

    printf("end of create_tab\n");
    return res;    
}

long hash(long p1, long p2, long p3, long p4) 
{
    return (p4 - (p4 % FUZ_FACTOR)) * 100000000 + (p3 - (p3 % FUZ_FACTOR)) * 100000 + (p2 - (p2 % FUZ_FACTOR)) * 100 + (p1 - (p1 % FUZ_FACTOR));
}

int getIndex(int freq) 
{
    int RANGE[] = { 40, 80, 120, 180, 300 };
    int i = 0;
    while (RANGE[i] < freq)
    {
        i++;
    }
    return i;
}

long* hash_tab(fftw_complex* song_tab, size_t song_size)
{
    printf("beginning of hash_tab\n");

    size_t chunk_size = SAMPLE_SIZE * 4;
    size_t song_time = song_size / (chunk_size);

    double* points = calloc(song_size, sizeof(double));
    if(points == 0)
    {
        errx(3, "Failed to calloc hash_ta in hash_tab!");
    }

    long* hash_tab = malloc(sizeof(long) * song_time);
    if(hash_tab == 0)
    {
        errx(3, "Failed to malloc hash_ta in hash_tab!");
    }

    size_t t;
    for (t = 0; t < song_time; t++)
    {
        for (size_t freq = 40; freq < 300; freq++)
        {
            double mag = (double) clog(cabs(song_tab[t * chunk_size + freq]) + 1);

            int index = getIndex(freq);

            if (mag > points[t * chunk_size + index]) 
            {
                points[t * chunk_size + index] = freq;
            }

        }
        long h = hash(points[t * chunk_size + 0], points[t * chunk_size + 1], points[t * chunk_size + 2], points[t * chunk_size + 3]);
        //printf("%f, %f, %f, %f\n", points[t * chunk_size + 0], points[t * chunk_size + 1], points[t * chunk_size + 2], points[t * chunk_size + 3]);
        //printf("hash = %ld\n", h);
        *(hash_tab + t) = h;
    } 

    //printf("t = %ld\n", t);
    printf("end of hash_tab\n");
    return hash_tab;
}
