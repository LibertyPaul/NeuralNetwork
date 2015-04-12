#ifndef NEURON_HPP
#define NEURON_HPP

#include <string>

class Neuron{
protected:
	static constexpr double teachingSpeed = 1;
	double currentSum;
	double weight;

public:
	Neuron(const double weight);
	virtual ~Neuron();

	void reset();
	void recieveSignal(const double value);
	double calcSignal() const;
	double calcDerivativeSignal() const;

	std::string toString() const;
};

#endif // NEURON_HPP
