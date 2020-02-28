/* Copyright (c) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef IMX_ML_SSD_H_
#define IMX_ML_SSD_H_

#include <gtkmm.h>

#include <chrono>
#include <fstream>
#include <iostream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace dnn;

class SingleShotDetection
{
    private:  
        std::string modelPath = "";
        std::string configPath = "";
        std::string fileClassesPath = "";
        std::string imageInferenceFilePath = "";
        Mat camera;
        Net net;
        Mat img, new_img, inputBlob;
    
    protected:     
        std::vector<std::string> classes;
    
    public:
        Gtk::Image *ImagePtr = nullptr; 
        gint modelType;
               
        std::chrono::duration<double> elapsed_seconds;        
        std::string getTimeElapsedSeconds(void);
        std::string getTimeElapsedMiliSeconds(void);
        void setInferenceImage(std::string img);   
        void setDrawingImage(Gtk::Image *imgAreaPtr);
        void setModelSettings(std::string model, std::string config, std::string classes, gint type);
        void getClasses(void);     
        void setCamera(void);       
        bool run(void); 
};

#endif /* IMX_ML_SSD_H_ */
