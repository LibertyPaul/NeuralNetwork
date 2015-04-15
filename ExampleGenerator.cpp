#include "ExampleGenerator.hpp"
#include <chrono>

ExampleGenerator::ExampleGenerator(const size_t inputSize, const size_t modelSize):
	generator(std::chrono::system_clock::now().time_since_epoch().count()),
	valueDistribution(-0.5, 0.5),
	inputSize(inputSize),
	modelSize(modelSize)
{

}

ExampleGenerator::~ExampleGenerator()
{

}

std::pair<std::vector<double>, std::vector<double>> ExampleGenerator::getExample() const{
	std::vector<double> input(inputSize);
	std::vector<double> model(modelSize);

	model.at(0) = 0;
	for(size_t i = 0; i < inputSize; ++i){
		input.at(i) = valueDistribution(generator);
		model.at(0) += input.at(i) * 2;
	}

	return std::make_pair(input, model);
}
