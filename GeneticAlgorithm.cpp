#include "GeneticAlgorithm.h"
#include <execution>
#include <stdlib.h> 
#include "Config.h"

Bird uniformCrossover(RandomGenerator& random, Bird& parent1, Bird& parent2) {
	Bird offspring = parent1;

	std::vector<MatrixXf> offspringWeights = offspring.network.getWeights();
	std::vector<MatrixXf> parent1Weights = parent1.network.getWeights();
	std::vector<MatrixXf> parent2Weights = parent2.network.getWeights();

	for (size_t i = 0; i < parent1Weights.size(); ++i) {
		for (int r = 0; r < parent1Weights[i].rows(); ++r) {
			for (int c = 0; c < parent1Weights[i].cols(); ++c) {
				if (random.generateUniform(0, 1) > 0.5) {
					offspringWeights[i](r, c) = parent2Weights[i](r, c);
				}
			}
		}
	}
	offspring.network.setWeights(offspringWeights);
	return offspring;
}

GeneticAlgorithm::GeneticAlgorithm(const std::vector<int>& layer_sizes)
{
	this->layer_sizes = layer_sizes;
	populationNumber = 1;

	for (auto i = 1; i < PopulationSize; i++) {
		population.push_back(Bird(layer_sizes));

	}
}

void GeneticAlgorithm::evolve()
{
	std::vector<Bird> new_population;
	
	system("cls");

	std::cout << "Population " << populationNumber << std::endl;
	for (int i = 0; i < EliteCount; ++i) {
		std::cout << "Best bird " << i + 1 << ":  " << population[i].score << std::endl;
		population[i].reset();
		new_population.push_back(population[i]);
	}

	// Generate offspring using crossover and mutation
	while (new_population.size() < PopulationSize) {
		Bird parent1 = selectParent();
		Bird parent2 = selectParent();
		Bird offspring = uniformCrossover(random, parent1, parent2);
		mutate(offspring);

		offspring.reset();
		new_population.push_back(offspring);
	}

	population = new_population;
	populationNumber++;
}

void GeneticAlgorithm::sortPopulationByScore()
{
	sort(population.begin(), population.end(), [](const Bird& a, const Bird& b) {
		return a.score > b.score;
	});
}

Bird& GeneticAlgorithm::selectParent()
{
	float sum = std::accumulate(population.begin(), population.end(), 0,
		[](int i, const Bird& o) { return i + o.score; });

	float point = random.generateUniform(0, sum);

	int index = 0;
	float accumulator = population[0].score;
	while (accumulator < point) {
		index++;
		accumulator += population[index].score;
	}

	return population[index];
}

void GeneticAlgorithm::mutate(Bird& bird)
{
	std::vector<MatrixXf> offspringWeights = bird.network.getWeights();
	for (auto& weight : offspringWeights) {
		weight = weight.array() + random.generateNormal(0, 0.1);
	}
	bird.network.setWeights(offspringWeights);
}
