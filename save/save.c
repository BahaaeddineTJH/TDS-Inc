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
#include "../Research/research.h"


void s_write(char* c, char* d)
{
    songinfo s_info;
    double* in = get_data(d, &s_info);
                        
    fftw_complex* tab = create_tab(in, &s_info);
                        
    free(in);
    long* p = hash_tab(tab, &s_info);
                        
    my_write(c, s_info.duration, p);
                        
    free(tab);
    free(p);
}

    
int main(int argc, char* argv[])
{
    sox_format_init();

    if(argc == 1)
    {
        struct dirent *de;
        DIR *dr = opendir("music/");
    
        if (dr == NULL)
        {
            errx(EXIT_FAILURE, "Could not open current directory");
        }

        while ((de = readdir(dr)) != NULL)
        {
            if(strcmp(de->d_name, ".") && strcmp(de->d_name, ".."))
            {
                size_t s = strlen(de->d_name);

                char *d = malloc(sizeof(char)*(s + 6));
                strcpy(d, "music/");
                strcat(d,de->d_name);
                //printf("%s\n",d);

                de->d_name[strlen(de->d_name) - 4] = '\0';
                char *c = malloc(sizeof(char)*(s - 1));
                strcpy(c, "bin/");
                strcat(c,de->d_name);
                //printf("%s\n",c);

                s_write(c, d);                 
            }
        }
    }
    else
    {
        argc -= 1;
        while(argc > 0)
        {      
            size_t s = strlen(argv[argc]);

            char *d = malloc(sizeof(char)*(s + 4));
            strcpy(d,argv[argc]);
            strcat(d,".mp3");
            //printf("%s\n",d);

            char *c = malloc(sizeof(char)*(s));
            strcpy(c, "bin/");
            strcat(c,argv[argc] + 6);
            //printf("%s\n",c);
            
            s_write(c, d); 

            argc -= 1;
        }
    }

    sox_format_quit();
}
    
    