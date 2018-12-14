#pragma once
#include "neuron.h"

namespace Neural
{
	class Net
	{
		double error;
		double RA_Error;			// Recent Average Error
		static double RAS_Factor;	// Recent Average Smoothing Factor
		std::vector<Layer> layers;	// layers[layerNum][neuronNum]
	public:
		Net(const std::vector<unsigned> &topology);
		~Net();
		void free();
		double getRecentAverageError();
		void getResults(std::vector<double> &results) const;
		void feedForward(const std::vector<double> &inputs);
		void backPropagation(const std::vector<double> &targets);
	};
}