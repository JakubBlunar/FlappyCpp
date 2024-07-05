
#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "SFML/Graphics.hpp"
#include "Bird.h"
#include "RandomGenerator.h"

class Game
{
public:
	Game(sf::Vector2i windowSize);
	Game(sf::Vector2i windowSize, unsigned int seed);

	~Game();

	sf::Vector2i windowSize;
	bool end;
	float pipeTimer;

	void update(float deltaTime);
	void addBird(Bird* bird);
	void handleKeyPressed(sf::Keyboard::Key key);
	void createPipe();

	std::vector<Bird*> birds;
	std::vector<sf::RectangleShape*> pipes;

	RandomGenerator randomGenerator;
};

#endif

