#pragma once
#include "vec2f.h"
#include <SFML/OpenGL.hpp>

namespace ls
{
	struct ShadowFin
	{
		Vec2f rootPos;
		Vec2f umbra;
		Vec2f penumbra;

		float umbraBrightness;
		float penumbraBrightness;

		ShadowFin();
		~ShadowFin();
		void render(float transparency);
	};
}