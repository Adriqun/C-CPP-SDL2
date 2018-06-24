#include "pupil.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

Pupil::Pupil()
{
	free();
}

Pupil::~Pupil()
{
	free();
}

void Pupil::free()
{
	goal = -1;
	alpha = 0;
}

void Pupil::printR()
{
	printf("Matrix R:\n");
	for (int i = 0; i < matrixr.size(); ++i)
	{
		for (int j = 0; j < matrixr[i].size(); ++j)
		{
			printf("%d\t", static_cast <int> (matrixr[i][j]));
		}
		printf("\n");
	}
	printf("\n");
}

void Pupil::printQ()
{
	printf("Matrix Q:\n");
	for (int i = 0; i < matrixq.size(); ++i)
	{
		for (int j = 0; j < matrixq[i].size(); ++j)
		{
			printf("%d\t", static_cast <int> (matrixq[i][j]));
		}
		printf("\n");
	}
	printf("\n");
}

void Pupil::setGoal(int newGoal)
{
	if (newGoal > -1 && newGoal < matrixr.size())
		goal = newGoal;
}

void Pupil::setAlpha(double newAlpha)
{
	if (newAlpha > 0.0 && newAlpha < 1.0)
		alpha = newAlpha;
}

bool Pupil::loadFromFile(const char* path)
{
	std::ifstream file(path);
	if (file.bad())
	{
		return false;
	}
	else
	{
		// Fill matrix R
		std::string line;
		while (getline(file, line))
		{
			double value;
			std::vector<double> bufor;
			std::stringstream ss(line);

			while (ss >> value)
				bufor.push_back(value);

			matrixr.push_back(bufor);
		}

		// Fill brain with zeros
		matrixq = matrixr;
		for (auto &it : matrixq)
			std::fill(it.begin(), it.end(), 0);
	}
}

void Pupil::runTraining(int size, int state)
{
	if (state >= 0 && state < matrixr.size() && alpha > 0 && goal > -1)
	{
		srand((unsigned)time(NULL));

		while (--size)
			state = lesson(state);
	}
}

int Pupil::getBestAction(int state)
{
	int index = -1;
	double max = -1;
	for (int i = 0; i < matrixq.size(); ++i)
	{
		if (matrixq[state][i] > max)
		{
			max = matrixq[state][i];
			index = i;
		}
	}

	return index;
}



int Pupil::lesson(int state)
{
	for(;;)
	{
		// Set next action
		int nextAction = getNextAction(state);

		// Update formula Q(s,a) = R(s,a) + alpha * max{Q(s', a')}
		matrixq[state][nextAction] = matrixr[state][nextAction] + alpha * getMax(nextAction);

		// If next_action is destination state, then go next lesson, if not, then go back to this loop
		if (nextAction == goal)
		{
			state = rand() % static_cast <int> (matrixr.size());
			break;
		}
		else
			state = nextAction;
	}

	return state;
}

double Pupil::getMax(int state)
{
	double max = 0;
	for (int i = 0; i < matrixq.size(); ++i)
	{
		if (matrixq[state][i] > max)
		{
			max = matrixq[state][i];
		}
	}

	return max;
}

int Pupil::getNextAction(int state)
{
	std::vector<int> actions;
	for (unsigned i = 0; i < matrixr.size(); ++i)
	{
		if (matrixr[state][i] > -1)
		{
			actions.push_back(i);
		}
	}

	return actions[rand() % static_cast <int> (actions.size())];
}