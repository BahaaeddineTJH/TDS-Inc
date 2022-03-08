#include "fourrier.h"
#include <stdio.h>

int main(){
 
     sox_format_init();
 
     int n;
     double* in = get_data("Stromae-L’enfer.mp3",&n);
     printf("get_data done\n");
     printf("n = %i\n",n);
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

