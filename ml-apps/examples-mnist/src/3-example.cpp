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
#include <cstring>
#include "armnn/ArmNN.hpp"
#include "armnn/Exceptions.hpp"
#include "armnn/Tensor.hpp"
#include "armnn/INetwork.hpp"
#include "armnnTfParser/ITfParser.hpp"

#include "../armnn-draw/mnist_loader.hpp"
#define TENSOR_MODEL "model/optimized_mnist_tf.pb"
#define INPUT_TENSOR "input_tensor"
#define OUTPUT_TENSOR "fc2/output_tensor"

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

int main(int argc, char** argv)
{
    std::string modelFile = TENSOR_MODEL;
    std::string modelInputLayer = INPUT_TENSOR;
    std::string modelOutputLayer = OUTPUT_TENSOR;

    if (argc != 2) {
        return EXIT_FAILURE;
    }

    armnnTfParser::ITfParserPtr parser = armnnTfParser::ITfParser::Create();
    armnn::INetworkPtr
        network = parser->CreateNetworkFromBinaryFile(modelFile.c_str(),
                                         { {modelInputLayer.c_str(), {1, 784, 1, 1}} },
                                         { modelOutputLayer.c_str() });
    armnnTfParser::BindingPointInfo
        inputBindingInfo = parser->GetNetworkInputBindingInfo(modelInputLayer.c_str());
    armnnTfParser::BindingPointInfo
        outputBindingInfo = parser->GetNetworkOutputBindingInfo(modelOutputLayer.c_str());
    armnn::IRuntime::CreationOptions options;
    armnn::IRuntimePtr runtime = armnn::IRuntime::Create(options);
    armnn::IOptimizedNetworkPtr optNet = Optimize(*network, {armnn::Compute::CpuRef},
                                                    runtime->GetDeviceSpec());
    armnn::NetworkId networkIdentifier;
    runtime->LoadNetwork(networkIdentifier, std::move(optNet));

    std::string dataFile = argv[4];
    float input[g_kMnistImageByteSize];
    float output[10];
    
    std::unique_ptr<MnistImage> imgInfo = loadMnistImage(dataFile);
    if (imgInfo == nullptr) {
        return EXIT_FAILURE;
    }

    std::memcpy(input, imgInfo->image, sizeof(imgInfo->image));
    armnn::InputTensors inputTensor = MakeInputTensors(inputBindingInfo, &input[0]);
    armnn::OutputTensors outputTensor = MakeOutputTensors(outputBindingInfo, &output[0]);
    runtime->EnqueueWorkload(networkIdentifier, inputTensor, outputTensor);

    float max = output[0];
    for (int j = 0; j < 10; ++j) {
      std::cerr << output[j] << " ";
      if (output[j] > max) {
         max = output[j];
      }
    }
    std::cerr << std::endl;
    return EXIT_SUCCESS;
}
