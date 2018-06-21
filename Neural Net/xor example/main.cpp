#include <iostream>
#include <string>
#include <cassert>
#include "net.h"
#include "training.h"




void showVectorValues(std::string label, std::vector<double> &v)
{
	std::cout << label << " ";
	for (unsigned i = 0; i < v.size(); ++i)
	{
		std::cout << v[i] << " ";
	}
	std::cout << '\n';
}


int main()
{
	using namespace Neural;

	Training training("data.txt");
	training.setTopology();

	Net net(training.getTopology());

	while (!training.isEOF())
	{
		// Get new input data and feed it forward
		if (training.setInputs() != training.getTopology()[0])
			break;

		training.iterate();
		std::cout << "\nCounter: " << training.getCounter() << '\n';
			
		showVectorValues("Inputs:", training.getInputs());
		net.feedForward(training.getInputs());

		// Collect the net's actual results:
		net.getResults(training.getResults());
		showVectorValues("Outputs:", training.getResults());

		// Train the net what the outputs should have been:
		training.setTargets();
		showVectorValues("Targets:", training.getTargets());
		assert(training.getTargets().size() == training.getTopology().back());

		net.backPropagation(training.getTargets());

		// Report how well the training is working, average over recnet
		std::cout << "Net recent average error: " << net.getRecentAverageError() << '\n';
	}

	return 0;
}