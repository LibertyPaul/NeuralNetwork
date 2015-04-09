#ifndef INPUTNEURON_HPP
#define INPUTNEURON_HPP

#include <memory>
#include "Neuron.hpp"
#include "NeuralNetwork.hpp"

class Axon;

class InputNeuron : virtual protected Neuron{
protected:
	std::shared_ptr<Axon> axon;
public:
	InputNeuron(const double weight);

	friend class NeuralNetwork;
};

#endif // INPUTNEURON_HPP
