#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <iomanip>
#include <execution>
#include <algorithm>

#include "NeuralNetwork.h"
#include "NeuralNetworkHelpers.h"
#include "Game.h"
#include "RandomGenerator.h"
#include "GeneticAlgorithm.h"
#include "Config.h"

const std::string roundFloat(const float input, const int decimal_places)
{
	ostringstream str;
	str << fixed << setprecision(decimal_places);
	str << input;
	return str.str();
}

int getClosestPipe(Game* g, Bird* b) {
	int index = 0;
	while (index < g->pipes.size() && g->pipes[index]->getPosition().x + g->pipes[index]->getSize().x < b->position.left) {
		index++;
	}
	return index;
}

void decideBird(Game* game, Bird* bird) {
	int pipeIndex = getClosestPipe(game, bird);
	sf::RectangleShape* nearestPipeTop = game->pipes[pipeIndex];
	sf::RectangleShape* nearestPipeBottom = game->pipes[pipeIndex + 1];

	MatrixXf params(NeuralNetworkShape.front(), 1);
	float nearestPipeX = nearestPipeTop->getPosition().x - bird->position.left;
	float nearestPipeTopY = nearestPipeTop->getSize().y;
	float nearestPipeBottomY = nearestPipeBottom->getPosition().y;

	float nextNearestPipeX = pipeIndex + 2 < game->pipes.size() ? game->pipes[pipeIndex + 2]->getPosition().x - bird->position.left : 0;
	nextNearestPipeX = nextNearestPipeX / game->windowSize.x;
	float nextNearestPipeTop = pipeIndex + 2 < game->pipes.size() ? game->pipes[pipeIndex + 2]->getSize().y : 0;
	nextNearestPipeTop = nextNearestPipeTop / game->windowSize.y;
	float nextNearestPipeBottom = pipeIndex + 2 < game->pipes.size() ? game->pipes[pipeIndex + 3]->getPosition().y : 0;
	nextNearestPipeBottom = nextNearestPipeBottom / game->windowSize.y;

	params << bird->position.top, bird->velocityY, nearestPipeX, nearestPipeTopY, nearestPipeBottomY, nextNearestPipeX, nextNearestPipeTop, nextNearestPipeBottom;


	MatrixXf result = bird->network.forward(params, "relu");
	float result1 = result.coeff(0, 0);
	float result2 = result.coeff(1, 0);

	if (result1 > result2) {
		bird->jump();
	}
}

void runGameInWindow(const std::vector<MatrixXf>& custom_weights) {
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Vector2i windowSize(800, 600);

	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setPosition(sf::Vector2f(20, 20));

	Bird* b = new Bird(NeuralNetworkShape);

	if (custom_weights.empty() == false) {
		b->network.setWeights(custom_weights);
	}

	Game game(windowSize);
	game.addBird(b);

	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "");
	window.setVerticalSyncEnabled(true);

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				else {
					game.handleKeyPressed(event.key.code);
				}
			}
		}

		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			if (custom_weights.empty() == false) {
				decideBird(&game, b);
			}

			game.update(TimePerFrame.asSeconds());
		}


		window.clear();

		for (auto bird : game.birds)
		{
			if (bird->dead == true) continue;
			window.draw(bird->image);
		}

		for (auto pipe : game.pipes)
		{
			window.draw(*pipe);
		}

		scoreText.setString(roundFloat(game.birds.front()->score, 0));
		window.draw(scoreText);

		window.display();
	}

}

void trainGame() {
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Vector2i windowSize(800, 600);

	Game* game = new Game(windowSize);
	GeneticAlgorithm genetic(NeuralNetworkShape);

	for (int i = 0; i < genetic.population.size(); i++) {
		game->addBird(&genetic.population[i]);
	}

	bool end = false;

	while (end == false) {
		for (auto bird : game->birds)
		{
			if (bird->dead) continue;
			decideBird(game, bird);
		}

		if (game->end == true) {

			genetic.sortPopulationByScore();

			if (genetic.population[0].score > MaxScore || genetic.populationNumber > 10000) {
				end = true;
				break;
			}

			genetic.evolve();
			delete game;

			game = new Game(windowSize);

			for (int i = 0; i < genetic.population.size(); i++) {
				game->addBird(&genetic.population[i]);
			}
		}
		else {
			game->update(TimePerFrame.asSeconds());
		}
	}

	cout << "Best bird generation " << genetic.populationNumber << "score: " << genetic.population[0].score << endl;
	NeuralNetworkHelpers::saveWeights(genetic.population[0].network.getWeights(), "bestBird.txt");
}


int main()
{
	// Run game normally
	runGameInWindow({});

	// Train game
	/*trainGame();
	vector<MatrixXf> loaded_weights = NeuralNetworkHelpers::loadWeights("bestBird.txt");
	runGameInWindow(loaded_weights);*/
		
	// Run trained game
	/*vector<MatrixXf> loaded_weights = NeuralNetworkHelpers::loadWeights("bestBird.txt");
	runGameInWindow(loaded_weights);*/

	return 0;
}