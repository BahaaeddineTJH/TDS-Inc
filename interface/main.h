#ifndef MAIN_H_
#define MAIN_H_

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

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gmodule.h>
#include <glib.h>
#include <glib/gprintf.h>

#include "../fourrier/fourrier.h"
#include "../finger-print/finger_print.h"
#include "../bytes/read.h"
#include "../bytes/write.h"


GtkBuilder* get_builder();
int main(int argc, char *argv[]);
void callback_about();
void load_file();
void solver();
void run_shazam();
void write_output(char* filename);
void save_output();

typedef struct song_name
{
    char* name;
}song_name;


#endif
