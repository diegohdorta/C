/* Copyright (c) 2019 Diego Dorta <diego.dorta@nxp.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <gtk/gtk.h>
#include <stdlib.h>
#include "../include/gtk-main-experience.hpp"

static void setCssProvider(GtkWidget *w, GtkCssProvider *p)
{
    gtk_style_context_add_provider(gtk_widget_get_style_context(w),
                                   GTK_STYLE_PROVIDER(p),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    if (GTK_IS_CONTAINER(w))
        gtk_container_forall(GTK_CONTAINER(w), (GtkCallback)setCssProvider, p);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    GtkCssProvider *css = gtk_css_provider_new();
    GtkWidget *grid;
    GtkWidget *mlAppButton;
    GtkWidget *gpuAppButton;

    GtkWidget *mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(mainWindow), MW_TITLE);
    
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), MW_WIDTH, MW_HEIGHT);
    gtk_window_set_resizable (GTK_WINDOW(mainWindow), TRUE);
    
    gtk_window_set_position(GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER_ALWAYS);
    gtk_container_set_border_width (GTK_CONTAINER (mainWindow), 10);
    g_signal_connect(mainWindow, "destroy", G_CALLBACK(destroy), NULL);
   
    /* ############################################################## */

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID (grid), 3);
    gtk_container_add(GTK_CONTAINER (mainWindow), grid);
    mlAppButton = gtk_button_new_with_label("Machine Learning");
    gpuAppButton = gtk_button_new_with_label("GPU");
    
    if (gtk_css_provider_load_from_path(css, GTK_CSS_PROVIDER_COLOR_PATH, NULL)) {
        setCssProvider(mainWindow, css);
        gtk_widget_set_name(GTK_WIDGET(mlAppButton), "white-widget");
        gtk_widget_set_name(GTK_WIDGET(gpuAppButton), "white-widget");     


        gtk_grid_attach(GTK_GRID(grid), mlAppButton, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), gpuAppButton, 0, 1, 1, 1);
        gtk_widget_show_all(mainWindow);
        gtk_main();
    }
    return EXIT_SUCCESS;
}
