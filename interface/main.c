#include "main.h"

complex z;

GtkBuilder* get_builder() 
{
    static GtkBuilder *builder = NULL;
    if (!builder)
        builder = gtk_builder_new();
    return builder;
}

void callback_about() 
{
    GtkWidget *dialog = NULL;

    dialog =  GTK_WIDGET (gtk_builder_get_object (get_builder(), "about"));
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_hide (dialog);
}

void write_output(char* filename) 
{
    FILE *file;
    gchar *text;

    file = fopen(filename, "w+");
    GtkTextBuffer *b = GTK_TEXT_BUFFER(gtk_builder_get_object(get_builder(), "output_buffer"));
    GtkTextIter start, end;

    gtk_text_buffer_get_bounds(b, &start, &end);
    text = gtk_text_buffer_get_text(b, &start, &end, FALSE);

    fputs(text, file);

    g_free(text);
    fclose(file);
}

void save_output() 
{
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res;

	dialog = gtk_file_chooser_dialog_new("Save output...", NULL, action, "Cancel", GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);
	chooser = GTK_FILE_CHOOSER(dialog);

	gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
	gtk_window_set_icon_name(GTK_WINDOW(dialog), "document-save");

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT) 
    {
		char *filename;
		filename = gtk_file_chooser_get_filename(chooser);
		write_output(filename);
		g_free(filename);
	}

	gtk_widget_destroy(dialog);
}


void load_file() 
{
    GtkTextBuffer *b = GTK_TEXT_BUFFER(gtk_builder_get_object(get_builder(), "output_buffer"));
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    GtkWidget *dialog;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Load text...", NULL, action, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_window_set_icon_name(GTK_WINDOW(dialog), "document-open");
    
    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT) 
    {
        char* c = "------------------------------------\n";
        gtk_text_buffer_insert_at_cursor(b, c, strlen(c));

        //the file we chose
        char* began = "You have chosen to shazam : ";
        gtk_text_buffer_insert_at_cursor(b, began, strlen(began));

        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);

        char* filename = gtk_file_chooser_get_filename (chooser);
        size_t i = strlen(filename);

        z.name = calloc(strlen(filename)+1, sizeof(char));
        strcpy(z.name, filename);
        //printf("file_name = %s\n", z.name);

        gtk_text_buffer_insert_at_cursor(b, filename, i);
        gtk_text_buffer_insert_at_cursor(b, "\n", 1);

        g_free (filename);
    }

    gtk_widget_destroy (dialog);
}

//-------------Lance tout les fonctions---------------
void run_shazam() 
{
    GtkTextBuffer *b = GTK_TEXT_BUFFER(gtk_builder_get_object(get_builder(), "output_buffer"));

    //check if z.name is
    if(z.name == NULL)
        load_file();

    size_t i = strlen(z.name);
    if(i == 0)
    {
        load_file();
    }
    //printf("file_name = %s\n", z.name);
    //FILE *f = fopen(z.name, "r");

    //fourier

    //empreinte

    //take as parameter the empreinte
    //Research_match();
        
    char* c = "No correspounding were found.\n";
    gtk_text_buffer_insert_at_cursor(b, c, strlen(c));
    gtk_text_buffer_insert_at_cursor(b, "\n\n", 2);

    z.name = NULL;
}

//-------------Le main----------------
int main(int argc, char *argv[]) 
{
    GtkWidget *mainwindow = NULL;
    GError *error = NULL;
    gchar *filename = NULL;

    gtk_init(&argc, &argv);

    GtkBuilder *builder = get_builder();
    filename = g_build_filename("ui/window.glade", NULL);
    gtk_builder_add_from_file (builder, filename, &error);
    g_free(filename);

    if (error) 
    {
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free (error);
        return code;
    }

    gtk_builder_connect_signals(builder, NULL);

    mainwindow = GTK_WIDGET(gtk_builder_get_object (builder, "main_window"));
    gtk_widget_show_all (mainwindow);
    gtk_main();

    return 0;
}



