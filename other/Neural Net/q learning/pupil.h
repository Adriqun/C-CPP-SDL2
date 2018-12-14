#pragma once
#include <vector>

class Pupil
{
	int goal;
	double alpha;
	std::vector<std::vector<double>> matrixr;
	std::vector<std::vector<double>> matrixq;	// brain

public:
	Pupil();
	~Pupil();
	void free();

	void printR();
	void printQ();

	void setGoal(int newGoal = 0);
	void setAlpha(double newAlpha = 0.8);
	bool loadFromFile(const char* path = "");
	void runTraining(int size = 1000, int state = 0);	// Number of lessons, start state
	int getBestAction(int state);

private:
	int lesson(int state);
	double getMax(int state);		// Get greatest value of the row
	int getNextAction(int state);	// Get next possible action
};