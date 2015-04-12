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
	double error = (model - this->currentSum) * this->calcDerivativeSignal();

	double offsetCorrection = this->teachingSpeed * error;
	for(auto dendrite : this->inputDendrites){
		std::shared_ptr<InputNeuron> currentInputNeuron = dendrite->getInputNeuron();
		currentInputNeuron->getOffsetCorrection(offsetCorrection);

		double diff = offsetCorrection * currentInputNeuron->calcSignal();
		dendrite->adjustMultiplier(diff);
	}
}
