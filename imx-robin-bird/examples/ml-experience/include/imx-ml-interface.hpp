/* Copyright (c) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef IMX_ML_INTERFACE_H_
#define IMX_ML_INTERFACE_H_

#include <gtkmm.h>
#include "imx-ml-helper.hpp"

class WindowHandler : public Gtk::Window
{
    public:
	    WindowHandler(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	 
	    Glib::RefPtr<Gtk::Builder> builder;
	    Gtk::Window *WindowMainPtr = nullptr;
	    Gtk::Window *SplashScreenWindowPtr = nullptr;	    
	    
	    Gtk::ToolButton *HomeButtonPtr = nullptr;
	    Gtk::ToolButton *UpdateButtonPtr = nullptr;
	    Gtk::ToolButton *ReleaseNotesButtonPtr = nullptr;
	    Gtk::ToolButton *AboutButtonPtr = nullptr;
	    Gtk::ToolButton *QuitButtonPtr = nullptr;
	    
	    Gtk::Button *OpenCLButtonPtr = nullptr;
	    Gtk::Button *OpenGLButtonPtr = nullptr;
	    Gtk::Button *OpenVXButtonPtr = nullptr;

	    Gtk::Button *FileBaseImageButtonPtr = nullptr;
	    Gtk::Button *FileBaseVideoButtonPtr = nullptr;
	    Gtk::Button *MIPIButtonPtr = nullptr;
	    Gtk::Button *WebcamButtonPtr = nullptr;
        Gtk::Button *USBButtonPtr = nullptr;
        Gtk::Button *RSTPButtonPtr = nullptr;

        Gtk::Button *PlayButtonPtr = nullptr;
        Gtk::Button *StopButtonPtr = nullptr;
        
	    Gtk::Image *DrawingImagePtr = nullptr;
	    Gtk::Spinner *RunSpinnerPtr = nullptr;
	    Gtk::ComboBoxText *ComboBoxInferenceEnginesPtr = nullptr;
	    Gtk::ComboBoxText *ComboBoxApplicationsPtr = nullptr;
	    
	    Gtk::Label *BottomLabelPtr = nullptr;
	    Gtk::Label *InferenceTimeSecondsLabelPtr = nullptr;
	    Gtk::Label *InferenceTimeMiliSecondsLabelPtr = nullptr;
	    Gtk::Label *ModelNameLabelPtr = nullptr;
	    Gtk::Label *GraphNameLabelPtr = nullptr;
	    Gtk::Label *ClassesNameLabelPtr = nullptr;
	    Gtk::Label *StatusLabelPtr = nullptr;
	    
	    CSV_Helper demo;
	    std::string filename;
	    gint splashScreenTimeoutValue = 5000; 

        /* Splash Screen Timeout */
        bool splashScreenTimeout(void);

        /* Interface functions */
        void set_initial_sensitive(void);
        
        /* Callback functions */
        void on_home_button_clicked(void);
        void on_update_button_clicked(void);
        void on_release_notes_button_clicked(void);
        void on_about_button_clicked(void); 
        void on_quit_button_clicked(void);
        void on_opencl_button_clicked(void);
        void on_opengl_button_clicked(void);
        void on_openvx_button_clicked(void);
        void on_file_base_image_button_clicked(void);
        void on_file_base_video_button_clicked(void);
        void on_mipi_button_clicked(void);
        void on_webcam_button_clicked(void);
        void on_usb_button_clicked(void);
        void on_rstp_button_clicked(void);
        void on_play_button_clicked(void);
        void on_stop_button_clicked(void);
        void on_combo_box_inference_engines_changed(void);
        void on_combo_box_applications_changed(void);
};

#endif /* IMX_ML_INTERFACE_H_ */
