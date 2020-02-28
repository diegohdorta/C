/* Copyright (c) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier: GPL3
 */
#include "imx-ml-sdd.hpp"
       
std::string SingleShotDetection::getTimeElapsedSeconds(void)
{   
    auto x = std::chrono::duration<double>(this->elapsed_seconds);
    std::string time = std::to_string(x.count());
    return time;
}

std::string SingleShotDetection::getTimeElapsedMiliSeconds(void)
{   
    auto x = std::chrono::duration_cast<std::chrono::microseconds>(this->elapsed_seconds);
    std::string time = std::to_string(x.count());
    return time;
}

void SingleShotDetection::setInferenceImage(std::string img)
{
    this->imageInferenceFilePath = img;
}   

void SingleShotDetection::setDrawingImage(Gtk::Image *imgAreaPtr)
{
    this->ImagePtr = imgAreaPtr;
}

void SingleShotDetection::setModelInformation(Gtk::Label *ModelPtr,
                                              Gtk::Label *GraphPtr,
                                              Gtk::Label *ClassesPtr)
{
    this->ModelLabelPtr = ModelPtr;
    this->GraphLabelPtr = GraphPtr;
    this->ClassesLabelPtr = ClassesPtr;

}

void SingleShotDetection::setModelSettings(std::string model,
                                            std::string config,
                                            std::string classes,
                                            gint type)
{
    this->modelPath = model;
    this->configPath = config;
    this->fileClassesPath = classes;
    this->modelType = type;
    
    if (type == 1) {
        this->net = readNetFromCaffe(this->configPath, this->modelPath);
    }
    if (type == 2) {
        this->net = readNetFromTensorflow(this->modelPath, this->configPath);
        this->net.setPreferableBackend(DNN_BACKEND_DEFAULT);
        this->net.setPreferableTarget(DNN_TARGET_OPENCL);
    }
}

   
void SingleShotDetection::getClasses(void)
{
    std::ifstream ifs(this->fileClassesPath.c_str());
    std::string line;     
    while (std::getline(ifs, line)) {
        this->classes.push_back(line);     
    }   
}   
     
void SingleShotDetection::setCamera(void)
{ 
    this->img = imread(this->imageInferenceFilePath, IMREAD_COLOR);
}  
    
bool SingleShotDetection::run(void)
{  
    auto start = std::chrono::system_clock::now();   
    this->getClasses();  
    if (imageInferenceFilePath.empty()) {
        return false;
    }
    std::vector<String> outNames(3);
    outNames[0] = "concat";
    outNames[1] = "concat_1";
    outNames[2] = "detection_out";
    
    setCamera();
    //this->camera >> img; 
    resize(this->img, this->new_img, Size(300, 300));
    
    this->inputBlob = blobFromImage(this->new_img, 0.007843,
                                    Size(300, 300),
                                    Scalar(127.5, 127.5, 127.5), false, false);
    
    if (this->modelType == 1) {
        this->net.setInput(inputBlob, "data");
    }
    
    if (this->modelType == 2) {
        this->net.setInput(inputBlob);    
    }
    
    Mat detection = this->net.forward("detection_out");
    if (this->modelType == 2) {       
        Mat detection = this->net.forward();
    }
    
    Mat detectionMat(detection.size[2],
                     detection.size[3],
                     CV_32F,
                     detection.ptr<float>());

    for (int i = 0; i < detectionMat.rows; i++) {
        float confidence = detectionMat.at<float>(i, 2);

        if (confidence > 0.7) {
            int xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * img.cols);
            int yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * img.rows);
            int xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * img.cols);
            int yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * img.rows);

            Rect object((int)xLeftBottom, (int)yLeftBottom,
            (int)(xRightTop - xLeftBottom),
            (int)(yRightTop - yLeftBottom));

            rectangle(img, object, Scalar(0, 255, 0));

            int baseLine = 0;
            int classId = static_cast<int>(detectionMat.at<float>(i, 1));

            std::string label = format("%s: %.4f", (this->classes.empty() ?
                format("Class #%d", classId).c_str() :
                this->classes[classId].c_str()), confidence);

            Size labelSize = getTextSize(label,
                FONT_HERSHEY_TRIPLEX, 0.5, 1, &baseLine);
            rectangle(this->img, Rect(Point(xLeftBottom, yLeftBottom - labelSize.height),
                Size(labelSize.width, labelSize.height + baseLine)),
                Scalar(190, 200, 255), 0);
            putText(this->img, label, Point(xLeftBottom, yLeftBottom),
                FONT_HERSHEY_DUPLEX, 1, Scalar(255,255,255));
        }
    }
    imwrite(OUTPUT_NAME, this->img);  
    auto end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;

    Glib::RefPtr<Gdk::Pixbuf> refPixbuf =
        Gdk::Pixbuf::create_from_file(OUTPUT_NAME, 640, 480, true);
    this->ImagePtr->set(refPixbuf);
    this->ModelLabelPtr->set_text(this->modelPath.erase(0, 17));
    this->GraphLabelPtr->set_text(this->configPath.erase(0, 17));
    this->ClassesLabelPtr->set_text(this->fileClassesPath.erase(0, 17));
    return true;    
}  
