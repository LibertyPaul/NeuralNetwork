#ifndef EXMPLEGENERATOR_HPP
#define EXMPLEGENERATOR_HPP

#include <random>
#include <utility>
#include <vector>


class ExampleGenerator{
	mutable std::default_random_engine generator;
	mutable std::uniform_real_distribution<double> valueDistribution;

	size_t inputSize, modelSize;
public:
	ExampleGenerator(const size_t inputSize, const size_t modelSize);
	~ExampleGenerator();

	std::pair<std::vector<double>, std::vector<double>> getExample() const;
};

#endif // EXMPLEGENERATOR_HPP
