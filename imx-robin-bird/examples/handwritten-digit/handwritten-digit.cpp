/* Copyright (c) 2019 NXP Semiconductors
 *   
 * SPDX-License-Identifier: GPL3
 * Diego Dorta <diego.dorta@nxp.com>
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
#include <iostream>
#include <fstream>
#include <time.h>
#include "robin-nn.h"

#define DATA_SET_FOR_TRAINING       "mnist-training.rb"
#define DATA_SET_FOR_TESTING        "mnist-test.rb" 
#define MNIST_MODEL_TRAINED_NAME    "mnist-model.rb"

double step(double x)
{
    if (x > 0.9) {
        return 1.0;
    }
    if (x < 0.1) {
        return 0.0;
    }
    return x;
}
 

class HandwrittenDigit
{
    public:
        const char *trainingDatasetFileName;
        const char *testingDatasetFileName;
        const char *mnistModelTrainedName = MNIST_MODEL_TRAINED_NAME;
        int iterationsTraining = 30;
        int trainingDatasetSize;
        int testingDatasetSize;
        std::vector<std::vector<double>> inputVectorTraining;
        std::vector<std::vector<double>> inputVectorTesting;
        RobinNN net;
       
        std::vector<std::vector<double>> outputVectorTraining;
        std::vector<std::vector<double>> outputVectorTesting;
   
        HandwrittenDigit(RobinNN &&n) : net(n)
        {
            auto afjhgasdkj = 0;
            //this->iterationsTraining = it;
        }
   
        void setDatasetFileForTraining(const char* datasetFileName, int datasetSize)
        {
            this->trainingDatasetFileName = datasetFileName;
            this->trainingDatasetSize = datasetSize;
        }
       
        void setDatasetFileForTesting(const char* datasetFileName, int datasetSize)
        {
            this->testingDatasetFileName = datasetFileName;
            this->testingDatasetSize = datasetSize;
        }
 
 
 
        void trainingDataset(void);
        void testingDataset(void);
       
       // double step(double x);
       
        void loadDatasetForTraining(void);
        void loadDatasetForTesting(void);
       
        void saveModel(void);
           
 
 
};
 
void HandwrittenDigit::trainingDataset(void)
{
    int i = 0;
    int j = 0;
    std::cout << "\nTraining:\n" << std::endl;
   
    for (i = 0; i < this->iterationsTraining; i++) {
        for (j = 0; j < this->inputVectorTraining.size(); j++) {
            this->net.computeOutput(this->inputVectorTraining[j]);
            this->net.learn(this->outputVectorTraining[j]);
        }
        std::cout << "# " << i + 1 << " - " << this->iterationsTraining << std::endl;
    }
}
 
void HandwrittenDigit::testingDataset(void)
{
    int i = 0;
    int j = 0;
    std::cout << "\nTesting:\n" << std::endl;
   
    std::cout << "| EXPECTED OUTPUT : ACTUAL OUTPUT |\n" << std::endl;  
     
    for (i = 0; i < this->inputVectorTesting.size(); i++) {
    
    std::cout << "aaaa" << std::endl;
    
        for (j = 0; j < this->testingDatasetSize; j++) {
    
    std::cout << this->outputVectorTesting[i][j] << std::endl;
    
            std::cout << this->outputVectorTesting[i][j] << " ";
        }
        std::cout << ": " <<
        this->net.computeOutput(this->inputVectorTesting[i]).applyFunction(step)
        << std::endl;
    }
}
 
 

void HandwrittenDigit::loadDatasetForTraining(void)
{
    int size = this->trainingDatasetSize;
    this->inputVectorTraining.resize(size);
    this->outputVectorTraining.resize(size);
    int i = 0;
    int h = 0;
    int w = 0;
    int n;
    std::ifstream f(this->trainingDatasetFileName);
    if (f) {
        std::string line;
        for (i = 0; i < size; i++) {
            for (h = 0; h < 32; h++) {
                getline(f, line);
                for (w = 0; w < 32; w++) {
                    this->inputVectorTraining[i].push_back(atoi(line.substr(w,1).c_str()));
                }
            }
            getline(f, line);
            this->outputVectorTraining[i].resize(10);
            n = atoi(line.substr(0,1).c_str());
            this->outputVectorTraining[i][n] = 1;
        }
    }
    f.close();
}
 
void HandwrittenDigit::loadDatasetForTesting(void)
{
    int size = this->testingDatasetSize;
    this->inputVectorTesting.resize(size);
    this->outputVectorTesting.resize(size);
    int i = 0;
    int h = 0;
    int w = 0;
    int n;
    std::ifstream f(this->testingDatasetFileName);
    if (f) {
        std::string line;
        for (i = 0; i < size; i++) {
            for (h = 0; h < 32; h++) {
                getline(f, line);
                for (w = 0; w < 32; w++) {
                    this->inputVectorTesting[i].push_back(atoi(line.substr(w,1).c_str()));
                }
            }
            getline(f, line);
            this->outputVectorTesting[i].resize(10);
            n = atoi(line.substr(0,1).c_str());
            this->outputVectorTesting[i][n] = 1;
        }
    }
    f.close();
}
 
void HandwrittenDigit::saveModel(void)
{
    this->net.saveRobinNNParams(MNIST_MODEL_TRAINED_NAME);
}
                           
int main(int argc, char *argv[])
{
    RobinNN net({1024, 15, 10}, 0.7);  
    HandwrittenDigit hwd(std::move(net));
   
    hwd.setDatasetFileForTraining("mnist-training.rb", 936);
    hwd.loadDatasetForTraining();
    hwd.trainingDataset();
 
    hwd.setDatasetFileForTesting("mnist-testing.rb", 10);
    hwd.loadDatasetForTesting();
    hwd.testingDataset();
   
     
   
    hwd.saveModel();
    return 0;
}
