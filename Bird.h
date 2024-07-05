#ifndef BIRD_HPP
#define BIRD_HPP

#include <vector>
#include "SFML/Graphics.hpp"
#include "NeuralNetwork.h"

class Bird
{
public:
	Bird(const std::vector<int>& layer_sizes);
	sf::RectangleShape image;
	NeuralNetwork network;
	float score;
	float velocityY;
	bool dead;

	sf::FloatRect position;

	void update(float deltaTime);
	void jump();

	void reset();
};

#endif

