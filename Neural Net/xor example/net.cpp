#include <cmath>
#include <cassert>
#include "net.h"

double Neural::Net::RAS_Factor = 100.0; // Number of training samples to average over

Neural::Net::Net(const std::vector<unsigned> &topology)
{
	free();

	for (unsigned layerNum = 0; layerNum < topology.size(); ++layerNum)
	{
		layers.push_back(Layer());
		// numOutputs of layer[i] is the numInputs of layer[i+1]
		// numOutputs of last layer is 0
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		// We have made a new Layer, now fill it with neurons, and add a bias neuron to the layer
		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			layers.back().push_back(Neuron(numOutputs, neuronNum));
		}

		// Force the bias node's output value to 1.0. It's the last neuron created above
		layers.back().back().setOutputValue(1.0);
	}
}

Neural::Net::~Net()
{
	free();
}

void Neural::Net::free()
{
	error = 0;
	RA_Error = 0;

	if (!layers.empty())
		layers.clear();
}

double Neural::Net::getRecentAverageError()
{
	return RA_Error;
}

void Neural::Net::getResults(std::vector<double> &results) const
{
	results.clear();

	for (unsigned n = 0; n < layers.back().size() - 1; ++n)
	{
		results.push_back(layers.back()[n].getOutputValue());
	}
}

void Neural::Net::feedForward(const std::vector<double> &inputs)
{
	// Check the num of inputVals euqal to neuronnum expect bias
	assert(inputs.size() == layers[0].size() - 1);

	// Assign {latch} the input values into the input neurons
	for (unsigned i = 0; i < inputs.size(); ++i)
	{
		layers[0][i].setOutputValue(inputs[i]);
	}

	// Forward propagate
	for (unsigned layerNum = 1; layerNum < layers.size(); ++layerNum)
	{
		Layer &prevLayer = layers[layerNum - 1];
		for (unsigned n = 0; n < layers[layerNum].size() - 1; ++n)
		{
			layers[layerNum][n].feedForward(prevLayer);
		}
	}
}

void Neural::Net::backPropagation(const std::vector<double> &targets)
{
	// Calculate overal net error (RMS of output neuron errors)
	error = 0.0;
	Layer& outputLayer = layers.back();

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n)
	{
		double delta = targets[n] - outputLayer[n].getOutputValue();
		error += delta * delta;
	}
	error /= outputLayer.size() - 1; // get average error squared
	error = sqrt(error);			 // RMS

									 // Implement a recent average measurement:
	RA_Error = (RA_Error * RAS_Factor + error) / (RAS_Factor + 1.0);

	// Calculate output layer gradients
	for (unsigned n = 0; n < outputLayer.size() - 1; ++n)
	{
		outputLayer[n].calculateOutputGradients(targets[n]);
	}

	// Calculate gradients on hidden layers
	for (unsigned layerNum = layers.size() - 2; layerNum > 0; --layerNum)
	{
		Layer& hiddenLayer = layers[layerNum];
		Layer& nextLayer = layers[layerNum + 1];

		for (unsigned n = 0; n < hiddenLayer.size(); ++n)
		{
			hiddenLayer[n].calculateHiddenGradients(nextLayer);
		}
	}

	// For all layers from outputs to first hidden layer, update connection weights
	for (unsigned layerNum = layers.size() - 1; layerNum > 0; --layerNum)
	{
		Layer& layer = layers[layerNum];
		Layer& prevLayer = layers[layerNum - 1];

		for (unsigned n = 0; n < layer.size() - 1; ++n)
		{
			layer[n].updateInputWeights(prevLayer);
		}
	}
}

