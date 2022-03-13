#ifndef FINGER_PRINT
#define FINGER_PRINT

#include <complex.h>
#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <sox.h>
#include <err.h>
#include <errno.h>

#include "fourrier.h"

fftw_complex* create_tab(double* song, size_t song_size);
long hash(long p1, long p2, long p3, long p4);
int getIndex(int freq);
long* hash_tab(fftw_complex* song_tab, size_t song_size);

#endif