#include <complex.h>
#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <sox.h>

double* get_data(char* file,int* n);

fftw_complex* fourrier_transform(double* in, int n);
