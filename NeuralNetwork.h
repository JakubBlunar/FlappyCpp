#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP

#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

class NeuralNetwork {
public:
    NeuralNetwork(const vector<int>& layer_sizes);

    // Method to set custom weights for all layers
    void setWeights(const vector<MatrixXd>& custom_weights);
    vector<MatrixXd>* getWeights();
   
    MatrixXd forward(const MatrixXd& X, const string& activation = "relu");

    void printWeights();

private:
    vector<MatrixXd> weights; // Weights for each layer
};

#endif