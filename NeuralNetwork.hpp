#ifndef NEURALNETWORK
#define NEURALNETWORK

#include <vector>
#include <memory>
#include <random>
#include <string>
#include <utility>

class InputNeuron;
class OutputNeuron;
class SuperNeuron;

typedef std::pair<std::vector<std::shared_ptr<InputNeuron>>,
				  std::vector<std::shared_ptr<OutputNeuron>>> IOLayersPair;

class NeuralNetwork{
private:
	mutable std::default_random_engine generator;
	mutable std::uniform_real_distribution<double> weightDistribution, multiplierDistribution;
protected:
	std::vector<std::shared_ptr<InputNeuron>> inputLayer;
	std::vector<std::vector<std::shared_ptr<SuperNeuron>>> hiddenNeurons;
	std::vector<std::shared_ptr<OutputNeuron>> outputLayer;

	void connectLayers(const IOLayersPair &layersPair) const;

	double getDendriteMultiplier() const;
	double getNeuronWeight() const;


	bool checkConnectivity(std::shared_ptr<InputNeuron> inputNeuron,
						   std::shared_ptr<OutputNeuron> outputNeuron) const;

	IOLayersPair getLayersPair(const size_t previousLayerIndex) const;
public:
	NeuralNetwork(const std::vector<uint32_t> &layerSizes);

	size_t getLayerCount() const;

	std::string toString() const;
	void test() const;

};

std::vector<std::shared_ptr<InputNeuron>> superVector2InputVector(const std::vector<std::shared_ptr<SuperNeuron>> &superNeurons);
std::vector<std::shared_ptr<OutputNeuron>> superVector2OutputVector(const std::vector<std::shared_ptr<SuperNeuron>> &superNeurons);

#endif // NEURALNETWORK

