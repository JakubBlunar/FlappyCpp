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
        static void saveWeights(const vector<MatrixXd>& weights, const string& filename);
        static vector<MatrixXd> loadWeights(const string& filename);
};

#endif