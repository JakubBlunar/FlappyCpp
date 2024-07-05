#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <vector>

const int Gravity = 20;
const float JumpVelocity = -7;
const float PipeSpeed = 200;
const int PipeSpace = 160;
const float PipeDelay = 1.6;
const int PipeWidth = 80;

const std::vector<int> NeuralNetworkShape = { 8, 9, 9, 2 };
const float PopulationSize = 20;
const int EliteCount = 4;
const float MaxScore = 400000;

#endif