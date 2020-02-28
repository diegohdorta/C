/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.
 *
 ** Copyright 2020 NXP Semiconductors
 ** Author: Diego Dorta <diego.dorta@nxp.com> 01/02/2020
 **
 ** This example was copied and adapted from TensorFlow examples respecting its
 ** rights. All the modified parts below are according to TF's LICENSE terms.
 **
 ** SPDX-License-Identifier:    Apache-2.0
 */
#include <fstream>
#include <iostream>
#include <sys/time.h>

//#include "tensorflow/contrib/lite/kernels/register.h"
//#include "tensorflow/contrib/lite/model.h"
#include "tensorflow/contrib/lite/optional_debug_tools.h"
//#include "tensorflow/contrib/lite/string_util.h"

#include "tensorflow/contrib/lite/examples/label_image/bitmap_helpers.h"
#include "tensorflow/contrib/lite/examples/label_image/get_top_n.h"

#include <opencv2/dnn.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

namespace tflite {
    namespace label_image {

        double get_us(struct timeval t)
        {
            return (t.tv_sec * 1000000 + t.tv_usec);
        }

        TfLiteStatus ReadLabelsFile(const string& file_name, std::vector<string>* result, size_t* found_label_count)
        {
            std::ifstream file(file_name);
            result->clear();
            string line;

            while (std::getline(file, line)) {
                result->push_back(line);
            }

            *found_label_count = result->size();
            const int padding = 16;

            while (result->size() % padding) {
                result->emplace_back();
            }
            return kTfLiteOk;
        }

        void RunInference(Settings* s)
        {
        
         std::cout << "DEBUG" << std::endl;
        
            std::unique_ptr<tflite::FlatBufferModel> model;
            std::unique_ptr<tflite::Interpreter> interpreter;
            model = tflite::FlatBufferModel::BuildFromFile(s->model_name.c_str());

            model->error_reporter();

            tflite::ops::builtin::BuiltinOpResolver resolver;
            tflite::InterpreterBuilder(*model, resolver)(&interpreter);

            interpreter->UseNNAPI(1);

  if (s->number_of_threads != -1) {
   interpreter->SetNumThreads(s->number_of_threads);
 }
            int image_width = 160;
            int image_height = 160;
            int image_channels = 3;
            std::vector<uint8_t> in = read_bmp(s->input_bmp_name, &image_width,
            &image_height, &image_channels, s);

            int input = interpreter->inputs()[0];

            const std::vector<int> inputs = interpreter->inputs();
            const std::vector<int> outputs = interpreter->outputs();

            if (interpreter->AllocateTensors() != kTfLiteOk) {
                std::cerr << "Failed to allocate tensors!" << std::endl;
            }

            if (s->verbose) PrintInterpreterState(interpreter.get());

            // get input dimension from the input tensor metadata
            // assuming one input only
            TfLiteIntArray* dims = interpreter->tensor(input)->dims;
            int wanted_height = dims->data[1];
            int wanted_width = dims->data[2];
            int wanted_channels = dims->data[3];

            switch (interpreter->tensor(input)->type)
            {
                case kTfLiteFloat32:
                    s->input_floating = true;
                    resize<float>(interpreter->typed_tensor<float>(input), in.data(), image_height, image_width, image_channels, wanted_height, wanted_width, wanted_channels, s);
                    break;
                case kTfLiteUInt8:
                    resize<uint8_t>(interpreter->typed_tensor<uint8_t>(input), in.data(), image_height, image_width, image_channels, wanted_height, wanted_width, wanted_channels, s);
                    break;
                default:
                    exit(EXIT_FAILURE);
            }

            profiling::Profiler* profiler = new profiling::Profiler();
            interpreter->SetProfiler(profiler);

            if (s->profiling) profiler->StartProfiling();

            struct timeval start_time, stop_time;
            gettimeofday(&start_time, nullptr);
            for (int i = 0; i < s->loop_count; i++) {
                if (interpreter->Invoke() != kTfLiteOk) {
                    std::cerr << "Failed to invoke tflite!\n" << std::endl;
                }
            }
            gettimeofday(&stop_time, nullptr);
            std::cout << "Average Time: " << (get_us(stop_time) - get_us(start_time)) / (s->loop_count * 1000) << " ms \n" << std::endl;

            const float threshold = 0.001f;

            std::vector<std::pair<float, int>> top_results;

            int output = interpreter->outputs()[0];
            TfLiteIntArray* output_dims = interpreter->tensor(output)->dims;
            // assume output dims to be something like (1, 1, ... ,size)
            auto output_size = output_dims->data[output_dims->size - 1];

            switch (interpreter->tensor(output)->type)
            {
                case kTfLiteFloat32:
                    get_top_n<float>(interpreter->typed_output_tensor<float>(0), output_size, s->number_of_results, threshold, &top_results, true);
                    break;
                case kTfLiteUInt8:
                    get_top_n<uint8_t>(interpreter->typed_output_tensor<uint8_t>(0), output_size, s->number_of_results, threshold, &top_results, false);
                    break;
                default:
                    std::cerr << "Can not handle output type " << interpreter->tensor(input)->type << " yet" << std::endl;
                    exit(EXIT_FAILURE);
            }

            std::vector<string> labels;
            size_t label_count;

            if (ReadLabelsFile(s->labels_file_name, &labels, &label_count) != kTfLiteOk) {
                exit(EXIT_FAILURE);
            }
            for (const auto& result : top_results) {
             float confidence = result.first;
             int index = result.second;
             std::cerr << confidence << " - " << labels[index] << "\n";
            }
        }
    } 
}

int main(int argc, char** argv)
{
  tflite::label_image::Settings s;

  s.model_name = "model/detect.tflite";
  s.labels_file_name = "model/labelmap.txt";
  s.input_bmp_name = "frame.bmp";

  cv::VideoCapture cap;
  cap.open("v4l2src ! video/x-raw,width=640,height=480 ! videoconvert ! appsink");

  cv::Mat frame;
  cv::Mat frame_bmp;

  while (cv::waitKey(1) < 0) {
    std::cout << "DEBUG" << std::endl;
    cap >> frame;
    frame.convertTo(frame_bmp, CV_8UC3);
    cv::imwrite("frame.bmp", frame_bmp);
    cv::imshow("Switch Demo", frame);
    tflite::label_image::RunInference(&s);
    std::cout << "aaaa" << std::endl;
  }
  
  return EXIT_SUCCESS;
}
