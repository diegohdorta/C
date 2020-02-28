/* Copyright (c) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier: MIT
 */
#include "../include/imx-ml-experience.h"
#include <gtk-3.0/gtk/gtk.h>
#include <gtk/gtk.h>
#include<gdk-pixbuf/gdk-pixbuf.h>
#include <stdio.h>
#include <stdlib.h>

static void on_close(GtkDialog *dialog, gint response_id, gpointer user_data)
{
    gtk_widget_destroy(GTK_WIDGET(dialog));
}

extern void about_license(void)
{
    GtkWidget *about_dialog;
    about_dialog = gtk_about_dialog_new();

    const gchar *authors[] = {AUTHOR_DORTA, NULL};
    const gchar *documenters[] = {AUTHOR_MAEGIMA, NULL};

    GError *error;
    GdkPixbuf *pixbuf = NULL;
    
    pixbuf = gdk_pixbuf_new_from_file(NXP_ABOUT_LOGO_PATH, NULL);
    /*if (!pixbuf) {
        g_error("gdk_pixbuf_new_from_file(): %s\n", error->message);
        g_error_free(error);
    }*/
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_dialog), pixbuf);
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), NXP_PROGRAM_NAME);
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog), NXP_COPYRIGHTS);
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), authors);
    gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(about_dialog), documenters);
    gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG (about_dialog), GTK_LICENSE_MIT_X11);
    gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog), NXP_WEBSITE_LABEL);
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog), NXP_WEBSITE);
    gtk_window_set_title (GTK_WINDOW (about_dialog), "");
    g_signal_connect(GTK_DIALOG(about_dialog), "response", G_CALLBACK(on_close), NULL);
    gtk_widget_show (about_dialog);
}


extern void setCssProvider(appWidgets *appWidgets, GtkCssProvider *p)
{
    gtk_style_context_add_provider(gtk_widget_get_style_context(appWidgets->w_Window),
        GTK_STYLE_PROVIDER(p), GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    if (GTK_IS_CONTAINER(appWidgets->w_Window)) {
        gtk_container_foreach(GTK_CONTAINER(appWidgets->w_Window),
                                           (GtkCallback)setCssProvider, p);
    }
}

static gboolean close_splashscreen(gpointer data)
{
  gtk_widget_destroy((GtkWidget*)data);
  gtk_main_quit ();
}

extern void init_splashscreen(int time, int width, int height, int argc, char *argv[])
{
    GtkWidget *window, *image; 
    gtk_init(&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER_ALWAYS);
    gtk_window_set_type_hint(GTK_WINDOW(window),GDK_WINDOW_TYPE_HINT_SPLASHSCREEN); 

    gtk_widget_set_size_request (window, width, height);
    gtk_window_set_decorated(GTK_WINDOW (window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER_ALWAYS);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    
    image = gtk_image_new_from_file("../media/splash/nxp_logo.png");
    gtk_container_add(GTK_CONTAINER(window), image);
    
    gtk_widget_show_all (window);
    g_timeout_add (time, close_splashscreen, window);
    gtk_main ();
}
