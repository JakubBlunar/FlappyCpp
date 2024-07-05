#include "Bird.h"
#include "Config.h"

Bird::Bird(const std::vector<int>& layer_sizes): network(layer_sizes)
{
	reset();
}

void Bird::update(float deltaTime)
{
	if (dead) return;

	score += deltaTime * 10;

	velocityY += Gravity * deltaTime;
	
	position.top += velocityY;
	
	image.setPosition(position.getPosition());

	if (score > MaxScore) {
		dead = true;
	}
}

void Bird::jump()
{
	velocityY = JumpVelocity;
}

void Bird::reset()
{
	score = 0;
	dead = false;
	velocityY = 0;

	position.width = 32;
	position.height = 24;
	position.left = 100;
	position.top = 200;

	image.setSize(position.getSize());
	image.setFillColor(sf::Color::Yellow);
}