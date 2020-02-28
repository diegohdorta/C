/* Copyright (c) 2019 NXP Semiconductors
 *
 * SPDX-License-Identifier: MIT
 * Diego Dorta <diego.dorta@nxp.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "../include/imx-ml-experience.h"
#include <gtk-3.0/gtk/gtk.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    init_splashscreen(SPLASHSCREEN_TIMEOUT, SPLASHSCREEN_WIDTH, SPLASHSCREEN_HEIGTH, argc, argv);
    const gchar *user_interface_file = UI_FILE;
    GtkBuilder *builder;    
    GError *error = NULL;
    
    appWidgets *widgets = g_slice_new(appWidgets);
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, user_interface_file, NULL);
    if (error != NULL) {
        g_error("gtk_builder_add_from_file(): %s\n", error->message);
        g_error_free(error);
        return EXIT_FAILURE;
    }
    if (!DEBUGGING) {
        g_print_builder_objects(builder);
    }
    
    widgets->w_Window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    if (widgets->w_Window == NULL || !GTK_IS_WINDOW(widgets->w_Window)) {
        g_error("gtk_builder_get_object(): %s\n", error->message);
        return EXIT_FAILURE;
    }
    /* Fix below here */
    g_signal_connect(G_OBJECT(widgets->w_Window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, widgets);
    
    widgets->w_FramesPerSecondLabel = GTK_WIDGET(gtk_builder_get_object(builder, "FramesPerSecondLabel"));
    widgets->w_ComboBoxApplications = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "ComboBoxApplications"));
    widgets->w_ComboBoxInferenceEngine = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "ComboBoxInferenceEngine"));
    widgets->w_ComboBoxFramework = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "ComboBoxFramework"));
    widgets->w_UpdateButton = GTK_WIDGET(gtk_builder_get_object(builder, "UpdateButton"));
    widgets->w_AboutButton = GTK_WIDGET(gtk_builder_get_object(builder, "AboutButton")); 
    widgets->w_FileBaseImageButton = GTK_WIDGET(gtk_builder_get_object(builder, "FileBaseImage")); 
    widgets->w_PlayButton = GTK_WIDGET(gtk_builder_get_object(builder, "PlayButton")); 
    widgets->w_RunSpinner = GTK_SPINNER(gtk_builder_get_object(builder, "RunSpinner"));
    widgets->w_DrawingImage = GTK_IMAGE(gtk_builder_get_object(builder, "DrawingImage"));


    /*GtkCssProvider *css = gtk_css_provider_new();
    if (gtk_css_provider_load_from_path(css, GTK_CSS_PROVIDER_COLOR_PATH, NULL)) {
        setCssProvider(widgets, css);
    }*/
 
    g_object_unref(builder);
    gtk_widget_show(widgets->w_Window);
    gtk_main();
    g_slice_free(appWidgets, widgets);
    return EXIT_SUCCESS;
}

extern void open_file_image_base(appWidgets *appWidget)
{
   printf("aaaaaaaaaaa\n");
    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(appWidget->w_Window), GTK_FILE_CHOOSER_ACTION_OPEN,
                                            GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
    char *filename;

    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        printf("aaaaaaaaaaa\n");
        //open_file (filename);
        
         GError *error;
    GdkPixbuf *pixbuf = NULL;
    
    pixbuf = gdk_pixbuf_new_from_file(filename, NULL);
    pixbuf = gdk_pixbuf_scale_simple(pixbuf, 640, 480, GDK_INTERP_BILINEAR );
    //gtk_image_set_pixel_size(pixbuf, 307200);
    
        gtk_image_set_from_pixbuf (appWidget->w_DrawingImage, pixbuf);
        
        g_free (filename);
    }

    gtk_widget_destroy (dialog);
}

extern void on_file_base_image_clicked(GtkButton *button, appWidgets *appWidget)
{
    open_file_image_base(appWidget);

}

extern void on_about_button_clicked(GtkButton *button, appWidgets *appWidget)
{
    about_license();
}

extern void on_play_button_clicked(GtkButton *button, appWidgets *appWidgets)
{
    get_items_from_combo_box_text(appWidgets);
    gtk_spinner_start (GTK_SPINNER(appWidgets->w_RunSpinner));

}

extern void get_items_from_combo_box_text(appWidgets *appWidget)
{
    gchar *item = gtk_combo_box_text_get_active_text(appWidget->w_ComboBoxApplications);
    printf("%s\n", item);
    g_free(item);
}


extern void on_update_button_clicked(GtkButton *button, appWidgets *appWidget)
{
    populate_combo_box_text(appWidget);
}
// #############################################################################################
extern void get_lines_file(gchar *file, unsigned int *lines)
{
    FILE *fp;
    gchar *line;
    size_t lenght = 0;
    ssize_t read;

    fp = fopen(file, "r");
    if (fp != NULL) {
      while ((read = getline(&line, &lenght, fp)) != -1)
         (*lines)++;
      fclose(fp);
    }
}

#define FILE_CONTENT_LINE_SIZE  100

extern void populate_combo_box_text(appWidgets *appWidget)
{
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;  
    GtkWidget *dialog;
    gint errno = 0;    
    gchar file_app_content[FILE_CONTENT_LINE_SIZE];
    gchar file_ing_content[FILE_CONTENT_LINE_SIZE];
    gchar file_fmw_content[FILE_CONTENT_LINE_SIZE];
    gchar *files[3];
    gint appLines = 0;
    gint ingLines = 0;
    gint fmwLines = 0;
     
    files[0] = "../gtk3-ui/applications.dat";
    files[1] = "../gtk3-ui/inference-engines.dat";
    files[2] = "../gtk3-ui/frameworks.dat";

    get_lines_file(files[0], &appWidget->appArrayListSize);
    get_lines_file(files[1], &ingLines);
    get_lines_file(files[2], &fmwLines);


    FILE *file[2];
    for (int i = 0; i < G_N_ELEMENTS(files); i++) {
        file[i] = fopen(files[i], "r");
        if (file[i] == NULL) {
            dialog = gtk_message_dialog_new(GTK_WINDOW(appWidget->w_Window), flags, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Error reading ");
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG (dialog), "%s: %s", files[i], g_strerror(errno));
            gtk_window_set_title(GTK_WINDOW(dialog), "NXP ML Error");
            gtk_dialog_run(GTK_DIALOG (dialog));
            gtk_widget_destroy(GTK_WIDGET(dialog));
        }
    }    

    while (fscanf(file[0], "%s", file_app_content) == 1) {
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(appWidget->w_ComboBoxApplications), NULL, file_app_content);
        GString *s;
        appWidget->appArrayList = g_array_sized_new(FALSE, FALSE, sizeof(GString *), appWidget->appArrayListSize);
        s = g_string_new(file_app_content);

        g_array_append_val(appWidget->appArrayList, s);
        printf( "inserting %s\n", s->str );

    }
//#################################################################################

// print glib string vector
/*    GString *gs = NULL;
    for (gint i = 0; i < appWidget->appArrayListSize; i++) {         
         gs = g_array_index(appWidget->appArrayList, GString *, i );        
         if (gs == NULL)
            printf("NULLLLLL\n");            
         printf("glib array error\n");
         //g_printf("%s\n", gs->str );                        
          //  g_print ("ERROR: got d instead of d %s %d\n", g_array_index (appWidget->appArrayList, GString *, i), i);
   
    }*/
 
    while (fscanf(file[1], "%s", file_ing_content) == 1) {
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(appWidget->w_ComboBoxInferenceEngine), NULL, file_ing_content);
    }    
    while (fscanf(file[2], "%s", file_fmw_content) == 1) {
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(appWidget->w_ComboBoxFramework), NULL, file_fmw_content);
    }   
    gtk_combo_box_set_active(GTK_COMBO_BOX(appWidget->w_ComboBoxApplications), -1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(appWidget->w_ComboBoxInferenceEngine), -1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(appWidget->w_ComboBoxFramework), -1);        
    for (int i = 0; i < 3;i++)
        fclose(file[i]);
}


extern void on_opencl_button_clicked(GtkButton *button, appWidgets *appWidget)
{
    gtk_label_set_text(GTK_LABEL(appWidget->w_FramesPerSecondLabel), "Frames Per Second: 10");
}

extern void on_main_window_destroy(void)
{
    gtk_main_quit();
}

#ifdef DEBUGGING
extern void g_print_builder_objects(GtkBuilder *builder)
{
    GSList *lp, *lst;
    GType type;
    const gchar *name; 

    lst = gtk_builder_get_objects(builder);
    g_print("%p\n", lst);
    for (lp = lst; lp != NULL; lp = lp->next) {
        type = G_TYPE_FROM_INSTANCE(lp->data);
        name = g_type_name(type);
        printf("Object name: %s -> Type: %lu\n", name, type);
    }
}
#endif
