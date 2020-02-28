/* Copyright (c) 2019 Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier:	GPL-3.0+
 */
#ifndef GTK3_ML_EXPERIENCE_H_
#define GTK3_ML_EXPERIENCE_H_

#include <gtkmm.h>
#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>

#define MAIN_WINDOW_LAYOUT  "../main_window.glade"
#define MAIN_WINDOW_ID      "MainWindow"

void run(void);
bool initCamera(int cameraDevice);
void cameraLoop();

class Gtk3MlExperienceHandler : public Gtk::Window {
    public:
	    Gtk3MlExperienceHandler(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	    virtual ~Gtk3MlExperienceHandler();
	    void stopCamera();
	    void pauseResumeCamera();
	    void updateImage(cv::Mat & frame);
        void aaa();

	    bool isPaused() {
		    return this->paused;
	    }
    //private:
	    Glib::RefPtr<Gtk::Builder> builder;
	    Gtk::Image *drawingImage;
	    Gtk::Button *closeButton;
        Gtk::Button *videoButton;
	    Gtk::ToggleButton *resumePauseButton;
	    bool paused;
};

extern std::mutex mtx;
extern Glib::Dispatcher dispatcher;
extern volatile bool enabledCamera;
extern cv::VideoCapture camera;
extern cv::Mat frameBGR, frame;
extern Gtk3MlExperienceHandler *gtk3MlExperienceHandler; 

#endif /* GTK3_ML_EXPERIENCE_H_ */
