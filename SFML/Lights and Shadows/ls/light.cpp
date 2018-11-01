/*
Let There Be Light
Copyright (C) 2012 Eric Laukien

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

/*
Update by Adrian Michalek 2018.10.18
- Some functions were updated and shorten.
- Some code were deleted due to regressions and depracations.
- Names of variables and functions were changed.
- Functionality stays the same.
*/

#pragma once
#include "light.h"
#include <cassert>

namespace ls
{
	Light::Light()
	{
		updateRequired = true;
		alwaysUpdate = true;
		window = nullptr;
		staticTexture = nullptr;
		ls = nullptr;
		shaderAttenuation = true;

		center = Vec2f(0.0f, 0.0f);
		intensity = 1.0f;
		radius = 100.0f;
		size = 40.0f;
		bleed = 1.0f;
		linearizeFactor = 0.2f;
		color = Color3f(1.0f, 1.0f, 1.0f);
	}

	Light::~Light()
	{
		// Destroy the static Texture if one exists
		if(alwaysUpdate)
			delete staticTexture;
	}

	AABB* Light::getAABB()
	{
		return &aabb;
	}

	const bool &Light::isAlwaysUpdate() const
	{
		return alwaysUpdate;
	}

	void Light::setAlwaysUpdate(bool always)
	{
		// Must add to the light system before calling this
		assert(window);

		if(!always && alwaysUpdate) // If previously set to false, create a render Texture for the static texture
		{
			Vec2f dims(aabb.getDims());

			// Check if large enough textures are supported
			unsigned int maxDim = sf::Texture::getMaximumSize();

			if(maxDim <= dims.x || maxDim <= dims.y)
			{
				std::cout << "Attempted to create a too large static light. Switching to dynamic." << std::endl;
				return;
			}

			// Create the render Texture based on aabb dims
			staticTexture = new sf::RenderTexture();

			unsigned int uiDimsX = static_cast<unsigned int>(dims.x);
			unsigned int uiDimsY = static_cast<unsigned int>(dims.y);

			sf::ContextSettings cs = sf::ContextSettings();
			cs.depthBits = 0;

			staticTexture->create(uiDimsX, uiDimsY, cs);

			staticTexture->setSmooth(true);

			staticTexture->setActive();
			glEnable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);
			window->setActive();

			updateRequired = true;
		}
		else if(always && !alwaysUpdate) // If previously set to true, destroy the render Texture
			delete staticTexture;
	
		alwaysUpdate = always;
	}

	void Light::switchStaticTexture()
	{
		Vec2f dims(aabb.getDims());

		staticTexture->setActive();

		glViewport(0, 0, static_cast<unsigned int>(dims.x), static_cast<unsigned int>(dims.y));

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Flip the projection, since SFML draws the bound textures (on the FBO) upside down
		glOrtho(0, static_cast<unsigned int>(dims.x), static_cast<unsigned int>(dims.y), 0, -100.0f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
	}

	void Light::setRadius(float newRadius)
	{
		assert(alwaysUpdate);

		radius = newRadius;

		calculateAABB();
		update();
	}

	void Light::incRadius(float increment)
	{
		assert(alwaysUpdate);

		radius += increment;

		calculateAABB();
		update();
	}

	const float &Light::getRadius() const
	{
		return radius;
	}

	void Light::setCenter(Vec2f newCenter)
	{
		Vec2f difference(newCenter - center);

		center = newCenter;
		aabb.incCenter(difference);
		update();
		updateRequired = true;
	}

	void Light::incCenter(Vec2f increment)
	{
		center += increment;
		aabb.incCenter(increment);
		update();
		updateRequired = true;
	}

	const Vec2f &Light::getCenter() const
	{
		return center;
	}

	void Light::calculateAABB()
	{
		aabb.setCenter(center);
		aabb.setDims(Vec2f(radius, radius));
	}
}
