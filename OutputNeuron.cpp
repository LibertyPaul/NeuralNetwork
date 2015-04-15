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

double OutputNeuron::getSignal() const{
	return this->currentSum;
}

void OutputNeuron::sendError(const double model){
	//double error = (model - this->calcSignal()) * this->calcDerivativeSignal();
	double error = (model - this->currentSum - this->weight) * this->calcDerivativeSignal();

	for(auto dendrite : this->inputDendrites)
		dendrite->resendError(error, this->teachingSpeed);

	this->weight += this->teachingSpeed * error;
}

void OutputNeuron::sendError(){
	double error = this->errorSum * this->calcDerivativeSignal();

	for(auto dendrite : this->inputDendrites)
		dendrite->resendError(error, this->teachingSpeed);

	this->weight += this->teachingSpeed * error;
}
