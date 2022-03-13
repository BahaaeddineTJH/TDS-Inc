#include "fourrier.h"
#include <stdio.h>
#include <err.h>

int main(int argc, char** argv){

    if(argc != 2)
        errx(1,"./test path");

    sox_format_init();
    
    double sample_size;
    int n;
    double* in = get_data(argv[1],&n,&sample_size);
    int nb_samples = n/2;
    double t = ((double)nb_samples) / sample_size;
    printf("duration : %i:%f\n",(int)t/60,(t/60 -(int)t/60 )*60);
    printf("get_data done\n");
    printf("nb_samples = %i\n",nb_samples);
    printf("n mod 44100 = %i\n",n%((int) sample_size));
    fftw_complex* out = fourrier_transform(in, n);
    /*
       for(int i=0; i<n; ++i){

       double* p = &out[i];

       printf("%f + %fi\n",p[0],p[1]);
       }*/

    free(out);
    sox_format_quit();
    return 0;
}

