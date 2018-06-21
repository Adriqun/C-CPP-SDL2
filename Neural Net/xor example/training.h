#pragma once
#include <vector>
#include <fstream>

namespace Neural
{
	class Training
	{
		std::ifstream file;
		std::vector<double> inputs;
		std::vector<double> targets;
		std::vector<double> results;
		std::vector<unsigned> topology;
		int counter;
	public:
		Training(const char* = "");
		~Training();
		void free();

		// File
		bool open(const char* filename);
		void close();
		bool isEOF();

		// Set/Get
		unsigned setInputs();
		unsigned setTargets();
		bool setTopology();
		std::vector<double>& getInputs();
		std::vector<double>& getTargets();
		std::vector<double>& getResults();
		std::vector<unsigned>& getTopology();

		// Counter
		void iterate();
		int getCounter();
	};

}