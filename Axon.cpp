#include "Axon.hpp"
#include <algorithm>
#include <stdexcept>

Axon::Axon(std::shared_ptr<InputNeuron> inputNeuron): inputNeuron(inputNeuron){
}

bool Axon::isConnected(std::shared_ptr<Dendrite> dendrite) const{
	for(const auto currentDendrite : dendrites){
		if(currentDendrite->compareOutputs(dendrite))
			return true;
	}

	return false;
}

void Axon::addConnection(std::shared_ptr<Dendrite> dendrite){
	if(this->isConnected(dendrite))
		throw std::runtime_error("Axon is already connected to this dendrite");

	this->dendrites.push_back(dendrite);
}

void Axon::sendSignal(const double value){
	for(const auto dendrite : dendrites)
		dendrite->resendSignal(value);
}

std::shared_ptr<InputNeuron> Axon::getInputNeuron() const{
	return this->inputNeuron;
}
