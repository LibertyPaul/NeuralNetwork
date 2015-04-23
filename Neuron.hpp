#ifndef NEURON_HPP
#define NEURON_HPP

#include <string>

class Neuron{
protected:
	static constexpr long double teachingSpeed = 0.001;
	long double currentSum;
	long double errorSum;
	long double weight;

	static long double calcSignal(const long double value);
	static long double calcDerivativeSignal(const long double value);

public:
	Neuron(const long double weight);
	virtual ~Neuron();

	void reset();
	void recieveSignal(const long double value);
	long double getCurrentValue() const;
	long double calcSignal() const;
	long double calcDerivativeSignal() const;

	std::string toString() const;
};

#endif // NEURON_HPP
