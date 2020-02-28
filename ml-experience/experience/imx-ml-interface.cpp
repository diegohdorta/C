/* Copyright (c) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier: GPL3
 */
#include "imx-ml-interface.hpp"
#include "imx-ml-helper.hpp"
#include "imx-ml-sdd.hpp"

/* Window Handler function description
 *
 */

WindowHandler::WindowHandler(BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refGlade) :
    Gtk::Window(cobject), builder(refGlade)
{
    /* Window Main Pointer */
    this->builder->get_widget("window_main", this->WindowMainPtr);
    this->builder->get_widget("splash_screen_window", this->SplashScreenWindowPtr);

    /* Tool Bar */            
    this->builder->get_widget("HomeButton", this->HomeButtonPtr);
    this->HomeButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_home_button_clicked)); 
    
    this->builder->get_widget("UpdateButton", this->UpdateButtonPtr);
    this->UpdateButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_update_button_clicked));   
    
    this->builder->get_widget("ReleaseNotesButton", this->ReleaseNotesButtonPtr);
    this->ReleaseNotesButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_release_notes_button_clicked)); 
    
    this->builder->get_widget("AboutButton", this->AboutButtonPtr);
    this->AboutButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_about_button_clicked));
    
    this->builder->get_widget("QuitButton", this->QuitButtonPtr);
    this->QuitButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_quit_button_clicked));  

    /* Input Buttons */           
    this->builder->get_widget("FileBaseImageButton", this->FileBaseImageButtonPtr);
    this->FileBaseImageButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_file_base_image_button_clicked));

    this->builder->get_widget("FileBaseVideoButton", this->FileBaseVideoButtonPtr);
    this->FileBaseVideoButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_file_base_video_button_clicked));

    this->builder->get_widget("MIPIButton", this->MIPIButtonPtr);
    this->MIPIButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_mipi_button_clicked));

    this->builder->get_widget("WebcamButton", this->WebcamButtonPtr);
    this->WebcamButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_webcam_button_clicked));

    this->builder->get_widget("USBButton", this->USBButtonPtr);
    this->USBButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_usb_button_clicked));

    this->builder->get_widget("RSTPButton", this->RSTPButtonPtr);
    this->RSTPButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_rstp_button_clicked));

    /* Others */
    this->builder->get_widget("PlayButton", this->PlayButtonPtr);
    this->PlayButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_play_button_clicked));

    this->builder->get_widget("StopButton", this->StopButtonPtr);
    this->StopButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_stop_button_clicked));

    this->builder->get_widget("DrawingImage", this->DrawingImagePtr);
    
    this->builder->get_widget("RunSpinner", this->RunSpinnerPtr);

    this->builder->get_widget("BottomLabel", this->BottomLabelPtr);
    this->BottomLabelPtr->set_text("Copyright \xc2\xa9 2019 NXP Semiconductors");

    this->builder->get_widget("InferenceTimeSecondsLabel",
        this->InferenceTimeSecondsLabelPtr);
    this->InferenceTimeSecondsLabelPtr->set_text("-");

    this->builder->get_widget("InferenceTimeMiliSecondsLabel",
        this->InferenceTimeMiliSecondsLabelPtr);
    this->InferenceTimeMiliSecondsLabelPtr->set_text("-");
    
    this->builder->get_widget("ModelName",
        this->ModelNameLabelPtr);
    this->ModelNameLabelPtr->set_text("-");
    
    this->builder->get_widget("GraphName",
        this->GraphNameLabelPtr);
    this->GraphNameLabelPtr->set_text("-");
    
    this->builder->get_widget("ClassesName",
        this->ClassesNameLabelPtr);
    this->ClassesNameLabelPtr->set_text("-");

    this->builder->get_widget("StatusLabel", this->StatusLabelPtr);
    this->StatusLabelPtr->set_text("-");

    /* Performance Buttons */
    this->builder->get_widget("OpenCLButton", this->OpenCLButtonPtr);
    this->OpenCLButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_opencl_button_clicked));

    this->builder->get_widget("OpenGLButton", this->OpenGLButtonPtr);
    this->OpenGLButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_opengl_button_clicked));

    this->builder->get_widget("OpenVXButton", this->OpenVXButtonPtr);
    this->OpenVXButtonPtr->signal_clicked().connect(sigc::mem_fun(*this,
        &WindowHandler::on_openvx_button_clicked));

    this->builder->get_widget("ComboBoxInferenceEngines",
        this->ComboBoxInferenceEnginesPtr);
    this->ComboBoxInferenceEnginesPtr->signal_changed().connect(sigc::mem_fun(*this,
        &WindowHandler::on_combo_box_inference_engines_changed));

    this->builder->get_widget("ComboBoxApplications",
        this->ComboBoxApplicationsPtr);
    this->ComboBoxApplicationsPtr->signal_changed().connect(sigc::mem_fun(*this,
        &WindowHandler::on_combo_box_applications_changed));

    sigc::slot<bool>changeSplashToWindow = sigc::mem_fun(*this, &WindowHandler::splashScreenTimeout);
    Glib::signal_timeout().connect(changeSplashToWindow, this->splashScreenTimeoutValue); 
     
    set_initial_sensitive();    
}
  
bool WindowHandler::splashScreenTimeout(void)
{
    this->SplashScreenWindowPtr->hide();
    Gtk::Main::run(*this->WindowMainPtr);  
    return true;  
}
/* set_initial_sensitive() function description
 *
 */ 
      
void WindowHandler::set_initial_sensitive(void)
{    
    Glib::RefPtr<Gdk::Pixbuf> refPixbuf = Gdk::Pixbuf::create_from_file("../media/imgs/empty.png", 640, 480, true);
    this->DrawingImagePtr->set(refPixbuf);
    
    this->ComboBoxApplicationsPtr->set_active_text(" ");
    this->ComboBoxInferenceEnginesPtr->remove_all();
    this->ComboBoxApplicationsPtr->remove_all();
    
    this->InferenceTimeSecondsLabelPtr->set_text("-");
    this->InferenceTimeMiliSecondsLabelPtr->set_text("-");
    this->StatusLabelPtr->set_text("-");

    OpenCLButtonPtr->set_sensitive(false);
    OpenGLButtonPtr->set_sensitive(false);
    OpenVXButtonPtr->set_sensitive(false);
    
    /* File-based Input */
    FileBaseImageButtonPtr->set_sensitive(false);
    FileBaseVideoButtonPtr->set_sensitive(false);
    
    /* Hardare Input */
    MIPIButtonPtr->set_sensitive(false);
    WebcamButtonPtr->set_sensitive(false);
    USBButtonPtr->set_sensitive(false);
    RSTPButtonPtr->set_sensitive(false);
    
    /* Commands */
    UpdateButtonPtr->set_sensitive(true);
    ReleaseNotesButtonPtr->set_sensitive(true);
    PlayButtonPtr->set_sensitive(false);
    StopButtonPtr->set_sensitive(false);
}

/* on_home_button_clicked() function description
 *
 */

void WindowHandler::on_home_button_clicked(void)
{
    set_initial_sensitive();
}

/* on_update_button_clicked() function description
 *
 */

void WindowHandler::on_update_button_clicked(void)
{
    std::cout << "UPDATE BUTTON" << std::endl;        
    CSV_Helper demo;

    if (demo.run()) {
        Gtk::MessageDialog dialog(*this, "Warning", false , Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK);
        dialog.set_secondary_text("Missing Data files");
        this->ComboBoxInferenceEnginesPtr->remove_all();
        this->ComboBoxApplicationsPtr->remove_all();
        dialog.run(); 
    }
    else {                
        for (unsigned int i = 0; i < demo.inferencesArray.size(); i++) {
             this->ComboBoxInferenceEnginesPtr->append(demo.inferencesArray[i]);
        }
    }
} 

/* on_release_notes_button_clicked() function description
 *
 */

void WindowHandler::on_release_notes_button_clicked(void)
{
    Gtk::Window ReleaseNotes;
    ReleaseNotes.set_title("Release Notes");
    ReleaseNotes.set_default_size(640, 480);
    Gtk::TextView m_TextView;
    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
 
    const gchar *dataTreeFile = "../data/release-notes.txt";
        
    if (g_file_test (dataTreeFile, G_FILE_TEST_EXISTS)) {
        gsize length;
        gchar *content;
        if (g_file_get_contents (dataTreeFile, &content, &length, NULL)) {                   
            m_refTextBuffer = Gtk::TextBuffer::create();
            m_refTextBuffer->set_text(content);    
            g_free (content);
        }
    }
    m_TextView.set_buffer(m_refTextBuffer);                 
    ReleaseNotes.add(m_TextView);
    ReleaseNotes.show_all();
    Gtk::Main::run(ReleaseNotes);     
}

/* on_about_button_clicked() function description
 *
 */

void WindowHandler::on_about_button_clicked(void)
{            
    Gtk::AboutDialog aboutDialogBoxPtr;  
    // Bug -> GtkDialog mapped without a transient parent. This is discouraged.
    aboutDialogBoxPtr.set_logo(Gdk::Pixbuf::create_from_file("../media/splash/nxp_logo_small.png"));
    aboutDialogBoxPtr.set_program_name("Machine Learning Experience Environment");
    aboutDialogBoxPtr.set_version("1.0.0");
    aboutDialogBoxPtr.set_copyright("Copyright \xc2\xa9 2019 NXP Semiconductors");
    
    std::vector<Glib::ustring> authors;
    authors.push_back("Diego Dorta");
    authors.push_back("Vanessa Maegima");
    aboutDialogBoxPtr.set_authors(authors);            

    std::vector<Glib::ustring> documenters;
    documenters.push_back("Diego Dorta");
    aboutDialogBoxPtr.set_documenters(documenters);
    
    aboutDialogBoxPtr.set_license_type(Gtk::LICENSE_MIT_X11);
    aboutDialogBoxPtr.set_website_label("NXP Semicondutors");
    aboutDialogBoxPtr.set_website("https://www.nxp.com/");
    aboutDialogBoxPtr.set_title("");           
    aboutDialogBoxPtr.run();
}   

/* on_quit_button_clicked() function description
 *
 */
     
void WindowHandler::on_quit_button_clicked(void)
{
    //Gtk::Main::quit();
    this->WindowMainPtr->close();
}

/* on_opencl_button_clicked() function description
 *
 */

void WindowHandler::on_opencl_button_clicked(void)
{
    std::cout << "OPENCL BUTTON" << std::endl;
}

/* on_opengl_button_clicked() function description
 *
 */

void WindowHandler::on_opengl_button_clicked(void)
{
    std::cout << "OPENGL BUTTON" << std::endl;
}

/* on_openvx_button_clicked() function description
 *
 */

void WindowHandler::on_openvx_button_clicked(void)
{
    std::cout << "OPENVX BUTTON" << std::endl;
}        

/* on_file_base_image_button_clicked() function description
 *
 */

void WindowHandler::on_file_base_image_button_clicked(void)
{
    Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_default_size(640, 480); 
    dialog.set_current_folder("/home");

    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK); 
    
    Glib::RefPtr<Gtk::FileFilter> jpg = Gtk::FileFilter::create();
    Glib::RefPtr<Gtk::FileFilter> jpeg = Gtk::FileFilter::create();
    Glib::RefPtr<Gtk::FileFilter> png = Gtk::FileFilter::create();
    jpg->set_name( "jpg" );
    jpeg->set_name( "jpeg" );
    png->set_name( "png" );
    jpg->add_pattern( "*.jpg" );
    jpeg->add_pattern( "*.jpeg" );
    png->add_pattern( "*.png" );
    dialog.add_filter(jpg);
    dialog.add_filter(jpeg);
    dialog.add_filter(png);
   
    gint result = dialog.run();
    switch(result) {
        case Gtk::RESPONSE_OK: {
            this->filename = dialog.get_filename();            
            this->InferenceTimeSecondsLabelPtr->set_text("-");
            this->InferenceTimeMiliSecondsLabelPtr->set_text("-");
            this->StatusLabelPtr->set_text("-"); 
            break;
        }
        default: {
            std::cout << "Unexpected button clicked." << std::endl;
            break;
        }
    }
    Glib::RefPtr<Gdk::Pixbuf> refPixbuf = Gdk::Pixbuf::create_from_file(filename, 640, 480, true);
    refPixbuf->scale_simple(640, 480, Gdk::INTERP_BILINEAR);
    this->DrawingImagePtr->set(refPixbuf);
    PlayButtonPtr->set_sensitive(true);
}

/* on_file_base_video_button_clicked() function description
 *
 */

void WindowHandler::on_file_base_video_button_clicked(void)
{
    std::cout << "FILE VIDEO BUTTON" << std::endl;
}

/* on_mipi_button_clicked() function description
 *
 */

void WindowHandler::on_mipi_button_clicked(void)
{
    std::cout << "MIPI BUTTON" << std::endl;
}

/* on_webcam_button_clicked() function description
 *
 */

void WindowHandler::on_webcam_button_clicked(void)
{
    std::cout << "WEBCAM BUTTON" << std::endl;
}

/* on_usb_button_clicked() function description
 *
 */

void WindowHandler::on_usb_button_clicked(void)
{
    std::cout << "USB BUTTON" << std::endl;
}

/* on_rstp_button_clicked() function description
 *
 */

void WindowHandler::on_rstp_button_clicked(void)
{
    std::cout << "RSTP BUTTON" << std::endl;
}

/* on_play_button_clicked() function description
 *
 */

void WindowHandler::on_play_button_clicked(void)
{
    /* Continue: Colect all the combobox and check them */            
    PlayButtonPtr->set_sensitive(false);
    RunSpinnerPtr->start();
    
    SingleShotDetection ssd;
    ssd.setInferenceImage(this->filename);
    ssd.setDrawingImage(this->DrawingImagePtr);
    ssd.setModelInformation(this->ModelNameLabelPtr,
                            this->GraphNameLabelPtr,
                            this->ClassesNameLabelPtr);
    
    /* Temporary uglyhack */
    gint napp = 0;
    std::string opencv_sdd_caffe_object = "Object_Detection_Caffe";
    std::string opencv_sdd_tf_object = "Object_Detection_TensorFlow";

    std::string appChoosen = this->ComboBoxApplicationsPtr->get_active_text();

    if (appChoosen.compare(opencv_sdd_caffe_object) == 0) {
        napp = 1;
        std::string model, config, classes;
        model = "../modules/model/MobileNetSSD_deploy.caffemodel";
        config = "../modules/model/MobileNetSSD_deploy.prototxt";
        classes = "../modules/model/classes.txt";
        ssd.setModelSettings(model, config, classes, napp);
    }   
    if (appChoosen.compare(opencv_sdd_tf_object) == 0) {
        napp = 2;
        std::string model, config, classes;
        model = "../modules/model/frozen_inference_graph.pb";
        config = "../modules/model/graph.pbtxt";
        classes = "../modules/model/classes.txt";
        ssd.setModelSettings(model, config, classes, napp);
    }
   
   /* This ugly will be remove soon */
   
    switch (napp) {
        case 1:
        {     /* Caffe inference using OpenCV DNN */ 
            std::cout << "opencv_sdd_caffe_object" << std::endl;            
            if (!ssd.run()) {
                Gtk::MessageDialog dialog(*this, "Warning", false , Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK);
                dialog.set_secondary_text("Missing input");
                dialog.run();
                PlayButtonPtr->set_sensitive(true);
                RunSpinnerPtr->stop();             
            } 
            else {       
                PlayButtonPtr->set_sensitive(false); 
                RunSpinnerPtr->stop();        
                std::string s = ssd.getTimeElapsedSeconds();
                s.append(" s");                                           
                std::string ms = ssd.getTimeElapsedMiliSeconds();
                ms.append(" µs");                           
                this->InferenceTimeSecondsLabelPtr->set_text(s);
                this->InferenceTimeMiliSecondsLabelPtr->set_text(ms);
                this->StatusLabelPtr->set_text("Done");
                PlayButtonPtr->set_sensitive(true);      
            }
            break;
         } 
        case 2:
        {   /* TensorFlow inference using OpenCV DNN */
            std::cout << "opencv_sdd_tf_object" << std::endl;
            if (!ssd.run()) {
                Gtk::MessageDialog dialog(*this, "Warning", false , Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK);
                dialog.set_secondary_text("Missing input");
                dialog.run();
                PlayButtonPtr->set_sensitive(true);
                RunSpinnerPtr->stop();             
            } 
            else {       
                PlayButtonPtr->set_sensitive(false); 
                RunSpinnerPtr->stop();        
                std::string s = ssd.getTimeElapsedSeconds();
                s.append(" s");                                           
                std::string ms = ssd.getTimeElapsedMiliSeconds();
                ms.append(" µs");                           
                this->InferenceTimeSecondsLabelPtr->set_text(s);
                this->InferenceTimeMiliSecondsLabelPtr->set_text(ms);
                this->StatusLabelPtr->set_text("Done");
                PlayButtonPtr->set_sensitive(true);      
            }
            break; 
        }
        default:
        {
            std::cout << "default" << std::endl;
            PlayButtonPtr->set_sensitive(true);
            RunSpinnerPtr->stop();   
            break;
        }
        
        
    }

    //  AQUI DEVO COLETAR TODOS OS COMBO B0X AND CHECA-LOS ANTES DE RODAR   
}

/* on_stop_button_clicked() function description
 *
 */

void WindowHandler::on_stop_button_clicked(void)
{
    std::cout << "STOP BUTTON" << std::endl;
}

/* on_combo_box_inference_engines_changed() function description
 *
 */

void WindowHandler::on_combo_box_inference_engines_changed(void)
{
    std::cout << "COMBO BOX INFERENCE ENGINES" << std::endl;    
    //CSV_Helper demo;
    demo.file = this->ComboBoxInferenceEnginesPtr->get_active_text();
    if (demo.run()) {
        Gtk::MessageDialog dialog(*this, "Warning", false , Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK);
        dialog.set_secondary_text("Missing Data files");
        dialog.run();  
        this->ComboBoxInferenceEnginesPtr->remove_all();
        this->ComboBoxApplicationsPtr->remove_all();
        FileBaseImageButtonPtr->set_sensitive(false);
    } 
    else {
        for (unsigned int i = 0; i < demo.inferencesArray.size(); i++) {
             this->ComboBoxApplicationsPtr->append(demo.inferencesArray[i]);
        }
    }
    std::cout << std::endl;
}

/* on_combo_box_applications_changed() function description
 *
 */

void WindowHandler::on_combo_box_applications_changed(void)
{
    std::cout << "COMBO BOX APPLICATIONS" << std::endl;    
    FileBaseImageButtonPtr->set_sensitive(true);
    //PlayButtonPtr->set_sensitive(true);  
}
