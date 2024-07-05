#include "NeuralNetwork.h"
#include <functional>

MatrixXf relu(const MatrixXf& x) {
    return x.cwiseMax(0);
}

MatrixXf sigmoid(const MatrixXf& x) {
    return 1.0 / (1.0 + (-x.array()).exp());
}

MatrixXf tanh(const MatrixXf& x) {
    return x.array().tanh();
}

MatrixXf softmax(const MatrixXf& x) {
    MatrixXf exps = (x.array() - x.maxCoeff()).exp();
    return exps / exps.sum();
}

MatrixXf leakyRelu(const MatrixXf& x, float alpha = 0.01) {
    return x.cwiseMax(alpha * x);
}

NeuralNetwork::NeuralNetwork(const std::vector<int>& layer_sizes)
{
	for (size_t i = 1; i < layer_sizes.size(); ++i) {
		weights.push_back(MatrixXf::Random(layer_sizes[i], layer_sizes[i - 1]));
	}
}

void NeuralNetwork::setWeights(const std::vector<MatrixXf>& custom_weights)
{
	weights = custom_weights;
}

std::vector<MatrixXf> NeuralNetwork::getWeights()
{
    return weights;
}

MatrixXf NeuralNetwork::forward(const MatrixXf& X, const std::string& activation)
{
    MatrixXf A = X;
    for (size_t i = 0; i < weights.size(); ++i) {
        MatrixXf Z = weights[i] * A;
        if (activation == "relu") {
            A = relu(Z);
        }
        else if (activation == "sigmoid") {
            A = sigmoid(Z);
        }
        else {
            throw std::invalid_argument("Unsupported activation function");
        }
    }
    return A;
}

void NeuralNetwork::printWeights()
{
    for (size_t i = 0; i < weights.size(); ++i) {
        std::cout << "Weights of layer " << i + 1 << ":\n" << weights[i] << std::endl;
    }
}
