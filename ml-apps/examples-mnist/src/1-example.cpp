/* Copyright © 2017 Arm Ltd. All rights reserved.
 * See LICENSE file in the project root for full license information.
 *
 ** 04/06/2019 Diego Dorta <diego.dorta@nxp.com>
 **
 ** This example was copied from ARM examples respecting its rights. All the
 ** modified parts below are according to Apache License 2.0.
 **
 ** This example is only for training purposes, the code below has only a few
 ** modifications in order to get a better overview of the Mnist data example.
 **
 ** References:
 ** https://github.com/ARM-software/ML-examples/
 ** http://yann.lecun.com/exdb/mnist/
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <array>
#include <algorithm>
#include <chrono>
#include <ctime>
#include "armnn/ArmNN.hpp"
#include "armnn/Exceptions.hpp"
#include "armnn/Tensor.hpp"
#include "armnn/INetwork.hpp"
#include "armnnCaffeParser/ICaffeParser.hpp"

#include "../armnn/mnist_loader.hpp"
#define CAFFE_MODEL "model/lenet_iter_9000.caffemodel"

armnn::InputTensors MakeInputTensors(const std::pair<armnn::LayerBindingId,
    armnn::TensorInfo>& input,
    const void* inputTensorData)
{
    return { { input.first, armnn::ConstTensor(input.second, inputTensorData) } };
}

armnn::OutputTensors MakeOutputTensors(const std::pair<armnn::LayerBindingId,
    armnn::TensorInfo>& output,
    void* outputTensorData)
{
    return { { output.first, armnn::Tensor(output.second, outputTensorData) } };
}

int main(int argc, char *argv[])
{
    std::string dataDir = "data/";   
    int failed = 0;
    int nTests = atoi(argv[1]);

    if (argc < 2 || nTests > 9999) {
        std::cout << "You should specify number of tests!" << std::endl;
        return EXIT_FAILURE;
    }
    
    auto totalTimeStart = std::chrono::system_clock::now();
    for (int testImageIndex = 0; testImageIndex < nTests; testImageIndex++) {    
        auto start = std::chrono::system_clock::now();
        std::unique_ptr<MnistImage> input = loadMnistImage(dataDir, testImageIndex);
        if (input == nullptr) {
            return EXIT_FAILURE;
        }

        /* Import the Caffe model */     
        armnnCaffeParser::ICaffeParserPtr
            parser = armnnCaffeParser::ICaffeParser::Create();
        armnn::INetworkPtr
            network = parser->CreateNetworkFromBinaryFile(CAFFE_MODEL,
                        { }, { "prob" });

        /* Find the binding points for the input and output nodes */
        armnnCaffeParser::BindingPointInfo
            inputBindingInfo = parser->GetNetworkInputBindingInfo("data");
        armnnCaffeParser::BindingPointInfo
            outputBindingInfo = parser->GetNetworkOutputBindingInfo("prob");

        armnn::IRuntime::CreationOptions options;
        armnn::IRuntimePtr runtime = armnn::IRuntime::Create(options);
        armnn::IOptimizedNetworkPtr optNet = armnn::Optimize(*network,
            {armnn::Compute::CpuRef}, runtime->GetDeviceSpec());

        /* Load the optimized network onto the runtime device */
        armnn::NetworkId networkIdentifier;
        runtime->LoadNetwork(networkIdentifier, std::move(optNet));

        /* Run a single inference on the test image */
        std::array<float, 10> output;
        runtime->EnqueueWorkload(networkIdentifier,
            MakeInputTensors(inputBindingInfo, &input->image[0]),
            MakeOutputTensors(outputBindingInfo, &output[0]));

        /* Convert 1-hot output to an integer label and print */
        unsigned int predictLabel = std::distance(output.begin(),
                        std::max_element(output.begin(), output.end()));
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsedSeconds = end - start;
        
        if (input->label == predictLabel) {
            std::cout << "[" << testImageIndex << "]"
                      << "\tCaffe >> Actual: " << input->label
                      << "  Predict: " << predictLabel
                      << "  Time: " << elapsedSeconds.count()
                      << "s" << std::endl;
        } else {
            std::cout << "[" << testImageIndex << "]"
                      << "\tCaffe >> Actual: " << input->label
                      << "  Predict: " << predictLabel
                      << "  Time: " << elapsedSeconds.count()
                      << "s\tFAILED" << std::endl;
            failed++;
        }   
    }
    auto totalTimeEnd = std::chrono::system_clock::now();
        std::chrono::duration<double> totalTime = totalTimeEnd - totalTimeStart;
    std::cout << "Total Time: " << totalTime.count()
              << "s\tSucessfull: " << nTests
              << "\tFailed: " << failed << std::endl;    
    return EXIT_SUCCESS;
}
