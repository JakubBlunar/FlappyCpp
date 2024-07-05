// Helper function to save weights to a file
#include "NeuralNetworkHelpers.h"

void NeuralNetworkHelpers::saveWeights(const vector<MatrixXf>& weights, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& weight : weights) {
            file << weight.rows() << " " << weight.cols() << endl;
            file << weight << endl;
        }
        file.close();
        cout << "Weights saved to " << filename << endl;
    }
    else {
        cerr << "Unable to open file for saving weights." << endl;
    }
}

vector<MatrixXf> NeuralNetworkHelpers::loadWeights(const string& filename)
{
    ifstream file(filename);
    vector<MatrixXf> weights;
    if (file.is_open()) {
        int rows, cols;
        while (file >> rows >> cols) {
            MatrixXf weight(rows, cols);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    file >> weight(i, j);
                }
            }
            weights.push_back(weight);
        }
        file.close();
        cout << "Weights loaded from " << filename << endl;
    }
    else {
        cerr << "Unable to open file for loading weights." << endl;
    }
    return weights;
}
