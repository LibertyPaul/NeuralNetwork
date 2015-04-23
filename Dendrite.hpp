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
	long double multiplier;


public:
	Dendrite(std::shared_ptr<OutputNeuron> outputNeuron, std::shared_ptr<Axon> axon, const long double multiplier);
	void resendSignal(const long double value);
	void resendError(const long double error, const long double teachingSpeed);

	bool compareOutputs(std::shared_ptr<Dendrite> dendrite) const;


	friend class NeuralNetwork;
};

#endif // DENDRITE_HPP
