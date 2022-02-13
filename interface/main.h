#ifndef MAIN_H_
#define MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>


GtkBuilder* get_builder();
int main(int argc, char *argv[]);
void callback_about();
void load_file();
void solver();
void run_shazam();
void write_output(char* filename);
void save_output();

typedef struct complex
{
    char* name;
}complex;


#endif
