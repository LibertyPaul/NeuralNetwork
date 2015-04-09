#include "InputNeuron.hpp"
#include "Axon.hpp"

InputNeuron::InputNeuron(const double weight):
	Neuron(weight), axon(new Axon(std::shared_ptr<InputNeuron>(this))){
}
