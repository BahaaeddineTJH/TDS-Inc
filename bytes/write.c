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
#include <err.h>


void my_write(char* name, size_t size, long* list)
{
    FILE *out;

    out = fopen(name, "wb");
    if(out == NULL)
    {
        errx(3, "Couldn't open %s", name);
    }

    size_t res_out = fwrite(list, sizeof(long) * size, 1, out);

    fclose(out);
    if(res_out == 0)
    {
        errx(3, "Couldn't clode %s", name);
    }
};