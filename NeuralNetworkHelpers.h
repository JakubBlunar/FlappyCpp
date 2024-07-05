#ifndef NEURAL_NETWORK_HELPERS_HPP
#define NEURAL_NETWORK_HELPERS_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

class NeuralNetworkHelpers
{
    public:
        static void saveWeights(const vector<MatrixXf>& weights, const string& filename);
        static vector<MatrixXf> loadWeights(const string& filename);
};

#endif