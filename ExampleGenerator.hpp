#ifndef EXMPLEGENERATOR_HPP
#define EXMPLEGENERATOR_HPP

#include <random>
#include <utility>
#include <vector>


class ExampleGenerator{
	double lowerBound, upperBound;
	mutable std::default_random_engine generator;
	mutable std::uniform_real_distribution<double> valueDistribution;
	size_t inputSize, modelSize;

	std::vector<long double> generateInput() const;
	std::vector<long double> calcModel(const std::vector<long double> &input) const;
public:
	ExampleGenerator(const size_t inputSize, const size_t modelSize);
	~ExampleGenerator();

	std::pair<std::vector<long double>, std::vector<long double>> getExample() const;

	long double calcAcceptableMSE() const;
};

#endif // EXMPLEGENERATOR_HPP
