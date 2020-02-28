#include <fstream>
#include <sstream>
#include <iostream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace dnn;

std::vector<std::string> classes;

int main() {
    String model = "MobileNetSSD_deploy.caffemodel";
    String config = "MobileNetSSD_deploy.prototxt";
    
    std::string file = "classes.txt";
    std::ifstream ifs(file.c_str());
    std::string line;
    while (std::getline(ifs, line))
        classes.push_back(line);
       
    Net net = readNetFromCaffe(config, model);

    VideoCapture cap;
    //cap.open("v4l2src ! video/x-raw,width=640,height=480 ! videoconvert ! appsink");
    cap.open(0);

    Mat img;

    while (waitKey(1) < 0 ) {
        cap >> img;
        Mat new_img;
        resize(img, new_img, Size(300, 300));
        
        //Mat inputBlob = blobFromImage(img, 1.0, Size(300, 300), Scalar(104.0, 177.0, 123.0), false, false);
        Mat inputBlob = blobFromImage(new_img, 0.007843, Size(300, 300), Scalar(127.5, 127.5, 127.5), false, false);
        net.setInput(inputBlob, "data");
        
        Mat detection = net.forward("detection_out");
        Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
        
        for(int i = 0; i < detectionMat.rows; i++) {
            float confidence = detectionMat.at<float>(i, 2);

            if(confidence > 0.7)
            {
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
                
                std::string label = format("%s: %.4f", (classes.empty() ? format("Class #%d", classId).c_str() :  classes[classId].c_str()), confidence);
                                       
                Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                rectangle(img, Rect(Point(xLeftBottom, yLeftBottom - labelSize.height),
                                      Size(labelSize.width, labelSize.height + baseLine)),
                          Scalar(255, 255, 255), CV_FILLED);
                putText(img, label, Point(xLeftBottom, yLeftBottom),
                        FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
            }
        }

        imshow("cam", img);
    }
    
    return 0;
}
