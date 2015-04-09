#ifndef NEURON_HPP
#define NEURON_HPP


class Neuron{
protected:
	double currentSum;
	double weight;

public:
	Neuron(const double weight);
	virtual ~Neuron();

	void reset();
	void recieveSignal(const double value);
	double calcSignal() const;
	double calcDerivativeSignal() const;

};

#endif // NEURON_HPP
