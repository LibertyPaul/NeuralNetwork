#include "ExampleGenerator.hpp"
#include <chrono>
#include <cmath>
#include <stdexcept>

ExampleGenerator::ExampleGenerator(const size_t inputSize, const size_t modelSize):
	lowerBound(-M_PI),
	upperBound(M_PI),
	generator(std::chrono::system_clock::now().time_since_epoch().count()),
	valueDistribution(-M_PI, M_PI),
	inputSize(inputSize),
	modelSize(modelSize)
{

}

ExampleGenerator::~ExampleGenerator()
{

}

std::vector<long double> ExampleGenerator::generateInput() const{
	std::vector<long double> input(inputSize);
	for(auto &value : input)
		value = valueDistribution(generator);
	return input;
}

std::vector<long double> ExampleGenerator::calcModel(const std::vector<long double> &input) const{
	std::vector<long double> model(modelSize);
	if(model.size() != input.size())
		throw std::runtime_error("incorrect model size");

	for(size_t i = 0; i < modelSize; ++i)
		model.at(i) = std::sin(input.at(i));

	return model;
}

std::pair<std::vector<long double>, std::vector<long double>> ExampleGenerator::getExample() const{
	std::vector<long double> input = generateInput();
	std::vector<long double> model = calcModel(input);
	return std::make_pair(input, model);
}

long double ExampleGenerator::calcAcceptableMSE() const{
	long double result = 0.0001 * std::pow(std::abs(upperBound) + std::abs(lowerBound), 2);
	return result;
}
