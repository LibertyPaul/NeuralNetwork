#ifndef INPUTNEURON_HPP
#define INPUTNEURON_HPP

#include <memory>
#include "Neuron.hpp"
#include "NeuralNetwork.hpp"

class Axon;

class InputNeuron : virtual public Neuron{
protected:
	std::shared_ptr<Axon> axon;

public:
	InputNeuron(const double weight);
	void initialize(const double value);

	void sendSignal();
	void sendRawSignal();//костыль для 1-го уровня
	void getOffsetCorrection(const double offsetCorrection);

	friend class NeuralNetwork;
};

#endif // INPUTNEURON_HPP
