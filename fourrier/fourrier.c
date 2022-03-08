#include <complex.h>
#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <sox.h>

#define BUFFER_SIZE 512

double* get_data(char* file, int* n){
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

    *n = (int) len;

    sox_close(format);

    return data;
}


fftw_complex* fourrier_transform(double* in, int n){
    printf("start fourier\n");
    fftw_complex* out = fftw_alloc_complex(n*sizeof(fftw_complex));
    printf("alloc done\n");
    fftw_plan plan = fftw_plan_dft_r2c_1d(n,in, out,FFTW_ESTIMATE | FFTW_DESTROY_INPUT);
    printf("plan done\n");
    fftw_execute(plan);
    printf("execute done\n");
    fftw_destroy_plan(plan);
    fftw_cleanup();

    return out;
}

