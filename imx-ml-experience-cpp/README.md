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

/*
               // Glib::RefPtr<Gdk::Pixbuf> refPixbuf = Gdk::Pixbuf::create_from_file("../media/gnomestock/48x48/status/gtk-dialog-warning.png");
                //dialog.set_image("../media/gnomestock/48x48/status/gtk-dialog-warning.png");
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <string>

#define CSV_FILE_NAME "labels.csv"
#define RE_CSV_FILE "(\\d)?[[:digit:]]+(\\:)(\\w+|\\s*,\\s*)+"

struct dict {
    int index;
    std::string label;
};
typedef struct dict dict_t;

class CSV_Helper {
    std::string label; //trocar nome
    std::string entireLine;
    std::ifstream ifs;
    unsigned int csvLines;
    const char *fileName;
    
    public:
        CSV_Helper(void);
        void getNumberLines(void);
        void checkFile(void);
    
    void runCSV()
    {
        getNumberLines();
        checkFile();    
    }
};

CSV_Helper::CSV_Helper(void)
{
    csvLines = 0;
    fileName = CSV_FILE_NAME;
}

void CSV_Helper::getNumberLines(void)
{
    std::cout << "CSV_Helper getNumberLines() function" << std::endl;
    ifs.open(fileName, std::ifstream::in);
    if (ifs.fail()) {
        throw std::runtime_error("check csv file name\n");    
    }
    while (getline(ifs, label)) {
        csvLines++;
    }
    std::cout << "Number of lines inside csv file: " << csvLines << std::endl;
    ifs.close();
}

void CSV_Helper::checkFile(void)
{
    std::cout << "CSV_Helper checkFile() function" << std::endl;
    std::regex raw(RE_CSV_FILE);
    std::smatch m;
    
    ifs.open(fileName, std::ifstream::in);
    if (ifs.fail()) {
        throw std::runtime_error("check csv file name\n");    
    }

    while (getline(ifs, entireLine)) {
        if (std::regex_match (entireLine, raw)) {
            std::cout << "bateu!" << std::endl;
            for (std::smatch m; std::regex_search(entireLine, m, raw); entireLine = m.suffix())
           
              std::cout << "groups: " << m.groups() << std::endl;
              std::cout << "m[0]: " << m[0] << "\nm[1]: " << m[1] << "\nm[2]: " << m[2] << std::endl;
            
        }
        
    }
    ifs.close();
}

int main(int argc, char *argv[])
{
    std::cout << "Hello World" << std::endl;
    CSV_Helper demo;
    
    demo.runCSV();    
    
    return EXIT_SUCCESS;
}


        if (std::regex_search (entireLine, m, raw)) {
            std::cout << "[msize = " << m.size() << "] Pattern found: ";
            for (int i = m.size(); i >= 0; i--) {
                std::cout << m[i];
            }
            std::cout << std::endl;
        }
        
        while (std::regex_search (entireLine, m, raw)) {
            for (auto x:m) std::cout << x << " ";
            std::cout << std::endl;
            entireLine = m.suffix().str();
        
        }



char *name= http://127.0.0.1:8000/mybinfile


int getFile(char *name)
{

    GFile *f = g_file_new_for_uri(name);
    GFileInputStream *fis = NULL;
    GDataInputStream* dis = NULL;
    GError *err = NULL;
    //char buffer[2048];
    char *buffer;
    size_t length;
    int ret = -1;

    GFileInfo *info;

    int total_size = -1;


    fis = g_file_read(f, NULL, &err);

    if (err != NULL) {
        fprintf(stderr, "ERROR: opening %s\n", name);
        g_object_unref(f);
        return -1;
    }

    info = g_file_input_stream_query_info (G_FILE_INPUT_STREAM (fis),G_FILE_ATTRIBUTE_STANDARD_SIZE,NULL, &err);
    if (info)
    {
        if (g_file_info_has_attribute (info, G_FILE_ATTRIBUTE_STANDARD_SIZE))
            total_size = g_file_info_get_size (info);
            printf( "total_size = %d\n", total_size);
            g_object_unref (info);
    }

    // fill buffer
    if(total_size > 0){
        buffer = (char *) malloc(sizeof(char) * total_size);
        memset(buffer, 0, total_size);
        if ((length = g_input_stream_read (G_INPUT_STREAM(fis),
                    buffer, total_size, NULL, &err)) != -1) {
                printf( "reading file\n");
        }
        printf( "File length = %d\n", length);

            ret = 0;
        }
        // close streams
        g_object_unref(fis);
        g_object_unref(f);   
        return ret;
    }


// https://solarianprogrammer.com/2011/10/20/cpp-11-regex-tutorial-part-2/

*/


// ####################################################################################################################
/*

revealer in splash screen
pango text mask
gtk tree view

1:ArmNN

1.1:Caffe
1.1.1:Demos 1
1.1.2:Demos 2
1.1.3:Demos 3

1.2:TensorFlow
1.2.1:Demos 1
1.2.2:Demos 2
1.2.3:Demos 3

1.3:TensorFlowLite:
1.3.1:Demos 1
1.3.2:Demos 2
1.3.3:Demos 3        Demos...
    ONNX:
        Demos...

2:OpenCV-DNN
2.1:Caffe
2.1.1:Demos 1
2.1.2:Demos 2
2.1.3:Demos 3
        Demos...
     TensorFlow:
        Demos...

*//*
void get_dirs(void)
{
    std::cout << "start" << std::endl;
    const gchar *dataTreeFile = "../data/data-tree.txt";
    
    if (g_file_test (dataTreeFile, G_FILE_TEST_EXISTS)) {
        gsize length;
        gchar *content;
        if (g_file_get_contents (dataTreeFile, &content, &length, NULL)) {
        
            g_print("%s\n", content);
                
            // Process contents
            g_free (content);
        }
    }
    
    std::cout << "end" << std::endl;
}


#include <gio/gio.h>

void readFile(void)
{
    g_autoptr(GFile) file = g_file_new_for_path("../data/data-tree.txt");
    g_autoptr(GFileInputStream) in = g_file_read(file, NULL, NULL);
    if(!in)
        std::cout << "error 0" << std::endl;

    gssize read;
    char temp[1000];

    while (TRUE)
    {
      read = g_input_stream_read(G_INPUT_STREAM(in), temp, G_N_ELEMENTS(temp) - 1, NULL, NULL);
      if (read > 0)
      {
          temp[read] = '\0';
          g_print("%s", temp);
      }
      else if (read < 0)
          std::cout << "error 1" << std::endl;
      else
         break;
    }

    std::cout << "ok" << std::endl;
}*/

/*    GtkWidget *window, *image; 
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

           // Glib::RefPtr<Gdk::Pixbuf> refPixbuf = Gdk::Pixbuf::create_from_file("../media/splash/nxp_logo_small.png");*/

         /*   FILE *fp;
            const gchar *dataTreeFile = "../data/data-tree";
            gchar *line;
            size_t lenght = 0;
            ssize_t read;

            fp = fopen(dataTreeFile, "r");
            if (fp != NULL) {
                while ((read = getline(&line, &lenght, fp)) != -1) {
                //line.ignore();
                    //line.substr(line.find("::%s"));
                    this->ComboBoxInferenceEnginesPtr->append(line);
                }
            }
            fclose(fp);*/
            
                  //  if (std::regex_match (entireLine, raw)) {
        //    std::cout << "bateu!" << std::endl;
          //  for (std::smatch m; std::regex_search(entireLine, m, raw); entireLine = m.suffix())           
       //       std::cout << "groups: " << m.groups() << std::endl;
       
       
       
                   /*
             *  PRIMEIRO USAR O BUTTON UPDATE PARA ATUALIZAR A LISTA DE INFERENCES ENGINES            
             */
         /*   const gchar *dataTreeFile = "../data/data-tree.txt";

            if (g_file_test (dataTreeFile, G_FILE_TEST_EXISTS)) {
                gsize length;
                gchar *content;
                if (g_file_get_contents (dataTreeFile, &content, &length, NULL)) {                   

                        this->ComboBoxInferenceEnginesPtr->append(content);
                        
                    g_free (content);
                }
            }*/
            
            
            
            
            
                SplashScreenWindow *SplashScreenWindowPtr = nullptr;
    Gtk::Main app(argc, argv, "org.gtkmm.with_signal");    
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("../gtk3-ui/imx-ml-experience.glade");
    builder->get_widget_derived("splash_screen_window", SplashScreenWindowPtr);


    Gtk::Main::run(*SplashScreenWindowPtr); 
    
    
    
    
    class SplashScreenWindow : public Gtk::Window {
    public:
        Gtk::Window *SplashScreenWindowPtr = nullptr;
        Glib::RefPtr<Gtk::Builder> builder;
        
        Gtk::Image *SplashScreenImagePtr = nullptr;

        SplashScreenWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
        bool on_timeout(void);


};

SplashScreenWindow::SplashScreenWindow (BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refGlade) :
    Gtk::Window(cobject), builder(refGlade)
{
    //this->builder->get_widget_derived("splash_screen_window_main", SplashScreenWindowPtr);
    this->builder->get_widget("SplashScreenImage", SplashScreenImagePtr);
    SplashScreenImagePtr->set("../media/splash/nxp_logo_small.png");
    
    //create slot for timeout signal
     int timeout_value = 1500; //in ms (1.5 sec)
     sigc::slot<bool>my_slot = sigc::mem_fun(*this, &SplashScreenWindow::on_timeout);
     //connect slot to signal
     Glib::signal_timeout().connect(my_slot, timeout_value);
     
     std::cout << "bbbbbbb" << std::endl;
}

bool SplashScreenWindow::on_timeout(void)
{
    std::cout << "aaaaaaaaaaaaaa" << std::endl;
    //this->SplashScreenWindowPtr->close();
    return this->SplashScreenWindowPtr->close();

