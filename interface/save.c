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

#include <gmodule.h>
#include <glib.h>
#include <glib/gprintf.h>

#include "../bytes/write.h"
    
    
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        errx(EXIT_FAILURE, "Needs at least 2 argument!");
    }

    /*gchar* cur = argv[1];
    gchar* file_name = g_strndup(cur + 6, g_strstr_len(cur + 6, -1, ".mp3") - (cur + 6));
    printf("%s\n", file_name);
    my_write(file_name, duration, p);
    g_free(file_name);

    char* b = "bin/";
    char *c = malloc(strlen(file_name) + 5);
    //printf("%d\n", g_strstr_len(cur, -1, ".mp3"));
    strcpy(c, b);
    strcat(c, file_name);
    //printf("%s\n", c);*/
}
    
    