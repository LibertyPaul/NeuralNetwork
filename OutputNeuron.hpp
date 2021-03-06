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

public:
	OutputNeuron(const long double weight);
	virtual ~OutputNeuron();

	void addDendrite(std::shared_ptr<Dendrite> dendrite);
	void receiveSignal(const long double value);
	long double getSignal() const;

	void sendError(const long double model);//из выходного слоя
	void sendError();//из скрытых слоев

	friend class NeuralNetwork;
};

#endif // OUTPUTNEURON_HPP
