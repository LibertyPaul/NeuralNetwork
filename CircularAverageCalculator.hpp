#ifndef CIRCULARAVERAGECALCULATOR_HPP
#define CIRCULARAVERAGECALCULATOR_HPP

#include <vector>

class CircularAverageCalculator{
	std::vector<long double> buffer;
	std::vector<long double>::iterator oldestValue;
	std::size_t size;

public:
	CircularAverageCalculator(const std::size_t size);
	~CircularAverageCalculator();

	void pushValue(const long double value);
	bool isFull() const;
	long double calcAverage() const;
};

#endif // CIRCULARAVERAGECALCULATOR_HPP
