/* Copyright (c) 2019 Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier:	GPL-3.0+
 */
#include "gtk3-ml-experience.hpp"

Gtk3MlExperienceHandler::~Gtk3MlExperienceHandler(void) {}

Gtk3MlExperienceHandler::Gtk3MlExperienceHandler(BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refGlade) :
        Gtk::Window(cobject), builder(refGlade)
{
    this->paused = false;
    this->builder->get_widget("DrawingImage", this->drawingImage);
    this->builder->get_widget("closeButton", this->closeButton);
    this->builder->get_widget("resumePauseButton", this->resumePauseButton);
    this->builder->get_widget("videoButton", this->videoButton);
    this->closeButton->signal_clicked().connect(sigc::mem_fun(*this, &Gtk3MlExperienceHandler::stopCamera));
    this->resumePauseButton->signal_clicked().connect(sigc::mem_fun(*this, &Gtk3MlExperienceHandler::pauseResumeCamera));
    this->drawingImage->set("../images/image_not_found.png");
}

void Gtk3MlExperienceHandler::pauseResumeCamera(void)
{
    this->paused = !this->paused;
    if (this->paused) {
	    this->resumePauseButton->set_label("Resume");
    } else {
	    this->resumePauseButton->set_label("Start");
    }
}

void Gtk3MlExperienceHandler::stopCamera()
{
    std::cout << "closing stop camera" << std::endl;
	//Window::close();
camera.release();
}

void Gtk3MlExperienceHandler::aaa()
{
	std::cout << "aaa" << std::endl;
}


void Gtk3MlExperienceHandler::updateImage(cv::Mat & frame)
{
	if (!frame.empty()) {
        this->drawingImage->set(Gdk::Pixbuf::create_from_data(frame.data,
            Gdk::COLORSPACE_RGB, false, 8, frame.cols, frame.rows, frame.step));
		this->drawingImage->queue_draw();
	}
}

// ############################################################################

void run(void)
{
  //  gtk3MlExperienceHandler->closeButton->signal_clicked().connect(sigc::mem_fun(*gtk3MlExperienceHandler, &Gtk3MlExperienceHandler::stopCamera));
  //  gtk3MlExperienceHandler->resumePauseButton->signal_clicked().connect(sigc::mem_fun(*gtk3MlExperienceHandler, &Gtk3MlExperienceHandler::pauseResumeCamera));


    if (!initCamera(0))
        std::cerr << "Camera Failed" << std::endl;
    else {
        dispatcher.connect([&]() {
            mtx.lock();
            gtk3MlExperienceHandler->updateImage(frame);
            mtx.unlock();
        });
        enabledCamera = true;
        std::thread cameraThread = std::thread(&cameraLoop);
        Gtk::Main::run(*gtk3MlExperienceHandler);
        enabledCamera = false;
        cameraThread.join();
    }
    if (camera.isOpened())
            camera.release();
}

bool initCamera(int cameraDevice)
{
	bool r = camera.open(cameraDevice);	
	if (r) {
		camera.set(cv::CAP_PROP_FRAME_WIDTH, 640);
		camera.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
		camera.set(cv::CAP_PROP_FPS, 30);
		for (int i = 0; i < 10; i++)
			camera.grab();
	}
	return r;
}

void cameraLoop(void)
{
    while (enabledCamera) {
		bool continueToGrabe = true;
		bool paused = gtk3MlExperienceHandler->isPaused();
		if (!paused) {
			continueToGrabe = camera.read(frameBGR);
			if (continueToGrabe) {
				mtx.lock();
				cv::cvtColor(frameBGR, frame, cv::COLOR_BGR2RGB);
				mtx.unlock();
				dispatcher.emit();
			}
		} 
		if (!continueToGrabe) {
			enabledCamera = false;
			std::cerr << "The camera has stopped." << std::endl;
		} else if (paused) {
			std::this_thread::sleep_for(std::chrono::milliseconds(30));
		}
    }
}


