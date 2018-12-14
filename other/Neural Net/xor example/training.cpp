#include <sstream>
#include "training.h"

Neural::Training::Training(const char* filename)
{
	free();

	if (!(filename != nullptr && filename[0] == '\0'))
	{
		open(filename);
	}
}

Neural::Training::~Training()
{
	free();
}

void Neural::Training::free()
{
	close();

	if (!inputs.empty())
		inputs.clear();

	if (!targets.empty())
		targets.clear();

	if (!results.empty())
		results.clear();

	if (!topology.empty())
		topology.clear();

	counter = 0;
}



bool Neural::Training::open(const char* filename)
{
	file.open(filename);

	if (file.good())
	{
		return true;
	}

	return false;
}

void Neural::Training::close()
{
	if (file.is_open())
	{
		file.close();
	}
}

bool Neural::Training::isEOF()
{
	return file.eof();
}



unsigned Neural::Training::setInputs()
{
	inputs.clear();

	std::string line;
	getline(file, line);
	std::stringstream ss(line);

	std::string label;
	ss >> label;
	if (label.compare("in:") == 0)
	{
		double value;
		while (ss >> value)
		{
			inputs.push_back(value);
		}
	}

	return inputs.size();
}

unsigned Neural::Training::setTargets()
{
	targets.clear();

	std::string line;
	getline(file, line);
	std::stringstream ss(line);

	std::string label;
	ss >> label;
	if (label.compare("out:") == 0)
	{
		double value;
		while (ss >> value)
		{
			targets.push_back(value);
		}
	}

	return targets.size();
}

bool Neural::Training::setTopology()
{
	std::string line;
	getline(file, line);

	size_t result = line.find("topology:");
	if ((result != std::string::npos && result != 0) || isEOF())
	{
		return false;
	}

	std::stringstream ss(line);
	ss >> line;
	while (!ss.eof())
	{
		unsigned n;
		ss >> n;
		topology.push_back(n);
	}

	return true;
}

std::vector<double>& Neural::Training::getInputs()
{
	return inputs;
}

std::vector<double>& Neural::Training::getTargets()
{
	return targets;
}

std::vector<double>& Neural::Training::getResults()
{
	return results;
}

std::vector<unsigned>& Neural::Training::getTopology()
{
	return topology;
}



void Neural::Training::iterate()
{
	++counter;
}

int Neural::Training::getCounter()
{
	return counter;
}