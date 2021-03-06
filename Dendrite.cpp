#include "Dendrite.hpp"
#include <stdexcept>


Dendrite::Dendrite(std::shared_ptr<OutputNeuron> outputNeuron, std::shared_ptr<Axon> axon, const long double multiplier): multiplier(multiplier){
	if(outputNeuron == nullptr || axon == nullptr)
		throw std::runtime_error("nullptr is passed");

	this->outputNeuron = outputNeuron;
	this->axon = axon;
}

void Dendrite::resendSignal(const long double value){
	this->outputNeuron->receiveSignal(value * multiplier);
}

void Dendrite::resendError(const long double error, const long double teachingSpeed){
	long double diff = error * teachingSpeed * this->axon->getInputNeuron()->calcSignal();
	this->axon->getInputNeuron()->getOffsetCorrection(error * this->multiplier);
	this->multiplier += diff;

}

bool Dendrite::compareOutputs(std::shared_ptr<Dendrite> dendrite) const{
	return this->outputNeuron == dendrite->outputNeuron;
}
