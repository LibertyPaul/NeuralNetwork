#ifndef DENDRITE_HPP
#define DENDRITE_HPP

#include "OutputNeuron.hpp"
#include "Axon.hpp"
#include "NeuralNetwork.hpp"
#include <memory>

class Axon;
class OutputNeuron;

class Dendrite{
protected:
	std::shared_ptr<OutputNeuron> outputNeuron;
	std::shared_ptr<Axon> axon;
	double multiplier;

public:
	Dendrite(std::shared_ptr<OutputNeuron> outputNeuron, std::shared_ptr<Axon> axon, const double multiplier);
	void resendSignal(const double value);
	std::shared_ptr<InputNeuron> getInputNeuron() const;
	void adjustMultiplier(const double diff);

	bool compareOutputs(std::shared_ptr<Dendrite> dendrite) const;


	friend class NeuralNetwork;
};

#endif // DENDRITE_HPP
