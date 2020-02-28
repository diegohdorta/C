/*
 * SSD - Single Shot Detection using Caffe
 * Copyright (c) 2019 Diego Dorta <diego.dorta@nxp.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace cv;
using namespace dnn;

#define CAFFE_MODEL "model/MobileNetSSD_deploy.caffemodel"
#define CAFFE_CONFIG "model/MobileNetSSD_deploy.prototxt"
#define CAFFE_LABELS "model/labels.txt"
#define V4L2SRC "v4l2src ! video/x-raw,width=640,height=480 ! videoconvert ! appsink"
#define CONFIDENCE  0.7

int main(void)
{
    int i = 0;
    int xlb;
    int ylb;
    int xrt;
    int yrt;
    
    std::vector<std::string> labels;
    std::string model = CAFFE_MODEL;
    std::string config = CAFFE_CONFIG;
    std::string labelsFile = CAFFE_LABELS;
    
    std::ifstream ifs(labelsFile.c_str());
    std::string line;
    
    while (std::getline(ifs, line)) {
        labels.push_back(line);
    }    
    Mat frame;    
    Net net = readNetFromCaffe(config, model);
    VideoCapture camera;
    camera.open(V4L2SRC);

    while (waitKey(1) < 0) {
        camera >> frame;
        Mat new_frame;
        resize(frame, new_frame, Size(300, 300));
        Mat inputBlob = blobFromImage(new_frame,
                                      0.007843,
                                      Size(300, 300),
                                      Scalar(127.5, 127.5, 127.5),
                                      false,
                                      false);
        net.setInput(inputBlob, "data");        
        Mat detection = net.forward("detection_out");
        Mat detectionMat(detection.size[2],
                         detection.size[3],
                         CV_32F,
                         detection.ptr<float>());
        
        for (i = 0; i < detectionMat.rows; i++) {
            float cfdc = detectionMat.at<float>(i, 2);
            if (cfdc > CONFIDENCE) {
                xlb = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
                ylb = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
                xrt = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
                yrt = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

                Rect object((int)xlb, (int)ylb, (int)(xrt - xlb), (int)(yrt - ylb));
                rectangle(frame, object, Scalar(0, 255, 0));

                int baseLine = 0;
                int classId = static_cast<int>(detectionMat.at<float>(i, 1));                
                std::string label = format("%s: %.4f",
                    (labels.empty() ?
                     format("# %d", classId).c_str() :
                     labels[classId].c_str()), cfdc);
                                       
                Size labelSize = getTextSize(label,
                                    FONT_HERSHEY_SIMPLEX,
                                    0.5, 1, &baseLine);
                rectangle(frame, Rect(Point(xlb, ylb - labelSize.height),
                    Size(labelSize.width, labelSize.height + baseLine)),
                          Scalar(255, 255, 255), CV_FILLED);
                putText(frame, label, Point(xlb, ylb),
                    FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
            }
        }
        imshow("app-caffe", frame);
    }    
    return EXIT_SUCCESS;
}
