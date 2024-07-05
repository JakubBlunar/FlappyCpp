#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

class RandomGenerator {
public:
    RandomGenerator(unsigned int seed = std::random_device{}()) : engine(seed) {}


    float generateUniform(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(engine);
    }

    float generateNormal(float mean, float stddev) {
        std::normal_distribution<float> dist(mean, stddev);
        return dist(engine);
    }

    int generateUniformInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine);
    }

private:
    std::mt19937 engine; // Mersenne Twister random number engine
};

#endif