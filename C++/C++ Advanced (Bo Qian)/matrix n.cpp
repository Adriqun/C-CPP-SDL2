#include <iostream>

float getDet2D(float** tab)
{
	return tab[0][0] * tab[1][1] - tab[1][0] * tab[0][1];
}

float getDet3D(float** tab)
{
	float a = tab[0][0] * tab[1][1] * tab[2][2];
	float b = tab[0][1] * tab[1][2] * tab[2][0];
	float c = tab[0][2] * tab[1][0] * tab[2][1];

	float d = tab[2][0] * tab[1][1] * tab[0][2];
	float e = tab[0][0] * tab[1][2] * tab[2][1];
	float f = tab[1][0] * tab[0][1] * tab[2][2];

	return (a + b + c) - (d + e + f);
}

float getDetND(float** tab, int level)
{
	if (level == 3)
		return getDet3D(tab);

	float result = 0;
	int next = level - 1;
	float** buffer = nullptr;

	// allocate
	buffer = new float*[next];
	for (int i = 0; i < next; ++i)
		buffer[i] = new float[next];

	// calculate
	for (int i = 0; i < level; ++i)
	{
		int h = 0;	// y pos
		for (int j = 0; j < level; ++j)			
		{
			if (i != j)
			{
				for (int k = 1; k < level; ++k)	// x pos
				{
					buffer[k - 1][h] = tab[k][j];
				}
				++h;
			}
		}

		result += tab[0][i] * (i % 2 == 0 ? getDetND(buffer, next) : -getDetND(buffer, next));
	}

	// deallocate
	for (int i = 0; i < next; ++i)
		delete[] buffer[i];
	delete[] buffer;
	
	return result;
}


float getDet(float** tab, int level)
{
	if (level == 0)
		return 0;
	else if (level == 1)
		return tab[0][0];
	else if (level == 2)
		return getDet2D(tab);

	return getDetND(tab, level);
}

int main()
{
	int level = 5;
	float** tab;
	tab = new float*[level];
	for (int i = 0; i < level; ++i)
		tab[i] = new float[level];

	tab[0][0] = 1;
	tab[0][1] = 5;
	tab[0][2] = 3;
	tab[0][3] = 12;
	tab[0][4] = -5;

	tab[1][0] = -10;
	tab[1][1] = 2;
	tab[1][2] = 0;
	tab[1][3] = -9;
	tab[1][4] = -1;

	tab[2][0] = 3;
	tab[2][1] = 8;
	tab[2][2] = 1;
	tab[2][3] = 3;
	tab[2][4] = 3;

	tab[3][0] = -5;
	tab[3][1] = 3;
	tab[3][2] = 1;
	tab[3][3] = 2;
	tab[3][4] = 0;

	tab[4][0] = 0;
	tab[4][1] = 3;
	tab[4][2] = 5;
	tab[4][3] = 1;
	tab[4][4] = 1;

	std::cout << getDetND(tab, level);

	return 0;
}