#ifndef OUTPUTNEURON_HPP
#define OUTPUTNEURON_HPP

#include "Neuron.hpp"
#include "Dendrite.hpp"
#include <vector>
#include <memory>

class Dendrite;

class OutputNeuron : virtual public Neuron{
protected:
	std::vector<std::shared_ptr<Dendrite>> inputDendrites;

	double calcError(const double model);

public:
	OutputNeuron(const double weight);
	virtual ~OutputNeuron();

	void addDendrite(std::shared_ptr<Dendrite> dendrite);
	void receiveSignal(const double value);
	double getSignal() const;

	void sendError(const double model);

	friend class NeuralNetwork;
};

#endif // OUTPUTNEURON_HPP
