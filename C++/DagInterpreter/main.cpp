#include "TextBlock.h"
#include "Options.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (Options::Parse(argc, argv))
	{
		for (auto it = Options::Begin(); it != Options::End(); ++it)
		{
			bool status;
			TextBlockManager tbm(*it, status);
			if (!status)
				break;
			if (!tbm.RedirectToFile(*it + "r"))
				break;
		}
	}

	return 0;
}