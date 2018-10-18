#pragma once
#include <cmath>

namespace ls
{
	const double PI = 3.14159265359;
	const float pif = static_cast<float>(PI);
	const float pifTimes2 = pif * 2.0f;

	template<class T> T wrap(T val, T size)
	{
		if (val < 0)
			return val + size;

		if (val >= size)
			return val - size;

		return val;
	}
}