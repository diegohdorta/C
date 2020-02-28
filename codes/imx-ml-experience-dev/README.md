# imx-ml-experience

//gcc -rdynamic -o window src/imx-ml-experience.cpp `pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags --libs gmodule-2.0`
//gcc src/imx-ml-experience.c `pkg-config --cflags --libs gtk+-3.0` -rdynamic -Wl,--export-dynamic
//https://github.com/GNOME/gtk/blob/master/demos/gtk-demo/font_features.c




/*
void on_OpenCLButton_clicked(GtkButton *button, gpointer data)
{
    gtk_label_set_text(GTK_LABEL(data), "AAA");


}*/

// called when window is closed


/*
lixos, but uteis

const gchar *WidgetName = gtk_widget_get_name((GtkWidget*) lp->data);
printf("WidgetName=%s\n", WidgetName);
//gtk_builder_add_callback_symbol (builder, "FramesPerSecondLabel", G_CALLBACK (on_opencl_button_clicked));

*/


    //gtk_builder_add_callback_symbol (builder, "FramesPerSecondLabel", G_CALLBACK (on_opencl_button_clicked));
    
    
    
    static unsigned int randomic(void)
{
    /* This is the principle of generating pseudorandom numbers. The
       method is called linear congruential generator. */
    static unsigned int t = 314;
    return t = (1103515245 * t + 12345) & 0x7fffffff;
}

extern void on_opencl_button_clicked(GtkButton *button, appWidgets *appWidget)
{
    for (int i = 0; i < 100; i++) {
        if(gtk_events_pending())
            gtk_main_iteration();
        gchar r[100];
        sprintf(r, "%d", randomic());
        
        //printf("%u\n", randomic());
        gtk_label_set_text(GTK_LABEL(appWidget->w_FramesPerSecondLabel), "Frames Per Second: 10");

        usleep(100000);
    }
}



/* Close the splash screen */
gboolean close_screen(gpointer data)
{
  gtk_widget_destroy((GtkWidget*)data);
  gtk_main_quit ();
  return(FALSE);
}


int Show_Splash_Screen(int time,int width,int height)
{
printf("bbbbb\n");
  GtkWidget  *image, *window;
  printf("cccc\n");
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
  printf("ddd\n");
  gtk_widget_set_size_request (window, width, height);
  gtk_window_set_decorated(GTK_WINDOW (window), FALSE);
  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  image=gtk_image_new_from_file("../media/splash/nxp_logo.png");
  gtk_container_add(GTK_CONTAINER(window), image);
  gtk_widget_show_all (window);
  g_timeout_add (time, close_screen, window);
  gtk_main ();
  printf("gggggggg\n");
  
  return 0;
}
