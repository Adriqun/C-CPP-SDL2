#include "pupil.h"
#include <iostream>

int main()
{
	int GOAL = 5;
	Pupil pupil;
	pupil.loadFromFile("data.txt");
	pupil.printR();
	pupil.setGoal(GOAL);
	pupil.setAlpha(0.8);
	pupil.runTraining();
	pupil.printQ();

	// Test
	for (;;)
	{
		int pos;
		std::cout << "Input robot locate room: " << std::endl;
		std::cin >> pos;
		std::cout << pos << "->";
		for(;;)
		{
			int bestAction = pupil.getBestAction(pos);
			std::cout << bestAction << "->";
			if (bestAction == GOAL)
			{
				std::cout << "out" << std::endl;
				break;
			}
			else
				pos = bestAction;
		}
	}

	return 0;
}