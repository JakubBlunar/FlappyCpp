#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP

#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace Eigen;

class NeuralNetwork {
public:
    NeuralNetwork(const std::vector<int>& layer_sizes);
    void setWeights(const std::vector<MatrixXf>& custom_weights);
    std::vector<MatrixXf> getWeights();
    MatrixXf forward(const MatrixXf& X, const std::string& activation = "relu");
    void printWeights();
private:
    std::vector<MatrixXf> weights; // Weights for each layer
};

#endif