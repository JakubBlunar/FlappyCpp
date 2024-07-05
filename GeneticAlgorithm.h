
#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include "NeuralNetwork.h"
#include "Bird.h"
#include "RandomGenerator.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(const std::vector<int>& layer_sizes);

	void evolve();
	void sortPopulationByScore();

	std::vector<int> layer_sizes;
	std::vector<Bird> population;
	int populationNumber;
private:
	RandomGenerator random;
	Bird& selectParent();
	void mutate(Bird& bird);
};

#endif