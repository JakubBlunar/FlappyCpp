#include "Game.h"
#include <execution>
#include <algorithm>
#include "Config.h"

Game::Game(sf::Vector2i windowSize)
{
	this->windowSize = windowSize;
	end = false;
	pipeTimer = 0;

	createPipe();
}

Game::Game(sf::Vector2i windowSize, unsigned int seed) : randomGenerator(seed)
{
	this->windowSize = windowSize;
	end = false;
	pipeTimer = 0;

	createPipe();
}

Game::~Game()
{
	while (pipes.size() > 0) {
		sf::RectangleShape* pipeToDelete = pipes.front();
		pipes.erase(pipes.begin());
		delete pipeToDelete;
	}
}

void Game::update(float deltaTime)
{
	if (end == true) return;

	std::for_each(std::execution::par_unseq,
		birds.begin(),
		birds.end(), [deltaTime](Bird* bird) {
			bird->update(deltaTime);
		});

	std::for_each(std::execution::par_unseq,
		pipes.begin(),
		pipes.end(), [deltaTime](sf::RectangleShape* pipe) {
			auto position = pipe->getPosition();
			pipe->setPosition(position.x -= PipeSpeed * deltaTime, position.y);
		});

	pipeTimer -= deltaTime;
	if (pipeTimer <= 0) {
		createPipe();
	}

	while (pipes.front()->getPosition().x < -PipeWidth) {
		sf::RectangleShape* pipeToDelete = pipes.front();
		pipes.erase(pipes.begin());
		delete pipeToDelete;
	}


	bool allDead = true;

	for (auto bird : birds) {
		if (bird->position.top < 0 || bird->position.top > windowSize.y) {
			bird->dead = true;
		}

		for (auto pipe : pipes) {
			if (bird->position.intersects(pipe->getGlobalBounds())) {
				bird->dead = true;
			}
		}

		if (bird->dead == false) {
			allDead = false;
		}
	}

	if (allDead) {
		end = true;
	}
}

void Game::addBird(Bird* bird)
{
	birds.push_back(bird);
}

void Game::handleKeyPressed(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Up) {
		for (auto bird : birds) {
			bird->jump();
		}
	}
}

void Game::createPipe()
{
	sf::RectangleShape* topPipe = new sf::RectangleShape();
	sf::RectangleShape* bottomPipe = new sf::RectangleShape();
	topPipe->setFillColor(sf::Color::Green);
	bottomPipe->setFillColor(sf::Color::Red);

	int pipeHeight = randomGenerator.generateUniformInt(50, windowSize.y - PipeSpace - 50);

	topPipe->setPosition(windowSize.x, 0);
	topPipe->setSize(sf::Vector2f(PipeWidth, pipeHeight));

	bottomPipe->setPosition(windowSize.x, pipeHeight + PipeSpace);
	bottomPipe->setSize(sf::Vector2f(PipeWidth, windowSize.y - pipeHeight + PipeSpace));

	pipes.push_back(topPipe);
	pipes.push_back(bottomPipe);

	pipeTimer = PipeDelay;
}

