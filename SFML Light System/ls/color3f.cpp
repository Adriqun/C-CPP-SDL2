#include "color3f.h"
#include <SFML/OpenGL.hpp>

Color3f::Color3f()
{
	r = g = b = 0.0f;
}

Color3f::Color3f(float r, float g, float b) : r(r), g(g), b(b)
{
	// ...
}

void Color3f::set()
{
	glColor3f(r, g, b);
}
