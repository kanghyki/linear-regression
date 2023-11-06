#ifndef TRAINING_HPP
#define TRAINING_HPP

#include "../inc/util.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <utility>

double hypothesis(double weight, double bias, double data);
double loss_fn(std::vector<std::pair<int, int>>& data, double weight, double bias);
double pd_weight(std::vector<std::pair<int, int>>& data, double weight, double bias);
double pd_bias(std::vector<std::pair<int, int>>& data, double weight, double bias);
std::pair<double, double> gradient_descent(std::vector<std::pair<int, int>>& data, double learning_rate, int epoch);

#endif
