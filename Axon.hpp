#ifndef AXON_HPP
#define AXON_HPP

#include <vector>
#include <memory>

#include "Dendrite.hpp"
#include "InputNeuron.hpp"

class Dendrite;
class InputNeuron;

class Axon{
protected:
	std::vector<std::shared_ptr<Dendrite>> dendrites;
	std::shared_ptr<InputNeuron> inputNeuron;

	bool isConnected(std::shared_ptr<Dendrite> dendrite) const;
public:
	Axon(std::shared_ptr<InputNeuron> inputNeuron);
	void sendSignal(const double value);
	void addConnection(std::shared_ptr<Dendrite> dendrite);
	std::shared_ptr<InputNeuron> getInputNeuron() const;


	friend class NeuralNetwork;
};

#endif // AXON_HPP
