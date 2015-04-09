#include "OutputNeuron.hpp"

OutputNeuron::OutputNeuron(const double weight): Neuron(weight){
}

OutputNeuron::~OutputNeuron(){
}

void OutputNeuron::addDendrite(std::shared_ptr<Dendrite> dendrite){
	inputDendrites.push_back(dendrite);
}

void OutputNeuron::receiveSignal(const double value){
	this->currentSum += value;
}
