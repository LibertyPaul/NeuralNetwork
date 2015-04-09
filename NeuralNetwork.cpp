#include <stdexcept>
#include <type_traits>
#include "NeuralNetwork.hpp"
#include "Axon.hpp"
#include "InputNeuron.hpp"
#include "SuperNeuron.hpp"
#include "OutputNeuron.hpp"

NeuralNetwork::NeuralNetwork(const std::vector<uint32_t> &layerSizes): weightDistribution(0.0, 10.0), multiplierDistribution(0.0, 1.0){
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

IOLayersPair NeuralNetwork::getLayersPair(const size_t previousLayerIndex) const{
	if(previousLayerIndex == 0){
		if(this->getLayerCount() == 2)
			return std::make_pair(this->inputLayer, this->outputLayer);
		else
			return std::make_pair(this->inputLayer, superVector2OutputVector(this->hiddenNeurons.front()));
	}
	else if(previousLayerIndex > 0 && previousLayerIndex < this->getLayerCount() - 2)
		return std::make_pair(superVector2InputVector(this->hiddenNeurons.at(previousLayerIndex - 1)),
							  superVector2OutputVector(this->hiddenNeurons.at(previousLayerIndex)));
	else if(previousLayerIndex == this->getLayerCount() - 2)//тут подразумевается, что случай при previousLayerIndex == 0 исключен в самом начале
		return std::make_pair(superVector2InputVector(this->hiddenNeurons.back()), this->outputLayer);
	else
		throw std::runtime_error("Incorrect previousLayerIndex");
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
	for(size_t i = 0; i < this->inputLayer.size(); ++i)
		result += '*';
	result += '\n';

	for(const auto hiddenLayer : this->hiddenNeurons){
		result += std::to_string(layerNumber++) + ". ";
		for(size_t i = 0; i < hiddenLayer.size(); ++i)
			result += '*';
		result += '\n';
	}

	result += std::to_string(layerNumber++) + ". ";
	for(size_t i = 0; i < this->outputLayer.size(); ++i)
		result += '*';
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










