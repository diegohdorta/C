/* Copyright (c) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier: GLP3
 */
#ifndef IMX_ROBIN_NN_
#define IMX_ROBIN_NN_

#include <vector>
#include <fstream>
#include <cmath>
#include <time.h>
#include <stdlib.h>

#include "calc-matrix.h"

class RobinNN
{
public:
    RobinNN(std::vector<int> neurons, double learningRate);
    RobinNN(const char *filepath);

    Matrix<double> computeOutput(std::vector<double> input);
    void learn(std::vector<double> expectedOutput);

    void saveRobinNNParams(const char *filepath);
    void loadRobinNNParams(const char *filepath);

    std::vector<Matrix<double> > W;
    std::vector<Matrix<double> > B;
    
private:
    std::vector<Matrix<double> > H;
    std::vector<Matrix<double> > dEdW;
    std::vector<Matrix<double> > dEdB;

    Matrix<double> Y;

    int hiddenLayersCount;
    double learningRate;

    static double random(double x);
    static double sigmoid(double x);
    static double sigmoidePrime(double x);

    void printToFile(Matrix<double> &m, std::ofstream &file);
};

#endif /* IMX_ROBIN_NN_ */
