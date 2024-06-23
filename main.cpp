#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <iostream>
#include "NeuralNetwork.h"
#include "NeuralNetworkHelpers.h"

void runGameInWindow() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

int main()
{   
    vector<int> layer_sizes = { 3, 4, 5, 2 };
    MatrixXd X(3, 1);
    X << 1.0, 2.0, 3.0;

    NeuralNetwork nn(layer_sizes);

    vector<MatrixXd> custom_weights;
    custom_weights.push_back((MatrixXd(4, 3) << 0.1, 0.2, 0.3,
        0.4, 0.5, 0.6,
        0.7, 0.8, 0.9,
        1.0, 1.1, 1.2).finished());

    custom_weights.push_back((MatrixXd(5, 4) << 0.1, 0.2, 0.3, 0.4,
        0.5, 0.6, 0.7, 0.8,
        0.9, 1.0, 1.1, 1.2,
        1.3, 1.4, 1.5, 1.6,
        1.7, 1.8, 1.9, 2.0).finished());

    custom_weights.push_back((MatrixXd(2, 5) << 0.1, 0.2, 0.3, 0.4, 0.5,
        0.6, 0.7, 0.8, 0.9, 1.0).finished());

    nn.setWeights(custom_weights);
    nn.printWeights();

    NeuralNetworkHelpers::saveWeights(custom_weights, "weights.txt");
    vector<MatrixXd> loaded_weights = NeuralNetworkHelpers::loadWeights("weights.txt");

    NeuralNetwork nn_loaded(layer_sizes);
    nn_loaded.setWeights(loaded_weights);

    nn_loaded.printWeights();


    MatrixXd output1 = nn.forward(X, "sigmoid");
    MatrixXd output2 = nn_loaded.forward(X, "sigmoid");

    cout << "Output with initial weights:\n" << output1 << endl;
    cout << "Output with loaded weights:\n" << output2 << endl;

    return 0;
}