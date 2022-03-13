#include <complex.h>
#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <sox.h>
#include <err.h>
#include <errno.h>

#include "fourrier.h"

#define BUFFER_SIZE 512

double* get_data(char* file, songinfo* s_info){
    sox_format_t* format = sox_open_read(file, NULL, NULL, NULL);

    sox_sample_t buf[BUFFER_SIZE];
    double* data = NULL;

    size_t len = 0;
    
    size_t r;

    while((r = sox_read(format, buf, BUFFER_SIZE)) != 0){
        len += r;
        data = realloc(data,sizeof(double)*len);
        for(size_t i=0; i<r; ++i){
            data[len-r+i] = (double) buf[i];
        }
    }

    s_info->sample_size = (size_t) format->signal.rate;
    s_info->size = (size_t) len;
    s_info->encoding = format->signal.precision;
    s_info->nb_channels = format->signal.channels;
    s_info->duration = (double)len/(s_info->nb_channels*s_info->sample_size);

    sox_close(format);

    return data;
}


fftw_complex* fourrier_transform(double* in, int n){
    fftw_complex* out = fftw_alloc_complex(n*sizeof(fftw_complex));
    if(!out){
        perror("malloc fourrier output");
        exit(errno);
    }
    fftw_plan plan = fftw_plan_dft_r2c_1d(n,in, out,FFTW_ESTIMATE | FFTW_DESTROY_INPUT);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    fftw_cleanup();

    return out;
}

