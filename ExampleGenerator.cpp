#include "ExampleGenerator.hpp"
#include <chrono>

ExampleGenerator::ExampleGenerator(const size_t size):
	generator(std::chrono::system_clock::now().time_since_epoch().count()),
	valueDistribution(-10, 10),
	size(size)
{

}

ExampleGenerator::~ExampleGenerator()
{

}

std::pair<std::vector<double>, std::vector<double>> ExampleGenerator::getExample() const{
	std::vector<double> input(size);
	std::vector<double> model(size);

	for(size_t i = 0; i < size; ++i){
		input.at(i) = valueDistribution(generator);
		model.at(i) = input.at(i) * 2;
	}

	return std::make_pair(input, model);
}
