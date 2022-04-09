#ifndef RESEARCH_H_
#define RESEARCH_H_

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

#include "../bytes/read.h"

unsigned int countSetBits(unsigned int n);
int research(long* file, long* p, size_t duration, size_t len);
char* open_all_files(long* p, size_t duration);


#endif
