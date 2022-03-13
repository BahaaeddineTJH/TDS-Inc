#include "fourrier.h"
#include "finger_print.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        errx(3, "There sould only be one argument (the name of the music)!!!");
    }

    printf("Beginning of test with : %s\n", argv[1]);
    sox_format_init();
 
    int n;
    double* in = get_data(argv[1],&n);
    //printf("n = %d\n", n);

    fftw_complex* tab = create_tab(in, n);

    long* p = hash_tab(tab, n);

    /*size_t song_time = n/ (44100 * 4);
    size_t i;
    for(i = 0; i < song_time; i++)
    {
       printf("%ld\n",(p + i)[0]);
    }
    printf("i = %ld\n", i);*/

    sox_format_quit();
    printf("End of test\n");

    return 0;
}


