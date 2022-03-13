#ifndef FOURRIER_H
#define FOURRIER_H

#include <complex.h>
#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <sox.h>


typedef struct{
     size_t size;
     size_t encoding;
     size_t nb_channels;
     size_t sample_size;
     size_t duration; //in seconds
 } songinfo;


double* get_data(char* file, songinfo* sample_size);

fftw_complex* fourrier_transform(double* in, int n);
#endif
