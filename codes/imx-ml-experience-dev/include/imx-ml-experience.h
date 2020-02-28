/* Copyright (c) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef IMX_ML_EXPERIENCE_H_
#define IMX_ML_EXPERIENCE_H_

#include <glib.h>
#include <glib/gprintf.h>
#include <gtk-3.0/gtk/gtk.h>

/* About Settings */
#define AUTHOR_DORTA        "Diego Dorta <diego.dorta@nxp.com>"
#define AUTHOR_MAEGIMA      "Vanessa Maegima <vanessa.maegima@nxp.com>"
#define NXP_ABOUT_LOGO_PATH "../media/splash/nxp_logo_small.png"
#define NXP_PROGRAM_NAME    "Machine Learning Experience Environment"
#define NXP_COPYRIGHTS      "Copyright \xc2\xa9 2019 NXP Semiconductors"
#define NXP_WEBSITE_LABEL   "NXP Semiconductors"
#define NXP_WEBSITE         "https://www.nxp.com/"

/* Debug Settings */
#ifdef IMX_ML_DEBUG    
#define DEBUGGING   1
#else
#define DEBUGGING   0
#endif

/* Glade User Interface */
#define UI_FILE "../gtk3-ui/imx-ml-experience.glade"

/* CSS Color GTK Settings */
#define GTK_CSS_PROVIDER_COLOR_PATH "../gtk3-ui/imx-ml-experience.css"

/* Splash Screen Settings*/
#define SPLASHSCREEN_TIMEOUT    1000
#define SPLASHSCREEN_WIDTH      1000
#define SPLASHSCREEN_HEIGTH     600

typedef struct {
    GArray *appArrayList;
    unsigned int appArrayListSize;
    GtkWidget *w_Window;
    GtkWidget *w_OpenCLButton;
    GtkWidget *w_FramesPerSecondLabel;
    GtkWidget *w_UpdateButton;
    GtkWidget *w_AboutButton;
    GtkWidget *w_PlayButton;
    GtkWidget *w_FileBaseImageButton;
    GtkImage *w_DrawingImage;
    GtkComboBoxText *w_ComboBoxApplications;
    GtkComboBoxText *w_ComboBoxInferenceEngine;
    GtkComboBoxText *w_ComboBoxFramework;
    GtkSpinner *w_RunSpinner;
} appWidgets;


/* Prototypes Headers */

extern void on_about_button_clicked(GtkButton *button, appWidgets *appWidget);
extern void about_license(void);

extern void on_opencl_button_clicked(GtkButton *button, appWidgets *appWidget);
extern void on_main_window_destroy(void);
#ifdef DEBUGGING
extern void g_print_builder_objects(GtkBuilder *builder);
#endif
extern void populate_combo_box_text(appWidgets *appWidget);
extern void get_items_from_combo_box_text(appWidgets *appWidget);
extern void get_lines_file(gchar *file, unsigned int *lines);

/* imx-ml-helper.c */
extern void setCssProvider(appWidgets *appWidgets, GtkCssProvider *p);
extern void init_splashscreen(int time, int width, int height, int argc, char *argv[]);

#endif /* IMX_ML_EXPERIENCE_H_ */
