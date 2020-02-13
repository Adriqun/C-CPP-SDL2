#include "TextBlock.h"
#include "Options.h"
#include <iostream>


int main(int argc, char** argv)
{
	bool status;
	Options options(argc, argv, status);
	if (status)
	{
		for (auto it = options.Begin(); it != options.End(); ++it)
		{
			TextBlockManager tbm(*it, status);
			if (!status)
				break;
			if (!tbm.RedirectToFile(*it + "i"))
				break;
		}
	}

	return 0;
}