#include <iostream>
#include <windows.h>

std::string snowballs = "*";
std::string christmasballs = "@0oO8";
std::string leaves = "H!;:\"[]$%^&(){}'~.,-=";
std::string wood = "#";
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

bool isTree(const char &sign)
{
	for (auto it : leaves)
		if (sign == it)
			return true;
	if (sign == '/' || sign == '\\')
		return true;
	return false;
}

bool isSnowBall(const char &sign)
{
	for (auto it : snowballs)
		if (sign == it)
			return true;
	return false;
}

bool isWood(const char &sign)
{
	for (auto it : wood)
		if (sign == it)
			return true;
	return false;
}

void setTree()
{
	SetConsoleTextAttribute(hConsole, 2);
}

void setChristmasBall()
{
	SetConsoleTextAttribute(hConsole, rand() % 6 + 9);
}

void setSnowBall()
{
	SetConsoleTextAttribute(hConsole, rand() % 2 == 0 ? 15 : 7);
}

void setWood()
{
	SetConsoleTextAttribute(hConsole, 6);
}

int main()
{
	const int width = 45;
	const int wwidth = 9;

	const int w = width + 2, h = width / 2;
	char tree[w][h];
	char chballs[w][h];
	char snballs[w][h];
	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j)
		{
			tree[i][j] = ' ';
			chballs[i][j] = ' ';
			snballs[i][j] = rand()%10 == 0 ? '*' : ' ';
		}
			

	int s = h - 1, l = 2;
	for (int j = 0; j < h - 2; ++j)
	{
		for (int i = s; i < s + l; ++i)
		{
			tree[i][j] = leaves[rand() % leaves.size()];
		}
		--s;
		l += 2;
	}

	// left border of a tree
	for (int j = 0; j < h; ++j)
		for (int i = 0; i < w; ++i)
			if (tree[i][j] != ' ')
			{
				tree[i][j] = '/';
				break;
			}

	// right border of a tree
	for (int j = 0; j < h; ++j)
		for (int i = w - 1; i >= 0; --i)
			if (tree[i][j] != ' ')
			{
				tree[i][j] = '\\';
				break;
			}

	// fill christmas balls
	for (int j = 0; j < h; ++j)
		for (int i = w - 1; i >= 0; --i)
			if (tree[i][j] != ' ' && tree[i][j] != '/' && tree[i][j] != '\\') // but no borders
			{
				if(rand() % 10 < 2)
					chballs[i][j] = christmasballs[rand() % christmasballs.size()];
			}

	const int wstart = (width / 2) - (wwidth / 2);
	const int wend = (width / 2) + (wwidth / 2);
	for (int j = h - 2; j < h; ++j)
	{
		for(int i = wstart; i <= wend; ++i)
			tree[i][j] = wood[rand() % wood.size()];
	}
	
	while (1)
	{
		system("cls");
		for (int i = 0; i < h; ++i)
		{
			for (int j = 0; j < w; ++j)
			{
				if (snballs[j][i] != ' ')
				{
					setSnowBall();
					std::cout << snballs[j][i];
					continue;
				}
				else if (chballs[j][i] != ' ')
				{
					setChristmasBall();
					std::cout << chballs[j][i];
					continue;
				}

				if (isTree(tree[j][i]))	setTree();
				else if (isWood(tree[j][i]))	setWood();
				std::cout << tree[j][i];
			}
			
			std::cout << std::endl;
		}

		// move snow balls
		char buf[w];
		for (int i = 0; i < w; ++i)
			buf[i] = snballs[i][h - 1];

		for(int i = h - 1; i >= 1; --i)
			for (int j = 0; j < w; ++j)
			{
				snballs[j][i] = snballs[j][i - 1];
			}
		for (int i = 0; i < w; ++i)
			snballs[i][0] = buf[i];

		Sleep(1000);
	}

	return 0;
}
