#include "NeuralNetwork.h"
#include <functional>

MatrixXd relu(const MatrixXd& x) {
    return x.cwiseMax(0);
}

MatrixXd sigmoid(const MatrixXd& x) {
    return 1.0 / (1.0 + (-x.array()).exp());
}

MatrixXd tanh(const MatrixXd& x) {
    return x.array().tanh();
}

MatrixXd softmax(const MatrixXd& x) {
    MatrixXd exps = (x.array() - x.maxCoeff()).exp();
    return exps / exps.sum();
}

MatrixXd leakyRelu(const MatrixXd& x, float alpha = 0.01) {
    return x.cwiseMax(alpha * x);
}

NeuralNetwork::NeuralNetwork(const vector<int>& layer_sizes)
{
	for (size_t i = 1; i < layer_sizes.size(); ++i) {
		weights.push_back(MatrixXd::Random(layer_sizes[i], layer_sizes[i - 1]));
	}
}

void NeuralNetwork::setWeights(const vector<MatrixXd>& custom_weights)
{
	weights = custom_weights;
}

MatrixXd NeuralNetwork::forward(const MatrixXd& X, const string& activation)
{
    MatrixXd A = X;
    for (size_t i = 0; i < weights.size(); ++i) {
        MatrixXd Z = weights[i] * A;
        if (activation == "relu") {
            A = relu(Z);
        }
        else if (activation == "sigmoid") {
            A = sigmoid(Z);
        }
        else {
            throw invalid_argument("Unsupported activation function");
        }
    }
    return A;
}

void NeuralNetwork::printWeights()
{
    for (size_t i = 0; i < weights.size(); ++i) {
        cout << "Weights of layer " << i + 1 << ":\n" << weights[i] << endl;
    }
}
