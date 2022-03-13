#include <complex.h>
#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <sox.h>

double* get_data(char* file,int* n);

void fourrier_transform(double* in, fftw_complex* out, int n);
