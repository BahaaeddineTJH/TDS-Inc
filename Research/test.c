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

#include "../fourrier/fourrier.h"
#include "../finger-print/finger_print.h"
#include "../bytes/read.h"
#include "../bytes/write.h"
#include "research.h"


int main(int argc, char *argv[])
{
     if (argc != 2)
        errx(EXIT_FAILURE, "Usage:\n"
                "Arg 1 = song name");

    sox_format_init();

    songinfo s_info;
    double* in = get_data(argv[1], &s_info);

    fftw_complex* tab = create_tab(in, &s_info);

    free(in);
    long* p = hash_tab(tab, &s_info);


    char* result = open_all_files(p, "bin", s_info.duration);

    free(tab);
    free(p);
    sox_format_quit();

    if(result != NULL)
    {
        printf("The result is : %s\n", result);
    }
    else
    {
        printf("The extract does not correspond to any known music.\n");
    }

    return 0;
}
