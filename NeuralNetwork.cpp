#include <stdexcept>
#include <type_traits>
#include <chrono>
#include "NeuralNetwork.hpp"
#include "Axon.hpp"
#include "InputNeuron.hpp"
#include "SuperNeuron.hpp"
#include "OutputNeuron.hpp"

NeuralNetwork::NeuralNetwork(const std::vector<uint32_t> &layerSizes):
	generator(std::chrono::system_clock::now().time_since_epoch().count()),
	weightDistribution(-0.5, 0.5),
	multiplierDistribution(-0.5, 0.5){

	if(layerSizes.size() < 2)
		throw std::runtime_error("Incorrect NN size");


	//создаем нейроны

	//входной уровень
	uint32_t firstLayerSize = layerSizes.front();
	for(uint32_t i = 0; i < firstLayerSize; ++i){
		std::shared_ptr<InputNeuron> inputNeuron(new InputNeuron(this->getNeuronWeight()));
		this->inputLayer.push_back(inputNeuron);
	}
	//скрытые уровни
	hiddenNeurons.reserve(layerSizes.size() - 2);
	for(auto layerSize = layerSizes.cbegin() + 1; layerSize != layerSizes.cend() - 1; ++layerSize){
		hiddenNeurons.push_back(std::vector<std::shared_ptr<SuperNeuron>>());
		hiddenNeurons.back().reserve(*layerSize);
		for(uint32_t i = 0; i < *layerSize; ++i){
			std::shared_ptr<SuperNeuron> superNeuron(new SuperNeuron(this->getNeuronWeight()));
			hiddenNeurons.back().push_back(superNeuron);
		}
	}
	//выходной уровень
	outputLayer.reserve(layerSizes.back());
	for(uint32_t i = 0; i < layerSizes.back(); ++i){
		std::shared_ptr<OutputNeuron> outputNeuron(new OutputNeuron(this->getNeuronWeight()));
		outputLayer.push_back(outputNeuron);
	}


	//соединяем уровни между собой
	for(size_t previousLayerIndex = 0; previousLayerIndex < this->getLayerCount() - 1; ++previousLayerIndex){
		IOLayersPair layersPair = move(this->getLayersPair(previousLayerIndex));
		this->connectLayers(layersPair);
	}
}

void NeuralNetwork::initialize(const std::vector<double> &values){
	if(values.size() != this->inputLayer.size())
		throw std::runtime_error("Incorrect initialising vector size");

	this->reset();
	for(size_t i = 0; i < values.size(); ++i){
		this->inputLayer.at(i)->initialize(values.at(i));
	}
}

void NeuralNetwork::reset(){
	for(auto neuron : this->inputLayer)
		neuron->reset();

	for(auto hiddenLayer : this->hiddenNeurons)
		for(auto neuron : hiddenLayer)
			neuron->reset();

	for(auto neuron : this->outputLayer)
		neuron->reset();

}

double NeuralNetwork::calcMSE(const std::vector<double> &output, const std::vector<double> &model) const{
	if(output.size() != model.size())
		throw std::runtime_error("different vector sizes");

	double result = 0;
	for(size_t i = 0; i < model.size(); ++i){
		result += std::pow(model.at(i) - output.at(i), 2);
	}
	result /= model.size();

	return result;
}

std::vector<double> NeuralNetwork::run(const std::vector<double> &values){
	this->initialize(values);

	size_t inputLayersCount = this->getLayerCount() - 1;

	for(size_t i = 0; i < inputLayersCount; ++i)
		for(auto inputNeuron : this->getInputLayer(i))
			inputNeuron->sendSignal();

	std::vector<double> result;
	result.reserve(this->outputLayer.size());

	for(const auto outputNeuron : this->outputLayer)
		result.push_back(outputNeuron->calcSignal());

	return result;
}


double NeuralNetwork::teach(const std::vector<double> &input, const std::vector<double> &model){
	std::vector<double> output = this->run(input);

	//тут обратное распространение ошибки
	//
	//



	return this->calcMSE(output, model);
}



double NeuralNetwork::getDendriteMultiplier() const{
	return multiplierDistribution(generator);
}

double NeuralNetwork::getNeuronWeight() const{
	return weightDistribution(generator);
}

void NeuralNetwork::connectLayers(const IOLayersPair &layersPair) const{
	for(auto inputNeuron_ : layersPair.first){
		std::shared_ptr<InputNeuron> inputNeuron = std::dynamic_pointer_cast<InputNeuron>(inputNeuron_);//TODO: try to reduce
		for(auto outputNeuron_ : layersPair.second){
			std::shared_ptr<OutputNeuron> outputNeuron = std::dynamic_pointer_cast<OutputNeuron>(outputNeuron_);//same as above
			std::shared_ptr<Dendrite> dendrite(new Dendrite(outputNeuron,
															inputNeuron->axon,
															this->getDendriteMultiplier()));
			inputNeuron->axon->addConnection(dendrite);
			outputNeuron->addDendrite(dendrite);
		}
	}
}





bool NeuralNetwork::checkConnectivity(std::shared_ptr<InputNeuron> inputNeuron,
									  std::shared_ptr<OutputNeuron> outputNeuron) const{

	std::shared_ptr<Axon> axon = inputNeuron->axon;
	std::shared_ptr<Dendrite> dendrite;
	for(const auto dendrite_ : axon->dendrites){
		if(dendrite_->outputNeuron == outputNeuron){
			dendrite = dendrite_;
			break;
		}
	}

	if(dendrite == false)
		return false;
	std::shared_ptr<OutputNeuron> output = dendrite->outputNeuron;
	if(output != outputNeuron)
		return false;

	std::shared_ptr<Dendrite> reverseDendrite;

	for(const auto dendrite_ : output->inputDendrites)
		if(dendrite_ == dendrite){
			reverseDendrite = dendrite;
			break;
		}

	if(!reverseDendrite)
		return false;

	std::shared_ptr<Axon> reverseAxon = reverseDendrite->axon;
	if(reverseAxon != axon)
		return false;

	std::shared_ptr<InputNeuron> reverseInput = reverseAxon->inputNeuron;
	if(reverseInput != inputNeuron)
		return false;

	return true;

}

size_t NeuralNetwork::getLayerCount() const{
	return this->hiddenNeurons.size() + 2;
}

std::vector<std::shared_ptr<InputNeuron>> NeuralNetwork::getInputLayer(const size_t index) const{
	if(index == 0)
		return this->inputLayer;
	else if(index < this->getLayerCount() - 1)
		return superVector2InputVector(this->hiddenNeurons.at(index - 1));
	else
		throw std::runtime_error("Out of range");
}

std::vector<std::shared_ptr<OutputNeuron>> NeuralNetwork::getOutputLayer(const size_t index) const{
	if(index > 0 && index < this->getLayerCount() - 1)
		return superVector2OutputVector(this->hiddenNeurons.at(index - 1));
	else if(index == this->getLayerCount() - 1)
		return this->outputLayer;
	else
		throw std::runtime_error("Out of range");
}

IOLayersPair NeuralNetwork::getLayersPair(const size_t previousLayerIndex) const{
	return std::make_pair(this->getInputLayer(previousLayerIndex), this->getOutputLayer(previousLayerIndex + 1));
}

void NeuralNetwork::test() const{
	for(size_t previousLayerIndex = 0; previousLayerIndex < this->getLayerCount() - 1; ++previousLayerIndex){
		IOLayersPair layersPair = move(getLayersPair(previousLayerIndex));

		for(auto inputNeuron : layersPair.first)
			for(auto OutputNeuron : layersPair.second)
				if(checkConnectivity(inputNeuron, OutputNeuron) == false)
					throw std::runtime_error("Disconnected");
	}

}

std::string NeuralNetwork::toString() const{
	size_t layerNumber = 0;
	std::string result;

	result += std::to_string(layerNumber++) + ". ";
	for(const auto neuron : this->inputLayer)
		result += neuron->toString() + "\t";
	result += '\n';

	for(const auto hiddenLayer : this->hiddenNeurons){
		result += std::to_string(layerNumber++) + ". ";
		for(const auto neuron : hiddenLayer)
			result += neuron->toString() + "\t";
		result += '\n';
	}

	result += std::to_string(layerNumber++) + ". ";
	for(const auto neuron :  this->outputLayer)
		result += neuron->toString() + "\t";
	result += '\n';

	return result;

}











std::vector<std::shared_ptr<InputNeuron>> superVector2InputVector(const std::vector<std::shared_ptr<SuperNeuron>> &superNeurons){
	std::vector<std::shared_ptr<InputNeuron>> result(superNeurons.cbegin(), superNeurons.cend());
	return result;
}

std::vector<std::shared_ptr<OutputNeuron>> superVector2OutputVector(const std::vector<std::shared_ptr<SuperNeuron>> &superNeurons){
	std::vector<std::shared_ptr<OutputNeuron>> result(superNeurons.cbegin(), superNeurons.cend());
	return result;
}











